#pragma once
#include "GameInfo.h"
#include "Graphics.h"
#include "PixelBuffer.h"
#include "ColorRepository.h"

class Renderer
{
private:
	int _renderTick;
	ColorRepository colorRepo;


	void HandleUncover(GameInfo & game);
	void WriteCavePart(GameInfo & game, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)]);
	void CreateDisplay(char ret[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)]);
	void WriteInfoPart(GameInfo & game, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)]);
	void WriteToPixelBuffer(char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)], unsigned int zoom, unsigned int * pixelBuffer);
	void RenderNum(int number, int x, int y, int length, int pad, int typea, int typeb, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)]);

public:
	Renderer();
	Renderer(ColorRepository colorRepo);
	~Renderer();

	void RenderGame(GameInfo& game, PixelBuffer& pixelBuffer, unsigned int zoom);
};

