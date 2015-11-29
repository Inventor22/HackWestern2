#include <Wire.h>
#include "rgb_lcd.h"
#include <SoftwareSerial.h>

#include <MyoController.h>

#define FIST_PIN 4
#define WAVEIN_PIN 5
#define WAVEOUT_PIN 6
#define FINGERSSPREAD_PIN 7
#define DOUBLETAP_PIN 8

SoftwareSerial ss(2, 3); // rx, tx

MyoController myo = MyoController(ss);



rgb_lcd lcd;

int pin = 13;

uint32_t tNow, tPrev;

void setup() {

  myo.initMyo();

  lcd.begin(16, 2);
  lcd.print("set color");
  lcd.setRGB(110, 0, 110);

  printMyoData();
  //Serial.println("init myo");
  tNow = tPrev = millis();
}

void printMyoData() {
  lcd.clear();
  lcd.print("R:");
  lcd.print(myo.roll);
  lcd.print(" P:");
  lcd.print(myo.pitch);
  lcd.print(" H:");
  lcd.print(myo.throwHammer);
}

void loop()
{
  if (myo.updateData()) {
    printMyoData();
    tNow = millis();
    lcd.setCursor(0, 1);
    lcd.print(tNow - tPrev);
    tPrev = tNow;

//        lcd.clear();
//    lcd.print(sizeof(myo.msgChar));
//    lcd.print(" ");
//    lcd.print(myo.msgChar[0]); // 'S'
//    lcd.print(" ");
//    lcd.print(myo.msgChar[1], DEC); // turn
//    lcd.print(" ");
//    lcd.print(myo.msgChar[2], DEC); // forward/backward
//    lcd.print(" ");
//    lcd.print(myo.msgChar[3], DEC); // hammer
//    lcd.print(" ");
//    lcd.print(myo.msgChar[4]); // '!'
//    lcd.print(" ");
//    lcd.print(myo.msgChar[5], DEC); // newline?
  }



}


