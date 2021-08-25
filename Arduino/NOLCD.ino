#include <SD.h>
File myFile;
#include <Wire.h>

  
const int chipSelect = 10;//буфер
char dataString [64];  

int button_pin = 3;     // пин кнопки

int led_errCard = 7; //ошибка карты
int led_CardOn = 8; //карта исправна, запись данных доступна
int led_DataCard = 9; //данные записаны на карту

int led_BTON = 6; //данные записаны на телефона через Bluetooth
int led_BTerr = 5; //ошибка Bluetooth 

int analogInput1 = 0;
int analogInput2 = 1;
float vout = 0.0;
float vin = 0.0;
float R1 = 39500.0; // сопротивление R1 (100K)
float R2 = 10800.0; // сопротивление R2 (10K)
int value = 0;

void setup() { 

analogReference(INTERNAL);
Serial.begin(9600);
 
pinMode(led_errCard, OUTPUT); // Инициализируем цифровой вход/выход в режиме выхода.
pinMode(led_CardOn, OUTPUT);
pinMode(led_DataCard, OUTPUT);
pinMode(led_BTON, OUTPUT);
pinMode(led_BTerr, OUTPUT);

pinMode(button_pin, INPUT); // Инициализируем цифровой вход/выход в режиме входа.

pinMode(chipSelect, OUTPUT);

pinMode(analogInput1, INPUT); 
pinMode(analogInput2, INPUT); 

Serial.println("Initializing Card");//Initializing Card
    if (!SD.begin(chipSelect)) {
      Serial.println("Card Failure");//Card Failure
      digitalWrite(led_errCard, HIGH);
      delay(500);
      digitalWrite(led_errCard, LOW);
      delay(500);
      digitalWrite(led_errCard, HIGH);
      delay(500);
      digitalWrite(led_errCard, LOW);
      delay(500);
      return;
  }
  else {
      digitalWrite(led_CardOn, HIGH);
      delay(500);
      digitalWrite(led_CardOn, LOW);
      delay(500);
      digitalWrite(led_CardOn, HIGH);
      delay(500);
      digitalWrite(led_CardOn, LOW);
      delay(500);
  }
  Serial.println("Card Ready");//Card Ready
      if (Serial.available()=="i") {
        digitalWrite(led_BTON, HIGH);
        delay(1000);
        digitalWrite(led_BTON, LOW);
        delay(1000);
      }     

}
void loop() {
  {
  vin = (((analogRead(analogInput2)-analogRead(analogInput1)) * 1.1) / 1024.0 )/ (R2/(R1+R2)); 
      //vin = ((analogRead(analogInput1) * 1.1) / 1024.0 )/ (R2/(R1+R2));
      if ((digitalRead(button_pin) == HIGH)&&SD.begin(chipSelect)) { // Если кнопка нажата 
      digitalWrite(led_DataCard, HIGH);
      delay(500);
      digitalWrite(led_DataCard, LOW);
      delay(500);
      Serial.println(vin);
      
      File myFile = SD.open("log.xls", FILE_WRITE);
      if (myFile)
      {
        myFile.println(vin);
        myFile.close();
        delay(1000);
        //Serial.println(vin);

        while (Serial.available()>0) {
        digitalWrite(led_BTON, HIGH);
        delay(500);
        digitalWrite(led_BTON, LOW);
        delay(500);
        }
        while (Serial.available()<-1) {
        digitalWrite(led_BTerr, HIGH);
        delay(500);
        digitalWrite(led_BTerr, LOW);
        delay(500);
        }
      }
 }
  else if ((digitalRead(button_pin) == HIGH)&&!SD.begin(chipSelect)){ //Иначе
      digitalWrite(led_errCard, HIGH);
      delay(500);
      digitalWrite(led_errCard, LOW);
      delay(500); 
  }
  
}
}
