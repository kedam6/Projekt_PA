#pragma once
#include "GlobalValues.h"

class MapHandler
{
public:
	MapHandler();
	~MapHandler();

	void SaveNewMap(int from[CAVE_WIDTH][CAVE_HEIGHT], int to[CAVE_WIDTH][CAVE_HEIGHT]);
};

