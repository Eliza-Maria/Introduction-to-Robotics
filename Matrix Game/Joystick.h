#pragma once
#include "Slide.h"

// JOYSTICK
const int joyX = A0;
const int joyY = A1;
const int SW = 6;

boolean movedX = false, movedY = false;
int valX = 0;
int valY = 0;

//joystick button
int swVal = 0;
unsigned long lastTimePressed = 0;
const int pressInterval = 1000;

//MOVE SLIDE
const int moveSlideInterval = 100;
unsigned long lastTimeSlideMoved = 0;

//menu
bool joystickMovedX = false;
bool joystickMovedY = false;

void setupJoystickPins()
{
	pinMode(joyX, INPUT);
	pinMode(joyY, INPUT);
	pinMode(SW, INPUT_PULLUP);
}

bool readJoystickButton()
{

	swVal = digitalRead(SW);
	if (swVal == LOW)
	{
		return true;
		if (millis() - lastTimePressed > pressInterval)
		{
			lastTimePressed = millis();
			return true;
		}
	}
	return false;
}

void readJoystickMenu(int &selectState)
{
	valY = analogRead(joyY);

	if (valY > 600 && joystickMovedY == false)
	{
		selectState++;
		joystickMovedY = true;
		if (selectState > 1)
		{
			selectState = 0;
		}
	}

	if (valY < 400 && joystickMovedY == false)
	{
		selectState--;
		joystickMovedY = true;
		if (selectState < 0)
		{
			selectState = 1;
		}
	}
	if (valY <= 600 && valY >= 400)
	{
		joystickMovedY = false;
	}
}
void readJoystickGame()
{
	valX = analogRead(joyX);
	valY = analogRead(joyY);

	if (valY > 600)
	{
		if (movedY == false)
		{
			if (slideY > minYSlide)
			{
				slideY--;
			}
			movedY = true;
		}
	}
	else
	{
		if (valY < 400)
		{
			if (movedY == false)
			{
				if (slideY < maxYSlide)
				{
					slideY++;
				}
				movedY = true;
			}
		}
		else movedY = false;
	}

	if (valX < 400)
	{
		if (movedX == false)
		{
			slideIncrement = -1;
			movedX = true;

			if (millis() - lastTimeSlideMoved > moveSlideInterval)
			{
				lastTimeSlideMoved = millis();
				moveSlide();
			}
		}
	}
	else
	{
		if (valX > 600)
		{
			if (movedX == false)
			{
				slideIncrement = 1;
				movedX = true;

				if (millis() - lastTimeSlideMoved > moveSlideInterval)
				{
					lastTimeSlideMoved = millis();
					moveSlide();
				}
			}

		}
		else movedX = false;
	}
}
