// Definición de pines
int VelocidadMotor1 = 6;
int VelocidadMotor2 = 5;
int Motor1A = 13;
int Motor1B = 12;
int Motor2C = 11;
int Motor2D = 10;
int infraPin = 2;
int infraPin1 = 4;
int higrometroPin = A0;
int bombaPin = 9;

// Sensores infrarrojo - izquierdo y derecho
int valorInfra = 0;
int valorInfra1 = 0;

// Servo y objeto Servo para controlar el higrómetro
Servo servoHigrometro;
int higrometroAngulo = 90;

// Variables para el riego
int humedadMinima = 500;
bool riegoActivo = false;

// Configuración inicial
void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(infraPin, INPUT);
  pinMode(infraPin1, INPUT);
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2C, OUTPUT);
  pinMode(Motor2D, OUTPUT);
  pinMode(VelocidadMotor1, OUTPUT);
  pinMode(VelocidadMotor2, OUTPUT);
  pinMode(higrometroPin, INPUT);
  pinMode(bombaPin, OUTPUT);

  analogWrite(VelocidadMotor1, 150);
  analogWrite(VelocidadMotor2, 150);

  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, LOW);

  servoHigrometro.attach(7); // Pin del servo para el higrómetro
  servoHigrometro.write(higrometroAngulo);
}

// Ejecución contínua
void loop() {
  valorInfra = digitalRead(infraPin);
  valorInfra1 = digitalRead(infraPin1);

  Serial.println(valorInfra);
  Serial.println(valorInfra1);

  // Cuatro escenarios: De frente
  if (valorInfra == 0 && valorInfra1 == 0) {
    Serial.println("Ninguno en linea");

    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor2D, HIGH);
    delay(20);
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor2D, LOW);
    delay(20);
  }

  // El robot encuentra línea negra con el infrarrojo derecho y hay que corregir girando a la derecha
  if (valorInfra == 0 && valorInfra1 == 1) {
    Serial.println("Derecho en linea");

    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor2D, LOW);
    delay(25);
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor2D, LOW);
    delay(20);
  }

  // El robot encuentra línea negra con el infrarrojo izquierdo y hay que corregir girando a la izquierda
  if (valorInfra == 1 && valorInfra1 == 0) {
    Serial.println("Izquierdo en linea");

    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor2D, LOW);
    delay(25);
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor2D, HIGH);
    delay(20);
  }

  // Los dos sensores infrarrojos encuentran una línea negra, el final del circuito
  if (valorInfra == 1 && valorInfra1 == 1) {
    Serial.println("Ambos en linea");

    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2C, LOW);
    digitalWrite(Motor2D, LOW);

    int humedad = analogRead(higrometroPin);
    if (humedad < humedadMinima && !riegoActivo) {
      riegoActivo = true;
      servoHigrometro.write(0); // Bajar higrómetro al suelo
      delay(2000); // Esperar a que el higrómetro toque el suelo
      digitalWrite(bombaPin, HIGH); // Activar bomba de agua
      delay(5000); // Riego por 5 segundos
      digitalWrite(bombaPin, LOW); // Desactivar bomba de agua
      servoHigrometro.write(higrometroAngulo); // Subir higrómetro
      riegoActivo = false;
    }
  }
}
