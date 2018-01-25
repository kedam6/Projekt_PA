#include "FpsLimitter.h"
#include "SDL.h"


FpsLimitter::FpsLimitter()
{
}


FpsLimitter::~FpsLimitter()
{
}

void FpsLimitter::SetFpsMill(int mill)
{
	fpsMill = mill;
}

void FpsLimitter::LimitFps()
{
	//limitujemy FPS
	int current_tick = SDL_GetTicks();
	if ((current_tick - initTick) < fpsMill)
	{
		SDL_Delay(fpsMill - (current_tick - initTick));
	}
	initTick = SDL_GetTicks();
}

int FpsLimitter::SdlLimitFps(int * limiter)
{
	if (*limiter == 0)
	{
		*limiter = SDL_GetTicks();
	}

	int current_tick = SDL_GetTicks();

	if ((current_tick - *limiter) > 125)
	{
		current_tick = SDL_GetTicks();
		*limiter += 125;
		return 1;
	}
	return 0;
}
