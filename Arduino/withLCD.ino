#include <LiquidCrystal_I2C.h>
#include <SD.h>
File myFile;
#include <Wire.h>
LiquidCrystal_I2C LCD(0x3F, 16, 2); // Устанавливаем дисплей


const int chipSelect = 10;//буфер
//char dataString [64];
String KM = "";
boolean Flag;

int led_pin = 3;        // пин подключения
int button_pin = 4;     // пин кнопки

int analogInput1 = 0;
int analogInput2 = 1;
float vout = 0.0;
float vin = 0.0;
float R1 = 38800.0; // сопротивление R1 (100K)
float R2 = 11200.0; // сопротивление R2 (10K)
int value = 0;

void setup() {

  LCD.init(); // инициализация LCD дисплея
  LCD.backlight(); // включение подсветки дисплея
  analogReference(INTERNAL);
  Serial.begin(9600);

  pinMode(led_pin, OUTPUT); // Инициализируем цифровой вход/выход в режиме выхода.
  pinMode(button_pin, INPUT); // Инициализируем цифровой вход/выход в режиме входа.
  pinMode(chipSelect, OUTPUT);
  pinMode(analogInput1, INPUT);
  pinMode(analogInput2, INPUT);
  Serial.println("Initializing Card");//Initializing Card
  if (!SD.begin(chipSelect)) {
    Serial.println("Card Failure");//Card Failure
    LCD.print("CARD FAILURE");
    return;
  }
  else {
    LCD.print("Card Ready");
  }
  Serial.println("Card Ready");//Card Ready


}
void loop() {
  {
    vin = (((analogRead(analogInput2) - analogRead(analogInput1)) * 1.1) / 1024.0 ) / (R2 / (R1 + R2));
    //vin = ((analogRead(analogInput1) * 1.1) / 1024.0 )/ (R2/(R1+R2));
    if ((digitalRead(button_pin) == HIGH) && SD.begin(chipSelect)) { // Если кнопка нажата
      digitalWrite(led_pin, HIGH);
      delay(500);
      digitalWrite(led_pin, LOW);
      delay(500);// зажигаем светодиод
      File myFile = SD.open("log.xls", FILE_WRITE);
      if (myFile)
      {
        myFile.println(vin);
        LCD.setCursor(0, 0);
        LCD.print("Saved!      ");
        myFile.close();
        delay(1000);
        LCD.setCursor(0, 0);
        LCD.print("Ready      ");
        
        while (Serial.available()>0) {
          KM += (char)Serial.read();
          Flag = true;
          delay(2);
          //LCD.setCursor(0, 1);
          //LCD.print(Serial.read());
        }
        if (Flag){
          LCD.setCursor(0, 1);
          LCD.print(KM);
          KM = "";
          Flag = false;         
          }
        // LCD.setCursor(0, 1);
        // LCD.print(vin);
        Serial.println(vin);
      }

    }
    else if ((digitalRead(button_pin) == HIGH) && !SD.begin(chipSelect)) { //Иначе
      LCD.setCursor(0, 0);
      LCD.print("CARD MISSING");
      Serial.println(vin);
              while (Serial.available()>0) {
          KM += (char)Serial.read();
          Flag = true;
          delay(2);
          //LCD.setCursor(0, 1);
          //LCD.print(Serial.read());
        }
        if (Flag){
          LCD.setCursor(0, 1);
          LCD.print(KM);
          KM = "";
          Flag = false;         
          }
    }

    LCD.setCursor(9, 1);
    LCD.print("V=");
    LCD.print(vin);
    delay(300);
  }
}
