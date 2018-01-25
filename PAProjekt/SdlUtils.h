#pragma once
#include <iostream>
#include "SDL.h"
#include "PixelBuffer.h"
#include "FpsLimitter.h"
#include "InputHandler.h"

using namespace std;





class SdlUtils
{

private:
	unsigned int* pixelbuffer;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	FpsLimitter fpsLimiter;
	InputHandler inputHandler;
	int row;
	bool initialized = false;


public:
	SdlUtils();
	SdlUtils(InputHandler inputHandler, FpsLimitter fpsLimiter);
	~SdlUtils();

	PixelBuffer SdlInit(int height, int width, const char* title, int fps);
	void SdlClose();
	void SdlWindowSize(int height, int width);
	bool SdlHandleEvents(void* pixels);
	void SdlReleaseKeys();
	int SdlGetKey(int key);
	int SdlLimitFps(int* limiter);
};

