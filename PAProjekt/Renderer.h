#pragma once
#include "GameInfo.h"

class Renderer
{
private:
	int _renderTick;

public:
	Renderer();
	~Renderer();
	
	void RenderGame(GameInfo game, unsigned int* pixelBuffer, unsigned int zoom);
	void RenderNum(int number, int x, int y, int length, int pad, int typea, int typeb, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)]);
};

