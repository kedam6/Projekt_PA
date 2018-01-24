#include "SdlUtils.h"
#include "SDL.h"
#include "PixelBuffer.h"


SdlUtils::SdlUtils()
{
	window = NULL;
	renderer = NULL;
	texture = NULL;
}

SdlUtils::~SdlUtils()
{
}

int fpsMill;
int row;
int keymap;
int releasemap;
int ackmap;
unsigned int touch_avail = 0;
unsigned int motion_start = 0;
int motion_x = 0;
int motion_y = 0;
unsigned int touch_x = 0;
unsigned int touch_y = 0;

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
	fpsMill = 1000 / fps;
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

static void keyup(int key)
{
	if (ackmap & (1 << key))
	{
		keymap &= ~(1 << key);
	}
	else
	{
		releasemap |= (1 << key);
	}
}

static void touch_event(unsigned int x, unsigned int y)
{
	touch_x = x;
	touch_y = y;
	touch_avail = 1;
}

static void touch_end_move(void)
{
	motion_start = 0;
	keyup(0);
	keyup(1);
	keyup(2);
	keyup(3);
}

unsigned int SdlUtils::GetTouch(unsigned int * x, unsigned int * y)
{
	if (touch_avail == 1)
	{
		*x = touch_x;
		*y = touch_y;
		touch_avail = 0;
		return 1;
	}
	return 0;
}




static void keydown(int key)
{
	keymap = 1 << key;
	ackmap &= ~(1 << key);
}



int SdlUtils::SdlHandleEvents(void * pixels)
{
	SDL_UpdateTexture(texture, NULL, pixels, row * sizeof(Uint32));//update only the updated rects
																   //	SDL_RenderClear(renderer);//neccessary?
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	// limit to fps
	int current_tick = SDL_GetTicks();
	if ((current_tick - init_tick) < fpsMill)
	{
		SDL_Delay(fpsMill - (current_tick - init_tick));
	}
	init_tick = SDL_GetTicks();

	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type) {
		case SDL_QUIT:
			return 0;
			break;
		case SDL_MOUSEMOTION:
			if (motion_start == 1)
			{
				motion_x += ev.motion.xrel;
				motion_y += ev.motion.yrel;
				if (motion_y > 40)
				{
					keyup(0);
					keyup(1);
					keyup(2);
					keyup(3);
					keydown(2);
					motion_x = 0;
					motion_y = 0;
				}
				if (motion_y < -40)
				{
					keyup(0);
					keyup(1);
					keyup(2);
					keyup(3);
					keydown(0);
					motion_x = 0;
					motion_y = 0;
				}
				if (motion_x > 40)
				{
					keyup(0);
					keyup(1);
					keyup(2);
					keyup(3);
					keydown(1);
					motion_x = 0;
					motion_y = 0;
				}
				if (motion_x < -40)
				{
					keyup(0);
					keyup(1);
					keyup(2);
					keyup(3);
					keydown(3);
					motion_x = 0;
					motion_y = 0;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				motion_start = 1;
				motion_x = 0;
				motion_y = 0;
				touch_event(ev.button.x, ev.button.y);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				touch_end_move();
			}
			break;
		case SDL_KEYUP:
			switch (ev.key.keysym.sym)
			{
			case SDLK_UP:
				keyup(0);
				break;
			case SDLK_RIGHT:
				keyup(1);
				break;
			case SDLK_DOWN:
				keyup(2);
				break;
			case SDLK_LEFT:
				keyup(3);
				break;
			case SDLK_F1:
				keyup(4);
				break;
			case SDLK_F2:
				keyup(5);
				break;
			case SDLK_F3:
				keyup(6);
				break;
			case SDLK_F4:
				keyup(7);
				break;
			default: break;
			}
			break;
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return 0;
				break;
			case SDLK_UP:
				keydown(0);
				break;
			case SDLK_RIGHT:
				keydown(1);
				break;
			case SDLK_DOWN:
				keydown(2);
				break;
			case SDLK_LEFT:
				keydown(3);
				break;
			case SDLK_F1:
				keydown(4);
				break;
			case SDLK_F2:
				keydown(5);
				break;
			case SDLK_F3:
				keydown(6);
				break;
			case SDLK_F4:
				keydown(7);
				/*
				zoom=20;
				sdl_windowsize(CAVE_WIDTH*zoom, CAVE_HEIGHT*zoom);


				free(pixelarray);
				pixelarray = malloc (CAVE_HEIGHT *zoom * CAVE_WIDTH * zoom * sizeof(uint32_t));
				memset(pixelarray,0,CAVE_HEIGHT *zoom * CAVE_WIDTH * zoom * sizeof(uint32_t));*/
				break;
			default: break;
			}
		default: break;
		}
	}
	return 1;
}

void SdlUtils::SdlReleaseKeys()
{
	for (int i = 0; i < 8; i++)
	{
		if (releasemap & (1 << i))
		{
			keymap &= ~(1 << i);
		}
	}
	releasemap = 0;
}

int SdlUtils::SdlGetKey(int key)
{
	if ((keymap >> key) & 1)
	{
		ackmap |= (1 << key);
		return 1;
	}
	return 0;
}

int SdlUtils::SdlLimitFps(int* limiter)
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





