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
  //ss.begin(9600);
  
  //  pinMode(FIST_PIN, OUTPUT);
  //  pinMode(WAVEIN_PIN, OUTPUT);
  //  pinMode(WAVEOUT_PIN, OUTPUT);
  //  pinMode(FINGERSSPREAD_PIN, OUTPUT);
  //  pinMode(DOUBLETAP_PIN, OUTPUT);

  //Serial.begin(115200);

  pinMode(13, OUTPUT);

  myo.initMyo();

      lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("set color");
     lcd.setRGB(110, 0, 110);
  
  //Serial.println("init myo");
  tNow = tPrev = millis();
}


void loop()
{
  //Serial.println("HI");

  tNow = millis();
  if (tNow - tPrev > 1000) {
    tPrev = tNow;
    //Serial.println(".");
  }
  myo.updatePose();
  switch ( myo.getCurrentPose() ) {
    case rest:
      lcd.clear();
      lcd.print("rest");
      //Serial.println("rest");

      //      digitalWrite(FIST_PIN,LOW);
      //      digitalWrite(WAVEIN_PIN,LOW);
      //      digitalWrite(WAVEOUT_PIN,LOW);
      //      digitalWrite(FINGERSSPREAD_PIN,LOW);
      //      digitalWrite(DOUBLETAP_PIN,LOW);
      break;
    case fist:
      lcd.clear();
      lcd.print("fist");
      //Serial.println("fist");
      //digitalWrite(FIST_PIN,HIGH);
      break;
    case waveIn:
      lcd.clear();
      lcd.print("waveIn");
      //Serial.println("waveIn");
      //digitalWrite(WAVEIN_PIN,HIGH);
      break;
    case waveOut:
      lcd.clear();
      lcd.print("waveOut");
      //Serial.println("waveOut");
      //digitalWrite(WAVEOUT_PIN,HIGH);
      break;
    case fingersSpread:
      lcd.clear();
      lcd.print("fingersPressed");
      //Serial.println("fingersPressed");
      //digitalWrite(FINGERSSPREAD_PIN,HIGH);
      break;
    case doubleTap:
      lcd.clear();
      lcd.print("doubleTap");
      //Serial.println("doubleTap");
      //digitalWrite(DOUBLETAP_PIN,HIGH);
      break;
  }
  delay(100);
}
