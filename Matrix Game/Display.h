#include<LiquidCrystal.h>
#include "Joystick.h"
#include "Levels.h"


const int RS = 8;
const int E = 9;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

int selectState;
int lastSelectState;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);


//void displayScoreAndLevel()
//{
//	lcd.setCursor(1, 0);
//	lcd.print("Score:");
//	lcd.setCursor(8, 0);
//	lcd.print((String)currScore);
//	lcd.setCursor(1, 1);
//	lcd.print("Level:");
//	lcd.setCursor(8, 1);
//	lcd.print((String)Level);
//}

//void setupDisplay() {
//	// put your setup code here, to run once:
//
//	pinMode(rX, INPUT);
//	pinMode(rY, INPUT);
//	pinMode(SW, INPUT_PULLUP);
//
//
//	lcd.begin(16, 2); //columns, nr of rows
//	lcd.clear();
//
//	menuState = 0;
//	selectState = 0;
//}
//
//void displayMenu(bool &gameOver, bool &gameRunning) {
//	// put your main code here, to run repeatedly:
//
//	//readJoystickMenu(selectState)
//	//int swVal = readJoystickButton();
//
//	if (swVal == 1)
//	{
//		if (menuState == 0)
//		{
//			menuState = selectState + 1;
//		}
//
//		if (menuState == 1) //game started
//		{
//			gameRunning = true;
//			gameOver = true;
//			return;
//		}
//	}
//
//	
//
//	if ((lastMenuState != menuState) || (lastSelectState != selectState))
//	{
//		lcd.clear();
//		lastMenuState = menuState;
//		lastSelectState = selectState;
//	}
//
//	switch (menuState) {
//	case 0:
//	{
//		lcd.setCursor(1, 0);
//		lcd.print("Start");
//		lcd.setCursor(7, 0);
//		lcd.print("HighScore");
//		lcd.setCursor(5, 1);
//		lcd.print("Settings");
//
//		switch (selectState)
//		{
//		case 0:
//		{
//			lcd.setCursor(0, 0);
//			lcd.print(">");
//			break;
//		}
//		case 1:
//		{
//			lcd.setCursor(6, 0);
//			lcd.print(">");
//			break;
//		}
//		case 2:
//		{
//			lcd.setCursor(4, 1);
//			lcd.print(">");
//			break;
//		}
//		}
//		break;
//	}
//	case 1:
//	{
//		lcd.setCursor(0, 0);
//		lcd.print("High Score:" + (String)highScore);
//		break;
//	}
//	case 2:
//	{
//		/*lcd.setCursor(0, 0);
//		lcd.print("Starting Level:");
//		lcd.setCursor(0, 1);
//		lcd.print((String)startingLevelValue);
//		break;*/
//	}
//	}
//
//	/*if (menuState == 2)
//	{
//		if (yVal > maxThreshold&&joystickMovedY == false)
//		{
//			startingLevelValue++;
//			if (startingLevelValue > 5)
//			{
//				startingLevelValue = 0;
//			}
//			joystickMovedY = true;
//		}
//
//		if (yVal < minThreshold&&joystickMovedY == false)
//		{
//			startingLevelValue--;
//			if (startingLevelValue < 0)
//			{
//				startingLevelValue = 5;
//			}
//			joystickMovedY = true;
//		}
//		if (yVal <= maxThreshold && yVal >= minThreshold)
//		{
//			joystickMovedY = false;
//		}
//	}*/
//
//}