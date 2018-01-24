#pragma once
#include "GlobalValues.h"

class GameEffects
{
public:
	GameEffects();
	~GameEffects();

	void Explode(int map[CAVE_WIDTH][CAVE_HEIGHT], int x, int y);
	void Dexplode(int map[CAVE_WIDTH][CAVE_HEIGHT], int x, int y);
};

