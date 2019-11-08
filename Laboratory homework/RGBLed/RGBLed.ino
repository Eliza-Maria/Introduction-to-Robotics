const int potPinR=A0;
const int potPinG=A1;
const int potPinB=A2;

const int ledPinLegR=9;
const int ledPinLegG=10;
const int ledPinLegB=11;

int potValueR=0;
int ledValueR=0;

int potValueG=0;
int ledValueG=0;

int potValueB=0;
int ledValueB=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(potPinR, INPUT);
  pinMode(potPinG, INPUT);
  pinMode(potPinB, INPUT);
  
   pinMode(ledPinLegR, OUTPUT);
   pinMode(ledPinLegG, OUTPUT);
   pinMode(ledPinLegB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValueR = analogRead(potPinR);
  ledValueR = map(potValueR,0,1023,0,255);
  analogWrite(ledPinLegR,ledValueR);

  potValueG = analogRead(potPinG);
  ledValueG = map(potValueG,0,1023,0,255);
  analogWrite(ledPinLegG,ledValueG);

  potValueB = analogRead(potPinB);
  ledValueB = map(potValueB,0,1023,0,255);
  analogWrite(ledPinLegB,ledValueB);
}
