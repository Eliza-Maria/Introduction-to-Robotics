#include "LedControl.h" //  need the library

LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER

#include "Joystick.h"
#include "Slide.h"
#include "Ball.h"
#include "Animations.h"
#include "Display.h"
#include "EepromFunctions.h"
#include "Levels.h"

//BALL
unsigned long lastTimeBallMoved = 0;


///game logic
bool gameOver = false;
bool gameRunning = true;

bool showMenu = false;
bool showScore = false;

//animations
bool doLoseAnimation = false;
bool doWinAnimation = false;
unsigned long animationStartedAt = 0;
const int interlevelAnimationTime = 10000;
bool levelUpAnim = false;


void setup() {
	// the zero refers to the MAX7219 number, it is zero for 1 chip
	setupJoystickPins();
	setupDisplay();


	lc.shutdown(0, false); // turn off power saving, enables display
	lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
	lc.clearDisplay(0);// clear screen
	Serial.begin(9600);



	highScore = EEPROMReadInt(0);
	Serial.println(highScore);

	levelStartedAt = 0;
	resetLevels();
}

void loop() {
	// put your main code here, to run repeatedly:

	readJoystickGame();
	bool reset = readJoystickButton();

	if (showMenu)
	{
		displayMenu(showMenu, reset);
	}
	else
	{
		if (showScore)
		{
			displayScore();
		}
		else
		{
			displayTimeAndLevel();
		}
	}

	lc.clearDisplay(0); //clear the matrix

	if (millis() - levelStartedAt > Levels[currLevel].timeToComplete)
	{
		currLevel++;
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

		showMenu = true;
		lcd.clear();

		if (currScore > highScore)
		{
			EEPROMWriteInt(0, currScore);
		}
		//doLoseAnimation();
	}

	if (currLevel != lastLevel)
	{
		levelStartedAt = millis(); //we disable it temporarily

		//we leveled up
		gameRunning = false;
		showScore = true;
		lcd.clear();

		if (lastLevel == maxLevel)
		{
			resetLoseAnimation();
			levelUpAnim = true;
		}
		else
		{
			resetLoseAnimation();
			levelUpAnim = true;
			animationStartedAt = millis();
			//does animations for 10 sec
		}

		lastLevel = currLevel;
	}

	if (reset)
	{
		resetToFirstLevel();
		reset = false;
		gameRunning = true;
		resetBall();
		resetSlide();
		levelStartedAt = millis();
		doLoseAnimation = false;
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

		  showScore = false;
		  showMenu = false;
		  doLoseAnimation = false;
		  lcd.clear();

		  levelStartedAt = millis();
		  resetBall();
		  resetSlide();
	  }
  }

}
