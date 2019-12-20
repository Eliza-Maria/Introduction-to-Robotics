#pragma once
#include "LedControl.h" //  need the library

int lightX = 0;
int lightY = 0;
const int ledNr = 64;
int ledCount = 0;

int snowFlakeFrame0[8][8] = {
{0, 0, 0, 1, 0, 1, 0, 1},
{0, 0, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 1, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0}
};

int snowFlakeFrame1[8][8] = {
{0, 0, 0, 1, 0, 1, 0, 1},
{0, 1, 0, 0, 1, 1, 1, 0},
{1, 0, 0, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 1, 1, 1, 0},
{0, 1, 0, 1, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 0, 0}
};

int snowFlakeFrame2[8][8] = {
{0, 0, 0, 1, 0, 1, 0, 1},
{0, 0, 1, 0, 1, 1, 1, 0},
{0, 0, 0, 1, 1, 1, 1, 1},
{0, 1, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 1, 0, 1, 0, 1},
{0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 1, 0}
};

int matrix[8][8] = {
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0}
};

int incrementX = 1;
int incrementY = 1;

//lose animation
int contourIdx = 0;
const int timeToChangeContour = 100;
unsigned long long lastTimeContourChanged = 0;

int valueToLed = 1;

//win animation
int frameIdx = 0;
const int timeToChangeFrame = 5000;
unsigned long long lastTimeFrameChanged = 0;
int value = 0;


void resetLoseAnimation()
{
	lightX = 0;
	lightY = 0;
	ledCount = 0;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

//int getCurrFrameValue(int frameIdx, int row, int col)
//{
//	switch (frameIdx) {
//	case 0:
//		return snowFlakeFrame0[row][col];
//	case 1:
//		return snowFlakeFrame1[row][col];
//	case 2:
//		return snowFlakeFrame2[row][col];
//	}
//
//	return 0;
//}

void winAnimation(LedControl lc)
{
	if (millis() - lastTimeFrameChanged > timeToChangeFrame)
	{
		lastTimeFrameChanged = millis();
		frameIdx++;
		if (frameIdx > 2)
		{
			frameIdx = 0;
		}
		Serial.println("change");
	}

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{

			if (frameIdx == 0)
			{
				value = snowFlakeFrame0[row][col];
			}
			if (frameIdx == 1)
			{
				value = snowFlakeFrame1[row][col];
			}
			if (frameIdx == 2)
			{
				value = snowFlakeFrame2[row][col];
			}

			//switch (frameIdx) {
			//case 0:
			//{
			//	value = snowFlakeFrame0[row][col];
			//	Serial.println(0);
			//	//break;
			//}
			//case 1:
			//{
			//	value = snowFlakeFrame1[row][col];
			//	Serial.println(1);
			//	//break;
			//}
			//case 2:
			//{
			//	value = snowFlakeFrame2[row][col];
			//	Serial.println(2);
			//	//break;
			//}
			//default:
			//	break;
			//}
			lc.setLed(0, row, col, value);
		}
	}
}

void loseAnimation(LedControl lc)
{
	if (contourIdx < 4)
	{
		
		for (int i = contourIdx; i < 8-contourIdx; ++i)
		{
			matrix[i][contourIdx] = valueToLed;
			matrix[i][7 - contourIdx] = valueToLed;
			matrix[contourIdx][i] = valueToLed;
			matrix[7 - contourIdx][i] = valueToLed;
		}

		if (millis() - lastTimeContourChanged > timeToChangeContour)
		{
			lastTimeContourChanged = millis();
			contourIdx++;
		}
	}
	else
	{
		contourIdx = 0;
		valueToLed = !valueToLed;

	}

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			lc.setLed(0, row, col, matrix[row][col]);
		}
	}
}