#pragma once

//SLIDE
int slideX[3] = { 3, 4, 5 };
int slideY = 7;
const int minYSlide = 6;
const int maxYSlide = 7;
int slideIncrement = 1;

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