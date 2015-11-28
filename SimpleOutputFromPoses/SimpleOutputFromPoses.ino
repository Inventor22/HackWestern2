#include <MyoController.h>

#define FIST_PIN 4
#define WAVEIN_PIN 5
#define WAVEOUT_PIN 6
#define FINGERSSPREAD_PIN 7
#define DOUBLETAP_PIN 8

MyoController myo = MyoController();

int pin = 13;

uint32_t tNow, tPrev;

void setup() {

  //  pinMode(FIST_PIN, OUTPUT);
  //  pinMode(WAVEIN_PIN, OUTPUT);
  //  pinMode(WAVEOUT_PIN, OUTPUT);
  //  pinMode(FINGERSSPREAD_PIN, OUTPUT);
  //  pinMode(DOUBLETAP_PIN, OUTPUT);

  //Serial.begin(115200);

  pinMode(13, OUTPUT);

  myo.initMyo();
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
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      delay(1000);
      //Serial.println("rest");

      //      digitalWrite(FIST_PIN,LOW);
      //      digitalWrite(WAVEIN_PIN,LOW);
      //      digitalWrite(WAVEOUT_PIN,LOW);
      //      digitalWrite(FINGERSSPREAD_PIN,LOW);
      //      digitalWrite(DOUBLETAP_PIN,LOW);
      break;
    case fist:
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      delay(1000);
      //Serial.println("first");
      //digitalWrite(FIST_PIN,HIGH);
      break;
    case waveIn:
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      delay(1000);
      //Serial.println("waveIn");
      //digitalWrite(WAVEIN_PIN,HIGH);
      break;
    case waveOut:
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      delay(1000);
      //Serial.println("waveOut");
      //digitalWrite(WAVEOUT_PIN,HIGH);
      break;
    case fingersSpread:
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      delay(1000);
      //Serial.println("fingersPressed");
      //digitalWrite(FINGERSSPREAD_PIN,HIGH);
      break;
    case doubleTap:
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      delay(1000);
      //Serial.println("doubleTap");
      //digitalWrite(DOUBLETAP_PIN,HIGH);
      break;
  }
  delay(100);
}
