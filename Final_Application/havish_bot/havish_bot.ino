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



enum MoveState {
  LB,
  RB,
  LF,
  RF,
  S
};


//Data coming from Myo
char det;
char  determinant;
char info;
char data[4];

void setup() {

  Serial.begin(9600);

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

int i = 0;
void loop() {
  if (Serial.available() > 0) {
    info = Serial.read();
    data[i] = info;
    //Serial.println(data[i]);
    i++;
    if (info == '!') {
      Move();
    }
  }
}

void Move() {

  if (data[0] == 'S') {
    Serial.println(data[0]);
    if (data[1] < 51) { //turning left
      if (data[2] < 51) { //backwards
        det = LB; //left back
      }
      if (data[2] > 50) { //forwards
        det = LF; //left forward
      }
    }

    if (data[1] > 50) { //turning right
      if (data[2] < 51) { //backwards
        det = RB; //right back
      }
      if (data[2] > 50) { //forwards
        det = RF; //right forward
        Serial.println("Forward Right");
      }
    }
  }

  int V = map(abs(data[2]), 0, 100, 0, 255);

  //det= check();
  switch (det) {
    case LF: { //left forwards
        digitalWrite(pinMotorA1, HIGH);
        digitalWrite(pinMotorB1, LOW);
        analogWrite(pinMotor1, V / 2);
        digitalWrite(pinMotorA2, HIGH);
        digitalWrite(pinMotorB2, LOW);
        analogWrite(pinMotor2, V / 2);
        digitalWrite(pinMotorA3, HIGH);
        digitalWrite(pinMotorB3, LOW);
        analogWrite(pinMotor3, V);
        digitalWrite(pinMotorA4, HIGH);
        digitalWrite(pinMotorB4, LOW);
        analogWrite(pinMotor4, V);
        break;
      }

    case LB: { //LEFT BACK
        digitalWrite(pinMotorA1, LOW);
        digitalWrite(pinMotorB1, HIGH);
        analogWrite(pinMotor1, V);
        digitalWrite(pinMotorA2, LOW);
        digitalWrite(pinMotorB2, HIGH);
        analogWrite(pinMotor2, V);
        digitalWrite(pinMotorA3, LOW);
        digitalWrite(pinMotorB3, HIGH);
        analogWrite(pinMotor3, V / 2);
        digitalWrite(pinMotorA4, LOW);
        digitalWrite(pinMotorB4, HIGH);
        analogWrite(pinMotor4, V / 2);
        break;
      }

    case RF: { //RIGHT forward
        digitalWrite(pinMotorA1, HIGH);
        digitalWrite(pinMotorB1, LOW);
        analogWrite(pinMotor1, V);
        digitalWrite(pinMotorA2, HIGH);
        digitalWrite(pinMotorB2, LOW);
        analogWrite(pinMotor2, V);
        digitalWrite(pinMotorA3, HIGH);
        digitalWrite(pinMotorB3, LOW);
        analogWrite(pinMotor3, V / 2);
        digitalWrite(pinMotorA4, HIGH);
        digitalWrite(pinMotorB4, LOW);
        analogWrite(pinMotor4, V / 2);
        break;
      }

    case RB: { //RIGHT BACK
        digitalWrite(pinMotorA1, LOW);
        digitalWrite(pinMotorB1, HIGH);
        analogWrite(pinMotor1, V / 2);
        digitalWrite(pinMotorA2, LOW);
        digitalWrite(pinMotorB2, HIGH);
        analogWrite(pinMotor2, V / 2);
        digitalWrite(pinMotorA3, LOW);
        digitalWrite(pinMotorB3, HIGH);
        analogWrite(pinMotor3, V);
        digitalWrite(pinMotorA4, LOW);
        digitalWrite(pinMotorB4, HIGH);
        analogWrite(pinMotor4, V);
        break;
      }

    case S: { //STOP
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
        break;
      }


  }
}
//
//int check()
//{
//  if (Serial.available() > 0)    //Check for data on the serial lines.
//  {
//    dataIn = Serial.read();  //Get the character sent by the phone and store it in 'dataIn'.
//        if (det == LF)
//        {
//          determinant = LF;
//        }
//        else if (det == LB)
//        {
//          determinant = LB;
//        }
//        else if (det == RF)
//        {
//          determinant = RF;
//        }
//        else if (det == RB)
//        {
//          determinant = RB;
//        }
//        else if(det == 'S')
//        {
//          determinant = 'S';
//        }
//  }
//
//
//    return determinant;
//}
