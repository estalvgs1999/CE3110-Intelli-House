//Bases de Arduino Clase #7 - Ejercicio 11 - David Alvarado

//Incluír librerías
#include <LiquidCrystal.h>
#include <SimpleDHT.h>

//Definición de pines
//Sensor DHT11
#define PinSensor 41
//LDC
#define RS 53
#define E  51
#define D4 49
#define D5 47
#define D6 45
#define D7 43

//Creación de objetos
SimpleDHT11 Sensor(PinSensor);              //Objeto DHT11
LiquidCrystal led(RS, E, D4, D5, D6, D7);   //Obejeto LCD

//Declaración de variables
byte Temp = 0;
byte Hum = 0;

//Cofiguración inicial
void setup(){
    led.begin(16,2);
}

//Propragama Principal
void loop(){
    led.setCursor(0,0);
    Sensor.read(&Temp, &Hum, NULL);
    led.print("Temperatura: ");
    led.print(int(Temp));
    led.print(" C°, ");
    led.setCursor(0,1);
    led.print("Humedad: ");
    led.print(int(Hum));
    led.println(" %");
    delay(1100);
}