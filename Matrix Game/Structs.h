#pragma once

struct direction
{
	int incrementX;
	int incrementY;

	inline direction operator=(direction toCopy)
	{
		incrementX = toCopy.incrementX;
		incrementY = toCopy.incrementY;
	}
};


struct block
{
	int Xpos;
	int Ypos;
	bool wasHit;

	block()
	{
		Xpos = 0;
		Ypos = 0;
		wasHit = false;
	}

	block(int Xpos_, int Ypos_, bool wasHit_) :
		Xpos(Xpos_), Ypos(Ypos_), wasHit(wasHit_)
	{
	}

	inline block operator=(block toCopy)
	{
		Xpos = toCopy.Xpos;
		Ypos = toCopy.Ypos;
		wasHit = toCopy.wasHit;
	}
};

struct level
{
	int index;
	int pointsPerBlock;
	int numberOfBlocks;
	block *blocks;
	int ballSpeedRate;
	long timeToComplete;

	level(int index_, int pointsPerBlock_, int numberOfBlocks_, block blocks_[], int ballSpeedRate_, int timeToComplete_):
		index(index_), pointsPerBlock(pointsPerBlock_), numberOfBlocks(numberOfBlocks_),
		ballSpeedRate(ballSpeedRate_), timeToComplete(timeToComplete_)
	{
		blocks = (block*)malloc(64);
		for (int i = 0; i < numberOfBlocks; i++)
		{
			blocks[i] = blocks_[i];
		}

	}
	
	level()
	{
		index = 0;
		pointsPerBlock = 0;
		numberOfBlocks = 0;
		ballSpeedRate = 0;
		blocks = (block*)malloc(64);
	}
	//const int maxScore;

	inline level operator=(level toCopy)
	{
		index = toCopy.index;
		pointsPerBlock = toCopy.pointsPerBlock;
		numberOfBlocks = toCopy.numberOfBlocks;
		for (int i = 0; i < numberOfBlocks; ++i)
		{
			blocks[i] = toCopy.blocks[i];
		}
		ballSpeedRate = toCopy.ballSpeedRate;
		timeToComplete = toCopy.timeToComplete;
	}
};
