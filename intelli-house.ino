//Bibliotecas
#include <Servo.h>
#include <SimpleDHT.h>
#include <pt.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

// Sensores
#define LDR A0
#define HC_TRIGGER 32
#define HC_ECHO 2
#define PIR 50
#define DHT 53
#define RST_PIN  4
#define SS_PIN  31

// Salidas Digitales
#define LED_PATIO 44
#define LED_BANO 45
#define ACDC 46

#define SERVO_GARAGE 5
#define SERVO_PT1 6
#define SERVO_PT2 7

#define LED_R1 22
#define LED_V1 23
#define LED_R2 24
#define LED_V2 25

//Bases de datos
String baseDatos[] = {"C7 52 6B 63","A9 A0 8B C1"};
int bdSize = sizeof(baseDatos)/sizeof(String);
String baseDatos2[] = {"C7 52 6B 63","A9 A0 8B C1"};
int bdSize2 = sizeof(baseDatos2)/sizeof(String);

// Creación de Objetos
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Variables globales
volatile unsigned long LastPulseTime;  

// Hilos
struct pt procesoA;
struct pt procesoB;
struct pt procesoC;
struct pt procesoD;

// Setup
void setup(){
  PT_INIT(&procesoA);
  PT_INIT(&procesoB);
  PT_INIT(&procesoC);

  Serial.begin(9600);
  
  //SPI.begin();
  //mfrc522.PCD_Init();
}

// Loop
void loop(){
  fotosensor(&procesoA);
  sensorMovimiento(&procesoB);
  sensorDistancia(&procesoC);
}

/**
 * Sensor LDR
 * -----------------------------------------------
 * Si el valor de la lectura es menor que el de un 
 * valor límite (indica oscuridad) enciende la 
 * iluminación. 
 */
void fotosensor(struct pt *pt){
  PT_BEGIN(pt);
  static long t = 0;

  int valor;
  const int delay = 200;
  const int valorLimite = 200;

  pinMode(LED_PATIO, HIGH);

  while(true){
    digitalWrite(LED_PATIO, LOW);
    
    valor = analogRead(LDR);
    if(valor < valorLimite)
      digitalWrite(LED_PATIO, HIGH);
    
    t = millis();
    PT_WAIT_WHILE(pt,(millis()-t) < delay);

    PT_YIELD(pt);
  }
  PT_END(pt);
}

/**
 * Sensor Ultrasónico HCSR04
 * -----------------------------------------------
 * El sensor mide la distancia en cm.
 * Cuando la distancia es menor a una distancia d
 * se activa una salida.
 */
void sensorDistancia(struct pt *pt){
  PT_BEGIN(pt);
  const int delay_us = 10; // 10 microsegundos  
  const int limite = 20; // 15 cm
  int distancia;
  int tiempo;
  Servo servo;
  servo.attach(SERVO_GARAGE);

  attachInterurpt(0, EchoPinISR, CHANGE); // Pin 2

  pinMode(HC_ECHO, INPUT);
  pinMode(HC_TRIGGER, OUTPUT);
  
  
  while(true){

    digitalWrite(HC_TRIGGER, LOW);
    t = micros();
    PT_WAIT_WHILE(pt,(micros()-t) < 5);
    digitalWrite(HC_TRIGGER, HIGH);
    t = micros();
    PT_WAIT_WHILE(pt,(micros()-t) < delay_us);
    digitalWrite(HC_TRIGGER, LOW);

    distancia = LastPulseTime/58.2;

    if(distancia < limite)
      servo.write(90);
      

    Serial.print("Distancia = ");
    Serial.print(distancia);
    Serial.println(" cm");
    
    PT_YIELD(pt);
  }

  PT_END(pt);
}

/**
 * Sustituye la función síncrosa pulseIn()
 */
void EchoPinISR(){

  static unsigned long t;

  if(digitalRead(HC_ECHO))
    t = micros();
  else
    LastPulseTime = micros() - t;
}



/**
 * Sensor PIR
 * -----------------------------------------------
 * El sensor genera un señal ALTO si hay movimiento.
 * El led indicador se activa indicando que se ha 
 * detectado movimiento.
 */
void sensorMovimiento(struct pt *pt) {
  PT_BEGIN(pt);
  static long t = 0;

  const int delay = 200;
  bool pirState = false;

  pinMode(PIR, INPUT);
  pinMode(LED_BANO, OUTPUT);
  
  while(true){
    pirState = (digitalRead(PIR) == HIGH)? true: false;
    
    if(pirState)
      digitalWrite(LED_BANO, HIGH);
    else
      digitalWrite(LED_BANO, LOW);
    
    t = millis();
    PT_WAIT_WHILE(pt,(millis()-t) < delay);

    PT_YIELD(pt);
  }
  PT_END(pt);
}

void sensorTemperatura(struct pt *pt){

}


/***********************/

void RFID1(struct pt *pt){
  PT_BEGIN(pt);
  static long t = 0;

  while (true){
    // Revisamos si hay nuevas tarjetas  presentes  
  if ( mfrc522.PICC_IsNewCardPresent())
  {  
    
    if ( mfrc522.PICC_ReadCardSerial()){
      
      String uid = obtenerUID(); // Obtenemos el UID de la tarjeta
      
      if(verificarTarjeta(uid))
        accesoPermitido();
      else
        accesoDenegado(); 
    }
  }  

    PT_YIELD(pt);
  }

  PT_END(pt);
};

void RFID2(struct pt *pt){
  PT_BEGIN(pt);
  static long t = 0;

  while (true){
    // Revisamos si hay nuevas tarjetas  presentes  
  if ( mfrc522.PICC_IsNewCardPresent())
  {  
    
    if ( mfrc522.PICC_ReadCardSerial()){
      
      String uid = obtenerUID(); // Obtenemos el UID de la tarjeta
      
      if(verificarTarjeta2(uid))
        accesoPermitido2();
      else
        accesoDenegado2(); 
    }
  }  

    PT_YIELD(pt);
  }

  PT_END(pt);
};

// Enciende el led verde del sensor 1
void accesoPermitido(){
  digitalWrite(LED_V1,HIGH);
  //milis
  digitalWrite(LED_V1,LOW);
}

// Enciende el led rojo del sensor 1
void accesoDenegado(){
  digitalWrite(LED_R1,HIGH);
  //milis
  digitalWrite(LED_R1,LOW);
}

// Enciende el led verde del sensor 2
void accesoPermitido2(){
  digitalWrite(LED_V2,HIGH);
  //milis
  digitalWrite(LED_V2,LOW);
}

// Enciende el led rojo del sensor 2
void accesoDenegado2(){
  digitalWrite(LED_R2,HIGH);
  //milis
  digitalWrite(LED_R2,LOW);
}

// Devuelve el UID de la tarjeta
String obtenerUID(){
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    uid.concat(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    uid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  mfrc522.PICC_HaltA();
  uid.toUpperCase();
  return uid;
}

// Verifica si la tarjeta esta en la base de datos
bool verificarTarjeta(String tarUid){
  
  for(int i = 0; i < bdSize; i++){
    if(tarUid.substring(1) == baseDatos[i])
      return true;
  }
  return false;
}

// Verifica si la tarjeta esta en la base de datos #2
bool verificarTarjeta2(String tarUid){
  
  for(int i = 0; i < bdSize; i++){
    if(tarUid.substring(1) == baseDatos2[i])
      return true;
  }
  return false;
}
