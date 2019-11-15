const int passiveBuzzerPin = A0;
const int activeBuzzerPin = 11;
const int pushButtonPin=2;

int knockValue = 0;
int activeBuzzerValue = 440;

int activeBuzzerDelay=200;

int sing = 0;

unsigned long lastDebounceTime;
int lastButtonState = 1;
int readingButton = 0;
int buttonState = 1;

const int interval= 50;
const int threshold = 1;
unsigned long lastKnock = 0;
const int knockDelay = 10;
int singState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(passiveBuzzerPin, INPUT);
  pinMode(activeBuzzerPin, OUTPUT);
  pinMode(pushButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  knockValue = analogRead(passiveBuzzerPin);
  Serial.println(knockValue);
//  if (knockValue > threshold)
//  {
//    singState = 1;
//  }
//
//  if(millis()-lastKnock > knockDelay)
//    {
//      if(singState == 1)
//      {  
//        sing=1;
//        lastKnock = millis();
//        singState = 0;
//      }
//    }
  
  readingButton=digitalRead(pushButtonPin);
   if (readingButton !=lastButtonState)
   {
    lastDebounceTime=millis();
   }
   if(millis()-lastDebounceTime>interval)
    {
      if(readingButton!=buttonState)
      {
        buttonState=readingButton;

        if(buttonState==LOW)
        {
          sing = !sing; //=0
        }
      }
    }
   
    lastButtonState=readingButton;

  
  if(sing == 1)
  {
    tone(activeBuzzerPin, activeBuzzerValue, activeBuzzerDelay);
  }
  //tone(activeBuzzerPin, activeBuzzerValue, activeBuzzerDelay);
  //delay(activeBuzzerDelay);
  
}
