#pragma once
#include "GlobalValues.h"


class GameInfo
{
public:
	GameInfo();
	~GameInfo();

	int Tick;
	int Player_X;
	int Cave;
	int Difficulty;
	int DiamonValue;
	int DiamonValueBonus;
	int DiamondsRequired;
	int DiamondsCollected;
	int Won;
	int Lost;
	int CaveTime;
	int* Colors;
	int MagicWallActive;
	int MagicWallTime;
	int AmoebaTime;
	int AmoebaSpace;
	int SlimeSeed1;
	int SlimeSeed2;
	int Intermission;
	char covered[CAVE_WIDTH][CAVE_HEIGHT];
	int cavemap[CAVE_WIDTH][CAVE_HEIGHT];
	
};

