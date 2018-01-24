#pragma once
#include <iostream>
#include "SDL.h"

using namespace std;





class SdlUtils
{

private:
	 int init_tick;
	 unsigned int* pixelbuffer;
	 SDL_Window* window;
	 SDL_Renderer* renderer;
	 SDL_Texture* texture;
	 bool initialized = false;


public:
	SdlUtils();
	~SdlUtils();

	unsigned int* SdlInit(int height, int width, const char* title, int fps);
	void SdlClose();
	void SdlWindowSize(int height, int width);
	int SdlHandleEvents(void* pixels);
	void SdlReleaseKeys();
	int SdlGetKey(int key);
	int SdlLimitFps(int* limiter, int fps);
	unsigned int GetTouch(unsigned int* x, unsigned int* y);

};

