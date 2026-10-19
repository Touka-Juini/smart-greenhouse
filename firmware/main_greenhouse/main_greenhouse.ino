#include <Wire.h> // Include Wire library for I2C communication
#include "rgb_lcd.h" 
#include "DHT.h"
#define  DHTPIN A1
#define  DHTTYPE DHT11
#define  fan1_pin 9
#define  fan2_pin 5
#define  ledpin 8         
#define  ldr_sensor_pin A0        

//pins declaration
const int capteur_tube_pin        = 10;
const int capteur_niveau_bas_pin  = 2 ;
const int capteur_niveau_haut_pin = 3 ;
const int open_pompe              = 7 ; 
const int duree_pompe             = 1000 ;
DHT dht(DHTPIN, DHTTYPE); // constructor to declare our sensor
rgb_lcd lcd             ; //initialiser LCD 
const int lightref = 400; //refference :400<x night and 400>x day
int manualfanspeed = 0  ; // value init for manual fan speed controll
int manualfan2speed = 0 ;
void setup() {
  
  // initialisation des pins 
  pinMode(capteur_tube_pin,INPUT)       ;
  pinMode(capteur_niveau_bas_pin,INPUT) ;
  pinMode(capteur_niveau_haut_pin,INPUT);
  pinMode(open_pompe,OUTPUT);
  digitalWrite(relais_pin,LOW);//inialisation de la pompe a off
  //initialiser le capteur dht11
  Serial.begin(9600);
  dht.begin();
  //inisialiser fans
  pinMode(fan1_pin, OUTPUT);
  pinMode(fan2_pin, OUTPUT);
  // Initialisee LED and light sensor
  pinMode(ledpin, OUTPUT)       ;
  pinMode(ldr_sensor_pin, INPUT);
  //inisialiser LCD
  lcd.begin(16, 2)     ;
  lcd.setRGB(0, 255, 0);//backlight 
  Serial.begin(9600)   ;

}

void loop() {
  // Declare temperature and humidity variables
  float humidity;
  float temperature_en_C;
//systeme circulation de l'eau
int niveau_tube =analogRead(capteur_tube_pin);
Serial.print(niveau_tube); 
        Serial.println();
int niveau_haut =digitalRead(capteur_niveau_haut_pin);
int niveau_bas =digitalRead(capteur_niveau_bas_pin)  ; 

if(niveau_tube < 500){
  if((niveau_haut == 1 && niveau_bas == 1)|| (niveau_haut ==0 && niveau_bas==1)){
    digitalWrite(open_pompe,HIGH);
    delay(duree_pompe);
    digitalWrite(open_pompe,LOW);
  }else{
    lcd.print("citerne vide");
  } 
  delay(300000);//

  //temperature et humidité measurement
  delay(1000);// The DHT11 returns at most one measurement every 1s
  humidity = dht.readHumidity();//Read the moisture content in %
Serial.print(humidity);
        Serial.print(",");
  temperature_en_C = dht.readTemperature();//Read the temperature in degrees Celsius
       Serial.print(temperature_en_C);
        Serial.print(",");
  if (isnan(humidity) || isnan(temperature_en_C)) {
    lcd.print("Failed to read from DHT sensor!");
  } else{
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Temp: ");
    lcd.print(temperature_en_C);
    lcd.print(" C");

    lcd.setCursor(0, 1); 
    lcd.print("Hum: ");
    lcd.print(humidity);
    lcd.print(" %");

      // Send data to the serial monitor 
        
        
         

  }
   
}
if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        if (command.startsWith("FAN_SPEED,")) {
            manualfanspeed = command.substring(10).toInt(); // Extract the speed value
        }else if (command.startsWith("FAN2_SPEED,")) {
            manualfan2speed = command.substring(11).toInt(); // Extract Fan2 speed value
        }
    }

    //speed control
if (manualfanspeed > 0) {
        analogWrite(fan1_pin, map(manualfanspeed, 0, 100, 0, 255)); // Use manual speed
  } else if (temperature_en_C > 35.0) {
    int fanspeed = map(temperature_en_C, 35, 40, 0, 255);
    analogWrite(fan1_pin, fanspeed); // Automatic speed
    } else {
      analogWrite(fan1_pin, 0); // Turn off fan
      }  
  

  //humidity control
  if (manualfan2speed > 0) {
        analogWrite(fan2_pin, map(manualfan2speed, 0, 100, 0, 255)); // Use manual speed
  } else if (humidity > 70) {
    int fanspeed2 = map(humidity, 70, 85, 0, 255); 
    analogWrite(fan2_pin, fanspeed2);  
  } else {
    analogWrite(fan2_pin, 0);  
  }

  // light systeme
    int lightlevel = analogRead(ldr_sensor_pin); 
  
  if (lightlevel < lightref) { 
    digitalWrite(ledpin, HIGH); 
  } else {
    digitalWrite(ledpin, LOW); 
  }

}
