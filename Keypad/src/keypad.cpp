#include <Wire.h> 
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string>
#include <PasswordManager.hpp>

enum State {
  Checking,
  Setting
};

State state = Checking;
LiquidCrystal_I2C lcd(0x27,16,2);
PasswordManager passwordManager = PasswordManager();

int signalPin = 12;

std::string data;
std::string master = {"12345ABC"};
byte dataCount = 0, masterCount = 0;
bool pass_is_good;
char customKey;

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
  dataCount = 0;
  data = "";
  return;
}

void StoreData(char input){
  dataCount++;
  data += input;
}

char GetData(){
  return data[dataCount - 1];
}

void SwitchState(State newState){
  state = newState;
  clearData();
  lcd.clear();
  lcd.setCursor(0,0);
  String instruction = "~";
  switch (newState)
  {
  case Checking:
    instruction = "Masukkan Sandi:";
    break;
  case Setting:
    instruction = "Sandi Baru:";
    break;
  }
  lcd.print(instruction);
}

int i = 0;

void setup() {
  passwordManager.SetPassword(master);

  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  pinMode(signalPin, OUTPUT);

  SwitchState(Checking);
}

void loop() {
  customKey = customKeypad.getKey();
  if (customKey != NO_KEY){
    
    if (state != Setting && customKey == '*'){
      SwitchState(Setting);
    }
    
    switch (state)
    {
      case Checking:
        StoreData(customKey);
        lcd.setCursor(dataCount - 1,1); 
        lcd.print(GetData()); 
        if(dataCount == master.length()){
          lcd.clear();
          if(passwordManager.CheckPassword(data)){
            lcd.print("Berhasil");
            digitalWrite(signalPin, HIGH); 
            delay(2000);
            digitalWrite(signalPin, LOW);
          }
          else{
            lcd.print("Gagal");
            delay(1000);
          }
          SwitchState(Checking);
        }
        break;
      case Setting:
        if (customKey != '*'){
          StoreData(customKey);
          lcd.setCursor(dataCount - 1,1);
          lcd.print(GetData());
          Serial.print(dataCount);
          if(dataCount >= 8){
            passwordManager.SetPassword(data);
            Serial.print("Sandi Diubah!");
            lcd.clear();
            lcd.print("Sandi Diubah!");
            delay(1000);
            SwitchState(Checking);
          }
        }
        break;
    }
  } 
}