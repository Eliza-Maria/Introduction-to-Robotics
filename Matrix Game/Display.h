#include<LiquidCrystal.h>
#include "Joystick.h"
#include "Levels.h"


const int RS = 8;
const int E = 9;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

int selectState = 0;
int lastSelectState = 0;
int menuState = 0;
int lastMenuState = 0;
bool swVal2;

unsigned int lastDebounceBack = 0;
const int debounceBackInterval = 1000;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);


void setupDisplay() {

	lcd.begin(16, 2); //columns, nr of rows
	lcd.clear();

	menuState = 0;
	selectState = 0;
}

void displayTimeAndLevel()
{
	unsigned long timeRemaining = ((levelStartedAt + Levels[currLevel].timeToComplete) - millis()) / 1000;
	lcd.setCursor(0, 0);
	lcd.print("Time:");
	lcd.setCursor(8, 0);
	lcd.print((String)timeRemaining);

	lcd.setCursor(0, 1);
	lcd.print("Level:");
	lcd.setCursor(8, 1);
	lcd.print((String)currLevel); 
}

void displayScore()
{
	lcd.setCursor(0, 0);
	lcd.print("Score:");
	lcd.setCursor(8, 0);
	lcd.print((String)currScore);
}

void displayMenu(bool &showMenu, bool &reset) 
{
	reset = false;
	readJoystickMenu(selectState);

	swVal2 = digitalRead(SW);
	if (swVal2 == LOW)
	{

		if (millis() - lastTimePressed > pressInterval)
		{
			lastTimePressed = millis();
			if (menuState == 0)
			{
				menuState = selectState + 1;
				lastDebounceBack = millis();
			}
			else if (menuState == 2)
			{		
				menuState = 0;
				selectState = 0;
			}
		}
	}

	if (lastMenuState != menuState || lastSelectState != selectState)
	{
		lcd.clear();
		lastMenuState = menuState;
		lastSelectState = selectState;
	}

	switch (menuState)
	{
		case 0:
		{
			lcd.setCursor(4, 0);
			lcd.print("Start");
			lcd.setCursor(4, 1);
			lcd.print("HighScore");

			switch (selectState)
			{
			case 0:
			{
				lcd.setCursor(3, 0);
				lcd.print(">");
				break;
			}
			case 1:
			{
				lcd.setCursor(3, 1);
				lcd.print(">");
				break;
			}
			}
			break;
		}
		case 1:
		{
			showMenu = false;
			reset = true;
			menuState = 0;
			lastMenuState = 0;
			selectState = 0;
			break;
		}
		case 2:
		{
			lcd.setCursor(0, 0);
			lcd.print("High Score:" + (String)highScore);
			break;
		}
	}

}
