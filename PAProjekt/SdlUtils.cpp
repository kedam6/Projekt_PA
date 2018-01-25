#include "SdlUtils.h"
#include "SDL.h"
#include "PixelBuffer.h"



SdlUtils::SdlUtils()
{
	window = NULL;
	renderer = NULL;
	texture = NULL;
}

SdlUtils::SdlUtils(InputHandler inputHandler, FpsLimitter fpsLimiter)
{
	this->inputHandler = inputHandler;
	this->fpsLimiter = fpsLimiter;
}

SdlUtils::~SdlUtils()
{
}

int fpsMill;



SDL_Window* CreateWindow(int height, int width, const char* title)
{
	return SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, width, SDL_WINDOW_SHOWN);
}

SDL_Renderer* CreateRenderer(SDL_Window* window)
{
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* CreateTexture(SDL_Renderer* renderer, int height, int width)
{
	return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, height, width);
}

PixelBuffer SdlUtils::SdlInit(int height, int width, const char* title, int fps)
{
	//plansza to po prostu tablica intow
	pixelbuffer = new unsigned int[height*width];
	PixelBuffer ret = PixelBuffer(pixelbuffer);

	//SDLowe rzeczy
	//screensaver na poczatku
	SDL_EnableScreenSaver();
	window = CreateWindow(height, width, title); 
	renderer = CreateRenderer(window); 
	texture = CreateTexture(renderer, height, width); 

	//potrzebne dla renderowania
	fpsLimiter.SetFpsMill(1000 / fps);
	initialized = true;

	//ile mamy rzedow do renderowania
	row = height;

	return ret;
}

void SdlUtils::SdlClose()
{
	initialized = false;

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete pixelbuffer;
}

void SdlUtils::SdlWindowSize(int height, int width)
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_SetWindowSize(window, height, width);

	renderer = CreateRenderer(window);
	texture = CreateTexture(renderer, height, width);

	row = height;
}

bool SdlUtils::SdlHandleEvents(void * pixels)
{
	//potrzebna jest tablica void tutaj, nic nie moge z tym zrobic...
	SDL_UpdateTexture(texture, NULL, pixels, row * sizeof(Uint32));
	//renderujemy od nowa texture jesli to jest wymagane
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	fpsLimiter.LimitFps();

	SDL_Event ev;
	bool isStillRunning = true;

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type) {
		case SDL_QUIT:
			return false;
			break;
		case SDL_KEYUP:
			inputHandler.HandleInput(ev.key.keysym.sym, InputType::KeyUp);
			break;
		case SDL_KEYDOWN:
			isStillRunning = inputHandler.HandleInput(ev.key.keysym.sym, InputType::KeyDown);
			
			if (!isStillRunning)
				return false;
		default: break;
		}
	}
	return true;
}

void SdlUtils::SdlReleaseKeys()
{
	inputHandler.ReleaseKeys();
}

int SdlUtils::SdlGetKey(int key)
{
	return inputHandler.GetKey(key);

}

int SdlUtils::SdlLimitFps(int* limiter)
{
	return fpsLimiter.SdlLimitFps(limiter);
}





