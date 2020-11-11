#include <distanceSensor.h>
#include <photosensor.h>

//Bibliotecas
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

//Bases de datos
String baseDatos[] = {"C7 52 6B 63","A9 A0 8B C1"};
int bdSize = sizeof(baseDatos)/sizeof(String);
String baseDatos2[] = {"C7 52 6B 63","A9 A0 8B C1","96 0E 03 4B","D0 54 39 45"};
int bdSize2 = sizeof(baseDatos2)/sizeof(String);

// Creación de Objetos
MFRC522 mfrc522(SS_PIN, RST_PIN);
SimpleDHT11 Sensor(DHT);
Photosensor photosensor(LDR, LED_PATIO);
DistanceSensor distanceSensor(HC_TRIGGER,HC_ECHO,SERVO_GARAGE);

// Setup
void setup(){
  
  Serial.begin(9600);
}

// Loop
void loop(){
 photosensor.run();
 distanceSensor.run();
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
  static long t = 0;
  const int delay_us = 10; // 10 microsegundos  
  const int limite = 100; // 15 cm
  int distancia;
  int tiempo;
  
  pinMode(HC_ECHO, INPUT);
  pinMode(HC_TRIGGER, OUTPUT);
  
  while(true){

    digitalWrite(HC_TRIGGER, LOW);
    t = micros();
    PT_WAIT_WHILE(pt,(micros()-t) < 10);
    digitalWrite(HC_TRIGGER, HIGH);
    t = micros();
    PT_WAIT_WHILE(pt,(micros()-t) < 10);
    digitalWrite(HC_TRIGGER, LOW);

    tiempo = 1;
    distancia = tiempo/59;
    
    Serial.print("Distancia = ");
    Serial.print(distancia);
    Serial.println(" cm");
    
 
    PT_YIELD(pt);
  }

  PT_END(pt);
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
  PT_BEGIN(pt);
  static long t = 0;
  byte Temp = 0;
  byte Hum = 0;

  while(true){

    Serial.println("Datos Sensor DHT11");
    Sensor.read(&Temp, &Hum, NULL);
    Serial.print("Temperatura: ");
    Serial.print(int(Temp));
    Serial.print(" C°, ");
    delay(1000);
    
    PT_YIELD(pt);
  }
  PT_END(pt);
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
    }
  }  

    PT_YIELD(pt);
  }

  PT_END(pt);
};

// Enciende el led verde del sensor 1
void accesoPermitido(){
  //Lo hará después
  //milis
}

// Enciende el led verde del sensor 2
void accesoPermitido2(){
  //Lo hará después
  //milis
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
