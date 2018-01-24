#include "Graphics.h"
#include "GameSupport.h"
#include "Cave.h"
#include "GameObjects.h"
#include "GameInfo.h"
#include "CaveInfo.h"
#include <random>

extern const int CaveData[];
extern const int CaveStartIdx[];



Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

void Graphics::DrawFillRect(int x1, int y1, int x2, int y2, int item, int field[CAVE_WIDTH][CAVE_HEIGHT])
{
	for (int x = x1; x <= x2; x++)
	{
		for (int y = y1; y <= y2; y++)
		{
			field[x][y] = item;
		}
	}
}

void Graphics::DrawFillRect2(int x1, int y1, int x2, int y2, int item, int item2, int field[CAVE_WIDTH][CAVE_HEIGHT])
{
	for (int x = x1; x <= x2; x++)
	{
		for (int y = y1; y <= y2; y++)
		{
			if ((x == x1) || (x == x2) || (y == y1) || (y == y2))
				field[x][y] = item;
			else
				field[x][y] = item2;
		}
	}
}

void Graphics::DrawPoint(int x, int y, int item, int field[CAVE_WIDTH][CAVE_HEIGHT])
{
	field[x][y] = item;
}

void Graphics::DrawRaster(int x1, int y1, int count_x, int count_y, int offset_x, int offset_y, int item, int field[CAVE_WIDTH][CAVE_HEIGHT])
{
	for (int x = 0; x < count_x; x++)
	{
		for (int y = 0; y < count_y; y++)
		{
			field[x1 + (x * offset_x)][y1 + (y * offset_y)] = item;
		}
	}
}

void Graphics::DrawRect(int x1, int y1, int x2, int y2, int item, int field[CAVE_WIDTH][CAVE_HEIGHT])
{
	for (int x = x1; x <= x2; x++)
	{
		for (int y = y1; y <= y2; y++)
		{
			if ((x == x1) || (x == x2) || (y == y1) || (y == y2))
				field[x][y] = item;
		}
	}
}


