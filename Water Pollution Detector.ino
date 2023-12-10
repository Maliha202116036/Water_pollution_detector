#include <EEPROM.h>
#include "GravityTDS.h"
#include <LiquidCrystal.h>
#include <Servo.h>
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
#define TdsSensorPin A0
#define LED_PIN1 8
#define LED_PIN2 9
#define LED_PIN3 10
GravityTDS gravityTds;

#include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x27, 16, 2);
float calibration_value = 21.34;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

// Declare the Servo pin 
int servoPin = 13; 
// Create a servo object 
Servo Servo1; 
 
float temperature = 25,tdsValue = 0;
 
void setup()
{
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);
    pinMode(LED_PIN3, OUTPUT);
    Serial.begin(9600);
    lcd.begin(16,2);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
    Servo1.attach(servoPin); 
    
}
 
void loop()
{
    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    // Serial.print(tdsValue,0);
    // Serial.println("ppm");
    lcd.setCursor(0, 0);
    lcd.print("TDS Value:");
    lcd.setCursor(0, 1);
    lcd.print(tdsValue,0);
    lcd.print(" PPM");
    delay(1000);
    // lcd.clear();
    if (tdsValue>=45 && tdsValue<150){
      digitalWrite(LED_PIN1, HIGH);
      digitalWrite(LED_PIN2, LOW);
      digitalWrite(LED_PIN3, LOW);
      Servo1.write(0);
    } else if (tdsValue>=150 && tdsValue<=220){
      digitalWrite(LED_PIN2, HIGH);
      digitalWrite(LED_PIN3, LOW);
      digitalWrite(LED_PIN1, LOW);
      Servo1.write(0);
    }else if (tdsValue >220){
      digitalWrite(LED_PIN3, HIGH);
      digitalWrite(LED_PIN2, LOW);
      digitalWrite(LED_PIN1, LOW);
      Servo1.write(90);
    }else{
      digitalWrite(LED_PIN1, LOW);
      digitalWrite(LED_PIN2, LOW);
      digitalWrite(LED_PIN3, LOW);
      Servo1.write(0);
    }


    //pH meter
      
//  lcd.setCursor(0, 0);
//  lcd.print("pH Val:");
//  lcd.setCursor(8, 0);
//  lcd.print(ph_act);
    Serial.print(ph_act,0);
    Serial.println("pH");

    delay(1000);
}