#include "LedControl.h" //  need the library

LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER

#include "Joystick.h"
#include "Slide.h"
#include "Ball.h"
#include "Animations.h"
#include "Display.h"
#include "EepromFunctions.h"


//BALL
//const int moveBallInterval = 500;
unsigned long lastTimeBallMoved = 0;


///game logic
bool gameOver = false;
bool gameRunning = true;

int currLevel = 0;
int lastLevel = 0;

unsigned long long levelStartedAt;

//animations
bool doLoseAnimation = false;
bool doWinAnimation = false;
unsigned long animationStartedAt = 0;
const int interlevelAnimationTime = 10000;
bool levelUpAnim = false;


void setup() {
   // the zero refers to the MAX7219 number, it is zero for 1 chip
	setupJoystickPins();
	lc.shutdown(0, false); // turn off power saving, enables display
	lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
	lc.clearDisplay(0);// clear screen
	Serial.begin(9600);

	resetLevels();
	Serial.println("setup");

	_EEGET(highScore, 0);

	highScore = EEPROMReadInt(0);

	levelStartedAt = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

	readJoystickGame();
	bool reset = readJoystickButton();

	/*if (gameOver)
	{
		displayMenu(gameOver, gameRunning);
	}
	else
	{
		displayScoreAndLevel();

	}*/

	lc.clearDisplay(0); //clear the matrix

	if (millis() - levelStartedAt > Levels[currLevel].timeToComplete)
	{
		gameOver = true;
	}


	if (gameRunning)
	{
		//if the game hasn't ended, move the ball
		if (millis() - lastTimeBallMoved > Levels[currLevel].ballSpeedRate)
		{
			lastTimeBallMoved = millis();
			gameOver = moveBall(currLevel);
		}
		//matrix display
		displayBlocks(lc, currLevel);
		displaySlide(lc);
		displayBall(lc);
	}

	if (gameOver)
	{
		gameOver = false;
		gameRunning = false;
		resetLoseAnimation();
		doLoseAnimation = true;

		if (currScore > highScore)
		{
			EEPROMWriteInt(0, currScore);
		}
		//doLoseAnimation();
	}

	if (currLevel != lastLevel)
	{
		//we leveled up
		gameRunning = false;

		if (lastLevel == maxLevel)
		{
			resetLoseAnimation();
			levelUpAnim = true;
			//doWinAnimation(); //until it resets
			//display that if u click the joystick u can restart
		}
		else
		{
			resetLoseAnimation();
			levelUpAnim = true;
			animationStartedAt = millis();
			//doWinAnimation(); //10 sec
		}

		lastLevel = currLevel;
	}

	if (reset)
	{
		gameRunning = true;
		doLoseAnimation = false;
		resetLevels();
		resetBall();
		resetSlide();
		currLevel = 0;
		lastLevel = 0;
		currScore = 0;
		levelStartedAt = millis();
	}

	//do animations
  if (doLoseAnimation)
  {
	  loseAnimation(lc);
  }

  if (levelUpAnim)
  {
	  if (millis() - animationStartedAt < interlevelAnimationTime)
	  {
		  resetLoseAnimation();
		  loseAnimation(lc);
	  }
	  else
	  {
		  gameRunning = true;
		  levelUpAnim = false;
		  levelStartedAt = millis();
	  }
  }

  //Serial.println(currLevel);

}
