//Bibliotecas
#include <Servo.h>
#include <SimpleDHT.h>
#include <pt.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

// Sensores
#define LDR A0
#define HC_TRIGGER 48
#define HC_ECHO 49
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

//Base de datos
String baseDatos[] = {"C7 52 6B 63","A9 A0 8B C1"};
int bdSize = sizeof(baseDatos)/sizeof(String);

// Crear nuestros OBJETOS
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Hilos
struct pt procesoA;
struct pt procesoB;
struct pt procesoC;
struct pt procesoD;


void setup(){
  PT_INIT(&procesoA);
  PT_INIT(&procesoB);

  Serial.begin(9600);
  
  SPI.begin();
  mfrc522.PCD_Init();
}


void loop(){
  fotosensor(&procesoA);
  sensorMovimiento(&procesoB);
}

/**
 * Sensor LDR. 
 * Si el valor de la lectura es menor que el de un valor
 * límite (indica oscuridad) enciende la iluminación. 
 */
void fotosensor(struct pt *pt){
  PT_BEGIN(pt);
  
  int valor;
  const int valorLimite = 200;

  pinMode(LED_PATIO, HIGH);

  while(true){
    digitalWrite(LED_PATIO, LOW);
    
    valor = analogRead(LDR);
    if(valor < valorLimite)
      digitalWrite(LED_PATIO, HIGH);
    
    delayMillis(&pt, 200);

    PT_YIELD(pt);
  }
  PT_END(pt);
}

void sensorDistancia(struct pt *pt){

}

/**
 * Sensor PIR.
 * El sensor genera un señal ALTO si hay movimiento.
 * El led indicador se activa indicando que se ha detectado
 * movimiento.
 */
void sensorMovimiento(struct pt *pt) {
  PT_BEGIN(pt);
  bool pirState = false;

  pinMode(PIR, INPUT);
  pinMode(LED_BANO, OUTPUT);
  
  while(true){
    pirState = (digitalRead(PIR) == HIGH)? true: false;
    
    if(pirState)
      digitalWrite(LED_BANO, HIGH);
    else
      digitalWrite(LED_BANO, LOW);
    
    delayMillis(&pt, 200);

    PT_YIELD(pt);
  }
  PT_END(pt);
}

void sensorTemperatura(struct pt *pt){

}

/**
 * Delay Personalizado.
 * Realiza la función del delay adaptado al uso de protothreads
 */
void delayMillis(struct pt *pt, int delay){
  static long t = millis();
  PT_WAIT_WHILE(pt,(millis()-t) < delay);
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
      
      if(verificarTarjeta(uid))
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
