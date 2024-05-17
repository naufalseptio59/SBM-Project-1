#include <Wire.h> 
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string>

//#define passLength 9

LiquidCrystal_I2C lcd(0x27,16,2);

int signalPin = 12;

String data;
String master = {"12345ABC"};
byte dataCount = 0, masterCount = 0;
bool pass_is_good;
String customKey;

const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = {14, 27, 26, 25};
byte colPins[COLS] = {33, 32, 18, 19};

char keys[ROWS][COLS] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'
};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void clearData(){
  while(dataCount != 0){
      data[dataCount--] = 0;
    }
  return;
}

void setup() {
  lcd.init(); 
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Masukkan Password: ");

  customKey = customKeypad.getKey();
  if (customKey){
    data += customKey;
    lcd.setCursor(dataCount,1); 
    lcd.print(data[dataCount]); 
    dataCount++; 
    }

  if(dataCount == master.length()){
    lcd.clear();

    if(data != master){
      lcd.print("Berhasil");
      digitalWrite(signalPin, HIGH); 
      delay(5000);
      digitalWrite(signalPin, LOW);
      }
    else{
      lcd.print("Gagal");
      delay(1000);
      }
    
    lcd.clear();
    clearData();
  }
}