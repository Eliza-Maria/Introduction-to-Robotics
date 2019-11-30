#include<LiquidCrystal.h>


const int RS = 12;
const int E = 11;
const int D4= 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

const int rX = A1;
const int rY = A0;
const int SW = 10;

int xVal = 0;
int yVal = 0;
int swVal = 0;

bool joystickMovedX=false;
bool joystickMovedY=false;
int minThreshold=400;
int maxThreshold=600;

int menuState = 0; //0 is main menu, 1 is start game
                      //2 is high score, 3 is settings
int lastMenuState = 0;

int selectState = 0;
int lastSelectState = 0;  

//start game
int gameStarted = 0;
int gameOver = 1;
int startingLevelValue = 0;
int level = 0;
int score = 0;

double timeGameStarted;
double lastTimeLevelUp;
const double endGameInterval = 10*1000;
const double levelUpInterval = 2*1000;

//highscore
int highScore = 0;

//for button 
double lastTimePressed = 0;
const double pressInterval = 1000;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
  // put your setup code here, to run once:

  pinMode(rX, INPUT);
  pinMode(rY, INPUT);
  pinMode(SW, INPUT_PULLUP);

  
  lcd.begin(16,2); //columns, nr of rows
  lcd.clear();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  xVal = analogRead(rX);
  yVal = analogRead(rY);
  swVal = digitalRead(SW); 

  if (swVal == LOW)
  {
    if (millis() - lastTimePressed > pressInterval)
    {
      if (menuState == 0)
    {
      menuState = selectState + 1;
    }
    else
    {
      if (gameOver == 1)
      {
        menuState = 0;
        selectState = 0;
      }
    }
    lastTimePressed = millis();
    }

    if( menuState == 1) //game started
    {
      gameStarted = 1;
    }
  }

  if(xVal>maxThreshold&&joystickMovedX==false)
  {
    selectState++;
    joystickMovedX=true;
    if (selectState > 2)
    {
      selectState = 0;
    }
  }

  if(xVal<minThreshold&&joystickMovedX==false)
  {
     selectState--;
     joystickMovedX=true;
    if (selectState < 0)
    {
      selectState = 2; 
    }
  }
  if(xVal<=maxThreshold&&xVal>=minThreshold)
  {
    joystickMovedX=false;
  }

  if ((lastMenuState != menuState) || (lastSelectState != selectState))
  {
    lcd.clear();
    lastMenuState = menuState;
    lastSelectState = selectState;
  }

  switch (menuState) {
  case 0:
    {
      lcd.setCursor(1,0); 
      lcd.print("Start");
      lcd.setCursor(7,0); 
      lcd.print("HighScore");
      lcd.setCursor(5,1); 
      lcd.print("Settings");

      switch (selectState)
      {
        case 0:
        {
          lcd.setCursor(0,0); 
          lcd.print(">");
          break;
        }
        case 1:
        {
          lcd.setCursor(6,0); 
          lcd.print(">");
          break;
        }
        case 2:
        {
          lcd.setCursor(4,1); 
          lcd.print(">");
          break;
        }
      }
      break;
      }
  case 1:
     {
      if (gameStarted == 1)
      {
        gameStarted = 0;
        level = startingLevelValue;
        timeGameStarted = millis();
        lastTimeLevelUp = millis();
        gameOver = 0;
      }
      else
      {
        if (gameOver == 1)
      {
        lcd.setCursor(0,0); 
        lcd.print("Congrats, you  ");
        lcd.setCursor(0,1); 
        lcd.print("won the game");
        Serial.println("game over");
      }
      else
      {  

        if (millis()- timeGameStarted > endGameInterval)
        {
          gameOver = 1;
          if (score > highScore)
          {
            highScore=score;
          }
          lcd.clear();
          Serial.println("clear");
        }

        if ( millis() - lastTimeLevelUp > levelUpInterval)
        {
          level++;
          lastTimeLevelUp = millis();
        }
      lcd.setCursor(0,0); 
      lcd.print("Lives:3");
      lcd.setCursor(8,0);
      lcd.print("Level:"+(String)level);
      lcd.setCursor(0,1);
      score =  level*3;
      lcd.print("Score:"+(String)score);
      }
      }
      
      
      break;
      }
  case 2:
     {
      lcd.setCursor(0,0); 
      lcd.print("High Score:"+(String)highScore);
      break;
      }
  case 3:
     {
      lcd.setCursor(0,0); 
      lcd.print("Starting Level:");
      lcd.setCursor(0,1); 
      lcd.print((String)startingLevelValue);
      break;
      }
}

if (menuState == 3)
{
  if(yVal>maxThreshold&&joystickMovedY==false)
  {
    startingLevelValue++;
    if (startingLevelValue > 5)
    {
      startingLevelValue = 0;
    }
    joystickMovedY=true;
  }

  if(yVal<minThreshold&&joystickMovedY==false)
  {
    startingLevelValue--;
    if (startingLevelValue < 0)
    {
      startingLevelValue = 5;
    }
    joystickMovedY=true;
  }
  if(yVal<=maxThreshold&&yVal>=minThreshold)
  {
    joystickMovedY=false;
  }
}

}
