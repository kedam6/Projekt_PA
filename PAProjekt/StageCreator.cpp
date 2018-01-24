#include "StageCreator.h"
#include "GameObjects.h"


StageCreator::StageCreator()
{
}

StageCreator::StageCreator(Graphics g)
{
	this->graphics = g;
}


StageCreator::~StageCreator()
{
}

void StageCreator::CreateStage(GameInfo& gameInfo, Cave& cave)
{
	//to da sie do oddzielnej klasy wyciagnac
	//z cavedata wyciagamy potrzebna pozycje do szukania itemkow do rysowania na buforze
	int *drawidx = (&cave.caveData->DrawItems) + 1;
	int offset = 0;

	for (int item = 0; item < cave.caveData->DrawItems; item++)
	{
		int type = *(drawidx + offset);

		switch (type)
		{
		case DATA_DRAW_LINE:
		case DATA_DRAW_FILLRECT:
			graphics.DrawFillRect(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), gameInfo.cavemap);
			offset += 6;
			break;
		case DATA_DRAW_FILLRECT2:
			graphics.DrawFillRect2(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), *(drawidx + offset + 6), gameInfo.cavemap);
			offset += 7;
			break;
		case DATA_DRAW_RECTANGLE:
			graphics.DrawRect(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), gameInfo.cavemap);
			offset += 6;
			break;
		case DATA_DRAW_POINT:
			graphics.DrawPoint(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), gameInfo.cavemap);
			offset += 4;
			break;
		case DATA_DRAW_RASTER:
			graphics.DrawRaster(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), *(drawidx + offset + 6), *(drawidx + offset + 7), gameInfo.cavemap);
			offset += 8;
			break;
		}

	}
}
