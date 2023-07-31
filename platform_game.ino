#include <Wire.h>
#include <LiquidCrystal.h>  

LiquidCrystal lcd(7,8,9,10,11,12);
#define buttonPin  2

byte block[8] = {
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110
};

byte char1[8] = {
  0b01110,
  0b01110,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010,
  0b01010
};

byte hit[8] = {

  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10101,
  0b11111,
  0b01110,
  0b00100
};
byte char2[8]={
  0b01110,
  0b01110,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00100
};

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

int blocks[16];
int chary = 2;
int charx = 7;
int score = 0;
int speedlvl = 400;

int life = 5;

void setup() {
  lcd.begin(16, 2);  
  Serial.begin (9600);
  
  randomSeed(analogRead(0));
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  int i = 0;
  for (i = 0; i<16; i++) {
    blocks[i] = 0;
  }
 
  //lcd.begin();

  lcd.createChar(0, block);
  lcd.createChar(1, char1);
  lcd.createChar(2, hit);
  lcd.createChar(3, heart);
  lcd.createChar(4, char2);
 
}
//moves character reading the digital input of button
void charmove() {
  int buttonValue = digitalRead(buttonPin);
  int charId = 0;
  int deltime = 150;
  
  if (buttonValue == LOW) {
    chary = 0;
    charId = 1;
  } else {
    chary = 1;
    charId = 1;
    if (blocks[charx] == 1) {
      charId = 2;
      life--;
      score--;
      deltime = 300;
    }
  }
  
  lcd.setCursor(charx, chary);
  lcd.write((byte)charId);
  delay(deltime);
  lcd.setCursor(charx, chary);
  lcd.write((byte)4);
}

//moves blocks
void moveblock() {
  int dist = random(1, 3);

  int i;
  for (i=1; i<16; i++) {
    blocks[i-1] = blocks[i];
  }
  
  if (dist == 1 && (blocks[16] == 2 || blocks[13] == 1)) {
      blocks[15] = 0;
  } else {
     blocks[15] = random(0, 2);
  }
    
  for (i = 0; i<16; i++) {
    if (blocks[i] != 0) {
      lcd.setCursor(i, 1);
      lcd.write((byte)0);
    }
  }

}


void showLives() {
  int i;
  for (i=0; i<life; i++) {
    lcd.setCursor(i, 0);
    lcd.write((byte)3);
  }
}

void showScore() {
  lcd.setCursor(13,0);
  lcd.print(score);
}

void loop() {
  lcd.clear();
  
  if (life > 0) {
    moveblock();
    charmove();
    showLives();
    showScore();
    score++;
    speedlvl--;    
  } else {
    lcd.setCursor(3, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(3, 1);
    lcd.print("Score: ");
    lcd.print(score);
  }

  delay(speedlvl); 

}