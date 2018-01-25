#include "ColorRepository.h"
#include "GameObjects.h"
#include <random>

//obudowac do LUT
static const int sinlut64[] = { 16,18,19,21,22,24,25,26,27,28,29,30,31,31,32,32,32,32,32,31,31,30,29,28,27,26,25,24,22,21,19,18,16,14,13,11,10,8,7,6,5,4,3,2,1,1,0,0,0,0,0,1,1,2,3,4,5,6,7,8,10,11,13,14,16 };
static const int sinlut32[] = { 5,6,7,8,9,9,10,10,10,10,10,9,9,8,7,6,5,4,3,2,1,1,0,0,0,0,0,1,1,2,3,4,5 };


ColorRepository::ColorRepository()
{
	InitLUT();
}


ColorRepository::~ColorRepository()
{
}

void ColorRepository::InitLUT()
{
	colorLUT[DATA_SLIME] = Color(150, 6, 6);
	colorLUT[DATA_AMOEBA] = Color(6, 255, 6);
	colorLUT[DATA_DIRT] = Color(190, 160, 120);
	colorLUT[DATA_BOULDER] = Color(90, 99, 17);
	colorLUT[DATA_BOULDER_FALL] = Color(90, 99, 17);
	colorLUT[DATA_OUTBOX_ACTIVE] = Color(93, 93, 93);
	colorLUT[DATA_OUTBOX] = Color(63, 63, 63);
	colorLUT[DATA_STEELWALL] = Color(63, 63, 63);
	colorLUT[DATA_WALL] = Color(106, 106, 106);
	colorLUT[DATA_MAGICWALL] = Color(100, 100, 100);
	colorLUT[DATA_MAGICWALL_ACTIVE] = Color(100, 100, 100);
	colorLUT[DATA_DIAMOND] = Color(255, 255, 0);
	colorLUT[DATA_DIAMOND_FALL] = Color(255, 255, 0);
	colorLUT[DATA_COLOR_PURPLE] = Color(96, 6, 96);
	colorLUT[DATA_ROCKFORD] = Color(53, 90, 158);
	colorLUT[DATA_ROCKFORD_GRAB] = Color(53, 90, 158);
	colorLUT[DATA_FIREFLY_RIGHT] = Color(255, 255, 255);
	colorLUT[DATA_FIREFLY_LEFT] = Color(255, 255, 255);
	colorLUT[DATA_FIREFLY_TOP] = Color(255, 255, 255);
	colorLUT[DATA_FIREFLY_DOWN] = Color(255, 255, 255);
	colorLUT[DATA_BUTTERFLY_RIGHT] = Color(0, 255, 255);
	colorLUT[DATA_BUTTERFLY_LEFT] = Color(0, 255, 255);
	colorLUT[DATA_BUTTERFLY_UP] = Color(0, 255, 255);
	colorLUT[DATA_BUTTERFLY_DOWN] = Color(0, 255, 255);
	colorLUT[DATA_EXPLOSION1] = Color(255, 0, 0);
	colorLUT[DATA_EXPLOSION2] = Color(255, 0, 0);
	colorLUT[DATA_EXPLOSION3] = Color(255, 0, 0);
	colorLUT[DATA_EXPLOSION4] = Color(255, 0, 0);
	colorLUT[DATA_EXPLOSION5] = Color(255, 0, 0);
	colorLUT[DATA_DEXPLOSION1] = Color(255, 0, 0);
	colorLUT[DATA_DEXPLOSION2] = Color(255, 0, 0);
	colorLUT[DATA_DEXPLOSION3] = Color(255, 0, 0);
	colorLUT[DATA_DEXPLOSION4] = Color(255, 0, 0);
	colorLUT[DATA_DEXPLOSION5] = Color(255, 0, 0);


}

bool ColorRepository::IsKeyPresentInLUT(int key)
{
	map<int, Color>::iterator it = colorLUT.find(key);

	return it != colorLUT.end();
}

void ColorRepository::GetColors(int type, int tick, int * colors)
{
	colors[0] = 0; //blue
	colors[1] = 0; //green
	colors[2] = 0; //red

	if (IsKeyPresentInLUT(type))
	{
		Color chosenColor = colorLUT[type];

		colors[0] = chosenColor.Blue;
		colors[1] = chosenColor.Green;
		colors[2] = chosenColor.Red;
	}
}