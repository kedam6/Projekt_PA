#include "Graphics.h"
#include "GameSupport.h"
#include "Cave.h"
#include "GameObjects.h"
#include "GameInfo.h"
#include "CaveInfo.h"
#include <random>

extern const int CaveData[];
extern const int CaveStartIdx[];

static const int sinlut64[] = { 16,18,19,21,22,24,25,26,27,28,29,30,31,31,32,32,32,32,32,31,31,30,29,28,27,26,25,24,22,21,19,18,16,14,13,11,10,8,7,6,5,4,3,2,1,1,0,0,0,0,0,1,1,2,3,4,5,6,7,8,10,11,13,14,16 };
static const int sinlut32[] = { 5,6,7,8,9,9,10,10,10,10,10,9,9,8,7,6,5,4,3,2,1,1,0,0,0,0,0,1,1,2,3,4,5 };

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

int Graphics::RenderField(int cave, int level, int field[CAVE_WIDTH][CAVE_HEIGHT])
{
	Cave caveObj = Cave();
	GameSupport support = GameSupport();

	caveObj.FillCaveWithData(&CaveData[CaveStartIdx[cave]]);

	int RandSeed1 = 0;
	int RandSeed2 = caveObj.caveData->RandSeed[level];

	for (int x = 0; x < CAVE_WIDTH; x++) {
		for (int y = 0; y < CAVE_HEIGHT; y++) {
			field[x][y] = DATA_STEELWALL;
		}
	}

	for (int y = 1; y < CAVE_HEIGHT - 1; y++) {
		for (int x = 0; x < CAVE_WIDTH; x++) {
			support.NextRandom(&RandSeed1, &RandSeed2);
			int store = DATA_DIRT;
			for (int caveDataaddIndex = 0; caveDataaddIndex < 4; caveDataaddIndex++) {
				if (RandSeed1 < caveObj.caveData->RandomFill[caveDataaddIndex * 2 + 1]) {
					store = caveObj.caveData->RandomFill[caveDataaddIndex * 2];
				}
			}
			if ((x>0) && (x<CAVE_WIDTH - 1))
				field[x][y] = store;
		}
	}

	int *drawidx = (&caveObj.caveData->DrawItems) + 1;
	int offset = 0;

	for (int item = 0; item<caveObj.caveData->DrawItems; item++)
	{
		int type = *(drawidx + offset);

		switch (type)
		{
		case DATA_DRAW_LINE:
		case DATA_DRAW_FILLRECT:
			DrawFillRect(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), field);
			offset += 6;
			break;
		case DATA_DRAW_FILLRECT2:
			DrawFillRect2(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), *(drawidx + offset + 6), field);
			offset += 7;
			break;
		case DATA_DRAW_RECTANGLE:
			DrawRect(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), field);
			offset += 6;
			break;
		case DATA_DRAW_POINT:
			DrawPoint(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), field);
			offset += 4;
			break;
		case DATA_DRAW_RASTER:
			DrawRaster(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), *(drawidx + offset + 6), *(drawidx + offset + 7), field);
			offset += 8;
			break;
		}

	}
	return offset;
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

void Graphics::GetColors(int type, int tick, int * colors)
{
	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;

	switch (type)
	{
	case DATA_SLIME:
		tick = (rand() & 7);
		colors[0] = 6;
		colors[1] = 6;
		colors[2] = 150 + (5 * sinlut32[tick & 63]);
		break;
	case DATA_AMOEBA:
		tick = (rand() & 7);
		colors[0] = 6;
		colors[1] = 150 + (5 * sinlut32[tick & 63]);
		colors[2] = 6;
		break;
	case DATA_DIRT:
		colors[0] = 94;
		colors[1] = 68;
		colors[2] = 36;
		break;
	case DATA_BOULDER:
	case DATA_BOULDER_FALL:
		colors[0] = 17;
		colors[1] = 99;
		colors[2] = 90;
		break;
	case DATA_OUTBOX_ACTIVE:
		colors[0] = 93 + (2 * sinlut64[tick & 63]);
		colors[1] = 93 + (2 * sinlut64[tick & 63]);
		colors[2] = 93 + (2 * sinlut64[tick & 63]);
		break;
	case DATA_OUTBOX:
	case DATA_STEELWALL:
		colors[0] = 93;
		colors[1] = 93;
		colors[2] = 93;
		break;
	case DATA_WALL:
		colors[0] = 126;
		colors[1] = 126;
		colors[2] = 126;
		break;
	case DATA_MAGICWALL:
		colors[0] = 146;
		colors[1] = 146;
		colors[2] = 146;
		break;
	case DATA_MAGICWALL_ACTIVE:
		colors[0] = 100 + (4 * sinlut64[tick & 63]);
		colors[1] = 100 + (4 * sinlut64[tick & 63]);
		colors[2] = 100 + (4 * sinlut64[tick & 63]);
		break;
	case DATA_DIAMOND:
	case DATA_DIAMOND_FALL:
		colors[0] = 86 + (2 * sinlut64[tick & 63]);
		colors[1] = 6;
		colors[2] = 86 + (2 * sinlut64[(tick + 5) & 63]);
		break;
	case DATA_COLOR_PURPLE:
		colors[0] = 86 + 10;
		colors[1] = 6;
		colors[2] = 86 + 10;
		break;
	case DATA_ROCKFORD:
	case DATA_ROCKFORD_GRAB:
		colors[0] = 158;
		colors[1] = 90 + (5 * sinlut64[tick & 63]);
		colors[2] = 53;
		break;
	case DATA_FIREFLY_RIGHT:
	case DATA_FIREFLY_LEFT:
	case DATA_FIREFLY_TOP:
	case DATA_FIREFLY_DOWN:
		colors[0] = 32 + (20 * sinlut32[tick & 31]);
		colors[1] = 32 + (20 * sinlut32[tick & 31]);
		colors[2] = 32 + (20 * sinlut32[tick & 31]);
		break;
	case DATA_BUTTERFLY_RIGHT:
	case DATA_BUTTERFLY_LEFT:
	case DATA_BUTTERFLY_UP:
	case DATA_BUTTERFLY_DOWN:
		colors[0] = 32 + (20 * sinlut32[tick & 15]);
		colors[1] = 6;
		colors[2] = 32 + (20 * sinlut32[tick & 15]);
		break;
	case DATA_EXPLOSION1:
	case DATA_EXPLOSION2:
	case DATA_EXPLOSION3:
	case DATA_EXPLOSION4:
	case DATA_EXPLOSION5:
		colors[0] = 255;
		colors[1] = ((DATA_EXPLOSION5 - type) * 50);
		colors[2] = 0;
		break;
	case DATA_DEXPLOSION1:
	case DATA_DEXPLOSION2:
	case DATA_DEXPLOSION3:
	case DATA_DEXPLOSION4:
	case DATA_DEXPLOSION5:
		colors[0] = 255;
		colors[1] = ((DATA_DEXPLOSION5 - type) * 30);
		colors[2] = 50;
		break;
	}
}
