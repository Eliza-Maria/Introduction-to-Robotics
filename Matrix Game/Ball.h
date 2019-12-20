#pragma once

#include "Blocks.h"

//BALL
int origBallX = 0;
int origBallY = 3;
direction origBallDirection = { -1, 1 };

int ballX = 0;
int ballY = 3;
direction ballDirection = { -1, 1 };

void resetBall()
{
	ballX = origBallX;
	ballY = origBallY;
	ballDirection = origBallDirection;
}

bool moveBall(int &levelIdx)
{
	checkForBlocks(levelIdx, ballX, ballY, ballDirection);

	if (checkForLevelUp(levelIdx))
	{
		++levelIdx;
	}

	int auxY = ballY + ballDirection.incrementY;
	int auxX = ballX + ballDirection.incrementX;
	if (auxY == slideY) //with the current direction, the ball hits the slide
	{
		if (ballX == slideX[0]) //left edge of slide
		{
			ballDirection.incrementX = -1; //force to go left
			ballDirection.incrementY = -1;

			if (auxX == -1)
			{
				ballDirection.incrementX = 1; //we hit the wall so we can't go any further
			}

			ballX += ballDirection.incrementX;
			ballY += ballDirection.incrementY;
		}
		else if (ballX == slideX[2]) //right edge of slide
		{
			ballDirection.incrementX = 1; //force to go right
			ballDirection.incrementY = -1;

			if (auxX == 8)
			{
				ballDirection.incrementX = -1; //we hit the wall so we can't go any further
			}

			ballX += ballDirection.incrementX;
			ballY += ballDirection.incrementY;
		}
		else if (ballX == slideX[1]) //center of slide
		{
			ballDirection.incrementY = -1;

			ballX += ballDirection.incrementX;
			ballY += ballDirection.incrementY;
			/*ballY--;
			ballX++;*/
		}
		else
		{
			ballY++;
		}
	}
	else
	{
		//collisions with walls
		if ((ballX == 7) || //we hit the right wall
			(ballX == 0)) //we hit the left wall
		{
			ballDirection.incrementX *= -1;
		}

		if (auxY == 0) //we hit the upper wall
		{
			ballDirection.incrementY *= -1;
		}

		ballX += ballDirection.incrementX;
		ballY += ballDirection.incrementY;
	}
	//at corners, both directions will be inverted

	if (ballY > 7) //we hit the bottom wall
	{
		return true;
	}

	return false;
}

void displayBall(LedControl lc)
{
	lc.setLed(0, ballY, ballX, 1); //display the ball
}