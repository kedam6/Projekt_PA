#pragma once
#include "GlobalValues.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void DrawFillRect(int x1, int y1, int x2, int y2, int item, int field[CAVE_WIDTH][CAVE_HEIGHT]);
	void DrawFillRect2(int x1, int y1, int x2, int y2, int item, int item2, int field[CAVE_WIDTH][CAVE_HEIGHT]);
	void DrawPoint(int x, int y, int item, int field[CAVE_WIDTH][CAVE_HEIGHT]);
	void DrawRaster(int x1, int y1, int count_x, int count_y, int offset_x, int offset_y, int item, int field[CAVE_WIDTH][CAVE_HEIGHT]);
	void DrawRect(int x1, int y1, int x2, int y2, int item, int field[CAVE_WIDTH][CAVE_HEIGHT]);
	void GetColors(int type, int tick, int* colors);

};

