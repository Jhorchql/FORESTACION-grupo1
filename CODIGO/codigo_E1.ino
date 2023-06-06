// Definición pines EnA y EnB para el control de la velocidad
int VelocidadMotor1 = 6; 
int VelocidadMotor2 = 5;

// Definición de los pines de control de giro de los motores In1, In2, In3 e In4
int Motor1A = 13; 
int Motor1B = 12;  
int Motor2C = 11; 
int Motor2D = 10; 

// Sensores infrarrojo - izquierdo y derecho
int infraPin  = 2;    
int infraPin1 = 4;

// Variables para la captura de los valores: 0 - fondo claro y 1 - línea negra
int valorInfra = 0;  
int valorInfra1 = 0;  

// Configuración inicial
void setup() {
  Serial.begin(9600);
  
  delay(1000);

  // Establecemos modo de los pines de los sensores infrarrojo
  pinMode(infraPin, INPUT);    
  pinMode(infraPin1, INPUT);

  // Establecemos modo de los pines del control de motores
  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B,OUTPUT);
  pinMode(Motor2C,OUTPUT);
  pinMode(Motor2D,OUTPUT);
  pinMode(VelocidadMotor1, OUTPUT);
  pinMode(VelocidadMotor2, OUTPUT);

  // Configuramos los dos motores a velocidad 150/255
  analogWrite(VelocidadMotor1, 150); 
  analogWrite(VelocidadMotor2, 150);  

  // Configuramos sentido de giro
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, LOW);
}

// Ejecución contínua
void loop() {
  // Leemos el valor de los infrarrojo: 0 - fondo claro y 1 - línea negra
  valorInfra = digitalRead(infraPin);   
  valorInfra1 = digitalRead(infraPin1);

  Serial.println(valorInfra);
  Serial.println(valorInfra1);
         
  // Cuatro escenarios: De frente      
  if(valorInfra == 0 && valorInfra1 == 0){
    Serial.println("Ninguno en linea");
    
    // Modificamos sentido de giro de los motores
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor2D, HIGH);
    delay(20);                      
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor2D,LOW);
    delay(20);                     
  }

  // El robot encuentra línea negra con el infrarrojo derecho y hay que corregir girando a la derecha
  if(valorInfra == 0 && valorInfra1 == 1){  
    Serial.println("Derecho en linea");
    
    // Modificamos sentido de giro de los motores
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor2D,LOW);
    delay(25);
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor2D,LOW);
    delay(20);
  }

  // El robot encuentra línea negra con el infrarrojo izquierdo y hay que corregir girando a la izquierda
  if(valorInfra == 1 && valorInfra1 == 0){ 
    Serial.println("Izquierdo en linea");
    
    // Modificamos sentido de giro de los motores
    digitalWrite(Motor1A,LOW);
    digitalWrite(Motor2D, LOW);
    delay(25);
    digitalWrite(Motor1A,LOW);
    digitalWrite(Motor2D, HIGH);
    delay(20);
  }

  // Los dos sensores infrarrojos encuentran una línea negra, el final del circuito
  if(valorInfra == 1 && valorInfra1 == 1){ 
    Serial.println("Ambos en linea");
    
    // Paramos los motores 
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2C, LOW);
    digitalWrite(Motor2D, LOW);
  }
}
