int aIn1 = 5;
int aIn2 = 6;
int aPwm = 10;
int stby = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(aIn1, OUTPUT);
  pinMode(aIn2, OUTPUT);
  pinMode(aPwm, OUTPUT);
  pinMode(stby, OUTPUT);

  digitalWrite(stby, HIGH);
  digitalWrite(aIn1, HIGH);
  digitalWrite(aIn2, LOW);
  analogWrite(aPwm, 255);
}

void loop() {
  // put your main code here, to run repeatedly:

}
