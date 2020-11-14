/*
 

 */

// Bibliotecas
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Declaracion de variables
#define RST_PIN  5    //Pin 5 para el reset del RC522
#define SS_PIN  53    //Pin 53 para el SS (SDA) del RC522
#define LED_A 22      //Definimos el pin LED amarillo
#define LED_R 23      //Definimos el pin LED rojo
#define SERVO_PRIN 8  //Definimos el pin PWM del Servo de la puerta principal
#define SERVO_ROOM 9  //Definimos el pin PWM del Servo de la puerta del cuarto

#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

String baseDatos[] = {"C7 52 6B 63","A9 A0 8B C1","D0 54 39 45","96 0E 03 4B"};
int bdSize = sizeof(baseDatos)/sizeof(String);

// Crear nuestros OBJETOS
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
Servo servoPrin, servoRoom;

void setup() {

  Serial.begin(9600); //Iniciamos la comunicación  serial
  
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  
  pinMode(LED_A, OUTPUT);
  pinMode(LED_R, OUTPUT);

  servoPrin.attach(SERVO_PRIN);
  servoPrin.write(0);
  servoRoom.attach(SERVO_ROOM);
  servoRoom.write(0);
}

void loop()
{
  // Revisamos si hay nuevas tarjetas  presentes  
  if ( mfrc522.PICC_IsNewCardPresent()){  
    if ( mfrc522.PICC_ReadCardSerial()){

      String uid = obtenerUID(); // Obtenemos el UID de la tarjeta
      
      if(verificarTarjeta(uid)){
        if(uid.substring(1) == "C7 52 6B 63" || uid.substring(1) =="A9 A0 8B C1"){
          accesoPermitido2();
          return;
        }
        if(uid.substring(1) == "D0 54 39 45" || uid.substring(1) =="96 0E 03 4B"){
          accesoPermitido();
          return;
        }
     }
    }
  } 
}

// Enciende el led amarilla
void accesoPermitido(){
  digitalWrite(LED_A,HIGH);
  servoPrin.write(90);
  delay(ACCESS_DELAY);
  digitalWrite(LED_A,LOW);
  servoPrin.write(0);
}

// Enciende el led Rojo
void accesoPermitido2(){
  digitalWrite(LED_R,HIGH);
  servoRoom.write(90);
  delay(ACCESS_DELAY);
  digitalWrite(LED_R,LOW);
  servoRoom.write(0);
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
