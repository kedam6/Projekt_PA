#include "MapHandler.h"



MapHandler::MapHandler()
{
}


MapHandler::~MapHandler()
{
}

void MapHandler::SaveNewMap(int from[CAVE_WIDTH][CAVE_HEIGHT], int to[CAVE_WIDTH][CAVE_HEIGHT])
{
	for (int y = 0; y < CAVE_HEIGHT; y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			to[x][y] = from[x][y];
		}
	}
}
