#pragma once

#include "LedControl.h" //  need the library

//SLIDE
const int origSlideX[3] = { 3, 4, 5 };
const int origSlideY = 7;

int slideX[3] = { 3, 4, 5 };
int slideY = 7;
const int minYSlide = 6;
const int maxYSlide = 7;
int slideIncrement = 1;

void resetSlide()
{
	slideY = origSlideY;
	for (int i = 0; i < 3; i++)
	{
		slideX[i] = origSlideX[i];
	}
}

void moveSlide()
{
	if ((slideX[0] + slideIncrement < 0) ||
		(slideX[2] + slideIncrement > 7)) //the slide goes through walls
	{
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		slideX[i] += slideIncrement;
	}
}

void displaySlide(LedControl lc)
{
	for (int i = 0; i < 3; ++i) //display the slide
	{
		lc.setLed(0, slideY, slideX[i], 1);
	}
}