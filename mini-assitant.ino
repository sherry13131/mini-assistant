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
int choice = 0; // for psr game
int pcChoice = 0; // for psr game (pc)
int psrState = 0; // 0:end; 1:win; -1:lost;

time_t t;
int tempBtnState = 0; // also, paper
int gameBtnState = 0; // also, scissor
int dummyBtnState = 0; // also, rock

void setup() { 
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
// Serial.begin(9600);
 setTime(23,33,0,1,1,2019);
 randomSeed(analogRead(0));
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
  int buttonState2 = digitalRead(game_PIN);
  if (buttonState != tempBtnState) {
    if (buttonState == HIGH) {
      state = 1;
      lcd.clear();
    }
    delay(100);
  }
  if (buttonState2 != gameBtnState) {
    if (buttonState2 == HIGH) {
      state = 2;
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
   lcd.print("Humidity: ");
   lcd.print(DHT.humidity);
   delay(2000);
  }
   state = 0;
   lcd.clear();
 }

//rock paper scissor game
 if (state == 2) {
  while(!psrState) {
    psrState = 0;
    // play again
    psrGame();
  }
  psrState = 0;
 }
 
}

void psrGame() {
  psrGameMessage();
  choice = psrUserInput();
  pcChoice = psrPcChoice();
  psrShowChoices();
  psrState = psrResult();
  psrResultMessage();
  psrResetVars();
}

void psrGameMessage() {
  lcd.setCursor(0,0);
  lcd.print("Let's play paper");
  lcd.setCursor(0,1);
  lcd.print("scissor rock!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Let's start xD");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("3!");
  delay(1000);
  lcd.print("2!");
  delay(1000);
}

int psrUserInput() {
  while (!choice) {
  int buttonState = digitalRead(temp_PIN);
  int buttonState2 = digitalRead(game_PIN);
  int buttonState3 = digitalRead(dummy_PIN);
    if (buttonState != tempBtnState) {
      if (buttonState == HIGH) {
        return 1;
      }
    }
    if (buttonState2 != gameBtnState) {
      if (buttonState2 == HIGH) {
        return 2;
      }
    }
    if (buttonState3 != dummyBtnState) {
      if (buttonState3 == HIGH) {
        return 3;
      }
    }
  }
}

void psrShowChoices() {
  lcd.print("1!");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You: ");
  psrInputType(choice);
  lcd.setCursor(0,1);
  lcd.print("Me: ");
  psrInputType(pcChoice);
  delay(2000);
  lcd.clear();
}

void psrInputType(int c) {
  switch (c) {
    case 1:
      lcd.print("paper");
      break;
    case 2:
      lcd.print("scissor");
      break;
    case 3:
      lcd.print("rock");
      break;
    default:
      break;
  }
}

int psrPcChoice() {
  long randNumber;
  randNumber = random(100);
  return randNumber % 3 + 1;
}

int psrResult() {
  if (choice == pcChoice) {
    return 0;
  } else if (((choice == 1) && (pcChoice == 3)) || ((choice == 2) && (pcChoice == 1)) || ((choice == 3) && (pcChoice == 2))) {
    return 1;
  }
  return -1;
}

void psrResultMessage() {
  lcd.setCursor(0,0);
  switch(psrState) {
    case -1:
      lcd.print("You lose T.T");
      break;
    case 1:
      lcd.print("You win >w<");
      break;
    case 0:
      lcd.print("Tie...");
      lcd.print("So again...");
      break;
  }
  delay(2000);
}

void psrResetVars() {
  choice = 0;
  pcChoice = 0;
  state = 0;
  lcd.clear();
}
