#pragma once

#include "Structs.h"

int currScore = 0;
int highScore = 0;
const int maxLevel = 3;

//blocks
block lvl1Blocks[8] = { { 2, 0, false }, { 3, 0, false }, { 4, 0, false }, { 5, 0, false },
						{ 2, 1, false } , { 3, 1, false } , { 4, 1, false } , { 5, 1, false } };

block lvl2Blocks[12] = { { 1, 0, false }, { 2, 0, false }, { 3, 0, false }, { 4, 0, false },
						{ 5, 0, false } , { 6, 0, false } , { 2, 1, false } , { 3, 1, false },
						{ 4, 1, false } , { 5, 1, false } , { 3, 2, false } , { 4, 2, false } };

block lvl3Blocks[18] = { { 0, 0, false }, { 1, 0, false }, { 2, 0, false }, { 3, 0, false },
						{ 4, 0, false } , { 5, 0, false } , { 6, 0, false } , { 7, 0, false },
						{ 2, 1, false } , { 3, 1, false } , { 4, 1, false } , { 5, 1, false },
						{ 3, 2, false } , { 4, 2, false } , { 2, 3, false } , { 3, 3, false },
						{ 4, 3, false } , { 5, 3, false } };


level LevelsModel[3] = { {1, 2, 8, lvl1Blocks, 400, 60000}, {2, 3, 12, lvl2Blocks, 300, 50000}, {3, 4, 18, lvl3Blocks, 200, 40000} };

//LEVELS
level Levels[3];


bool checkForLevelUp(int levelIdx)
{
	level& currLevel = Levels[levelIdx];
	if (currScore == currLevel.numberOfBlocks*currLevel.pointsPerBlock)
	{
		return true;
	}
	return false;
}
void resetLevels()
{
	for (int i = 0; i < maxLevel; i++)
	{
		Levels[i] = LevelsModel[i];
	}
}