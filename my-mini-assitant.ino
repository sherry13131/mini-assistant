/*
* Arduino LCD Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

#include <dht.h>
#include <TimeLib.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 3, 4, 5, 6); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
#define DHT11_PIN 7
#define temp_PIN 8
#define game_PIN 9
#define dummy_PIN 10

dht DHT;
int state = -1; // 0:main menu; 1:temp&humd; 2:psr game
time_t t;
int tempBtnState = 0;
int gameBtnState = 0;
int dummyBtnState = 0;

void setup() { 
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
// Serial.begin(9600);
 setTime(23,33,0,1,1,2019);
}

void loop() {
//  welcome message
 if (state == -1) {
    lcd.setCursor(0,0);
    lcd.print("Hello!");
    delay(1000);
    lcd.setCursor(0,3);
    lcd.print("Sherry xD");
    delay(3000);
    state = 0;
    lcd.clear();
 }

// main menu
 if (state == 0) {
  lcd.setCursor(0,0);
  lcd.print("What can I help");
  lcd.setCursor(0,1);
  lcd.print("you?");
  lcd.setCursor(8,1);
  t = now();
  lcd.print(hour(t));
  lcd.print(":");
  lcd.print(minute(t));
  lcd.print(":");
  lcd.print(second(t));
  int buttonState = digitalRead(temp_PIN);
  if (buttonState != tempBtnState) {
    if (buttonState == HIGH) {
      state = 1;
      lcd.clear();
    }
    delay(100);
  }
 }

// temp and humidity
 if (state == 1) {
  for (int i = 0; i<5; i++) {
   DHT.read11(DHT11_PIN);
   lcd.setCursor(0,0);
   lcd.print("Temp: ");
   lcd.print(DHT.temperature);
   lcd.setCursor(0,1);
   lcd.print("humd: ");
   lcd.print(DHT.humidity);
   delay(2000);
  }
   state = 0;
   lcd.clear();
 }
}
