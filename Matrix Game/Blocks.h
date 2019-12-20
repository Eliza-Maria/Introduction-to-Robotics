#pragma once

#include "LedControl.h" //  need the library
#include "Structs.h"
#include "Levels.h"

void checkForBlocks(int levelIdx, int &ballX, int &ballY, direction &ballDirection)
{

	level& currLevel = Levels[levelIdx];

	int auxY = ballY + ballDirection.incrementY;
	int auxX = ballX + ballDirection.incrementX;
	
	for (int i = currLevel.numberOfBlocks - 1; i >= 0; --i)
	{
		block& currBlock = currLevel.blocks[i];
		if (!currBlock.wasHit)
		{
			if (currBlock.Xpos == auxX && currBlock.Ypos == ballY)
			{
				currBlock.wasHit = true;
				ballDirection.incrementX *= -1;
				currScore += currLevel.pointsPerBlock;
			/*	Serial.println("X");
				Serial.println(ballX);
				Serial.println(ballY);*/
			}
			else if (currBlock.Xpos == ballX && currBlock.Ypos == auxY)
			{
				currBlock.wasHit = true;
				ballDirection.incrementY *= -1;
				currScore += currLevel.pointsPerBlock;
				/*Serial.println("Y");
				Serial.println(ballX);
				Serial.println(ballY);*/
			}
			else if (currBlock.Xpos == auxX && currBlock.Ypos == auxY)
			{
				currBlock.wasHit = true;
				ballDirection.incrementY *= -1;
				ballDirection.incrementX *= -1;
				currScore += currLevel.pointsPerBlock;
				//Serial.println("XY");
				//Serial.println(ballX);
				//Serial.println(ballY);
			}

			if (currBlock.wasHit)
			{
				return;
			}

		}
	}
}

void displayBlocks(LedControl lc, int level)
{
	for (int i = 0; i < Levels[level].numberOfBlocks; ++i)
	{
		if (!Levels[level].blocks[i].wasHit)
		{
			lc.setLed(0, Levels[level].blocks[i].Ypos, Levels[level].blocks[i].Xpos, 1);
		}
	}
}