#include <SoftwareSerial.h>

#include <Servo.h>

int pinMotorA1 = 4;
int pinMotorB1 = 2;
int pinMotor1 = 5;
int pinMotorA2 = 12;
int pinMotorB2 = 13;
int pinMotor2 = 11;
int pinMotorA3 = A1;
int pinMotorB3 = A2;
int pinMotor3 = 3;
int pinMotorA4 = 8;
int pinMotorB4 = 7;
int pinMotor4 = 6;

uint32_t tNow, tPrev, tThrown;
const int posHammerUp = 80;
const int posHammerDown = 130;
bool reloadHammer = false;

int msgCount = 0;

int pinHammer = 10;

const int maxSpeed = 150;

int speed, turn, hammerState;

enum MoveState {
  LB,
  RB,
  LF,
  RF,
  S
};

SoftwareSerial ss(A4, A3); //rx tx

//Data coming from Myo
char det;
char  determinant;
char info;
char data[4];

String storageStr;
String msgChar;

Servo hammer;

void setup() {

  Serial.begin(115200);
  ss.begin(9600);

  Serial.println("Hello World");

  hammer.attach(pinHammer);
  hammer.write(posHammerUp);

  pinMode(pinMotorA1, OUTPUT);
  pinMode(pinMotorB1, OUTPUT);
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotorA2, OUTPUT);
  pinMode(pinMotorB2, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotorA3, OUTPUT);
  pinMode(pinMotorB3, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotorA4, OUTPUT);
  pinMode(pinMotorB4, OUTPUT);
  pinMode(pinMotor4, OUTPUT);

}

void loop() {
  if (checkForData()) {
    Move();
  }
  
  tNow = millis();

  if (!reloadHammer && tNow - tPrev > 1000) {
    hammer.write(posHammerUp);
    reloadHammer = true;
  }
}

bool checkForData() {
  if (ss.available())
  {
    byte firstByte = ss.read();
    if (firstByte == 'S') {
      storageStr = String("S");
      int i = 0;
      while (ss.available() && i < 5)
      {
        storageStr = storageStr + char(ss.read());
        i++;
        delay(1);
      }

      msgChar = storageStr;
      //serial.print(msgChar);

      if (msgChar[0] == 'S' && msgChar[4] == '!') {
        byte roll = msgChar[1];
        turn = roll - 51;// - 100;

        byte pitch = msgChar[2];
        speed = pitch - 51;// - 100;
        //roll  = (int8_t)(((int) msgChar[1]) - 100);
        //pitch = (int8_t)(((int) msgChar[2]) - 100);
        hammerState = msgChar[3] == '1';

        Serial.print(msgCount);
        Serial.print(": T:");
        Serial.print(turn, DEC);
        Serial.print(", S:");
        Serial.print(speed, DEC);
        Serial.print(", Hammer:");
        Serial.println(hammerState);

        return true;
      }
      else {
        return false;
      }
    }
  }
  else {
    return false;
  }
}

void Move() {
  if (speed < 0) {
    digitalWrite(pinMotorA1, LOW);
    digitalWrite(pinMotorB1, HIGH);

    digitalWrite(pinMotorA2, LOW);
    digitalWrite(pinMotorB2, HIGH);

    digitalWrite(pinMotorA3, LOW);
    digitalWrite(pinMotorB3, HIGH);

    digitalWrite(pinMotorA4, LOW);
    digitalWrite(pinMotorB4, HIGH);
  }
  else if (speed > 0) {
    digitalWrite(pinMotorA1, HIGH);
    digitalWrite(pinMotorB1, LOW);

    digitalWrite(pinMotorA2, HIGH);
    digitalWrite(pinMotorB2, LOW);

    digitalWrite(pinMotorA3, HIGH);
    digitalWrite(pinMotorB3, LOW);

    digitalWrite(pinMotorA4, HIGH);
    digitalWrite(pinMotorB4, LOW);
  }

  if (speed == 0) {
    digitalWrite(pinMotorA1, LOW);
    digitalWrite(pinMotorB1, HIGH);
    analogWrite(pinMotor1, 0);

    digitalWrite(pinMotorA2, LOW);
    digitalWrite(pinMotorB2, HIGH);
    analogWrite(pinMotor2, 0);

    digitalWrite(pinMotorA3, LOW);
    digitalWrite(pinMotorB3, HIGH);
    analogWrite(pinMotor3, 0);

    digitalWrite(pinMotorA4, LOW);
    digitalWrite(pinMotorB4, HIGH);
    analogWrite(pinMotor4, 0);
  }
  else {
    int mappedSpeed = map(abs(speed), 0, 50, 0, maxSpeed);

    if (turn == 0) {
      analogWrite(pinMotor1, mappedSpeed);
      analogWrite(pinMotor2, mappedSpeed);
      analogWrite(pinMotor3, mappedSpeed);
      analogWrite(pinMotor4, mappedSpeed);

      //Serial.println(mappedSpeed);
    }
    else {
      int slowerWheel = mappedSpeed * (50 - abs(turn)) / 50;

      if (turn < 0) {
        analogWrite(pinMotor1, slowerWheel);
        analogWrite(pinMotor2, slowerWheel);
        analogWrite(pinMotor3, mappedSpeed);
        analogWrite(pinMotor4, mappedSpeed);
      }
      else {
        analogWrite(pinMotor1, mappedSpeed);
        analogWrite(pinMotor2, mappedSpeed);
        analogWrite(pinMotor3, slowerWheel);
        analogWrite(pinMotor4, slowerWheel);
      }
    }
  }
  
    tNow = millis();
    if (hammerState && tNow - tPrev > 3000) {
      hammer.write(posHammerDown);
      tPrev = tNow;
      hammerState = false;
      reloadHammer = false;
    }
}
