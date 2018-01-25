#include "KeyMapper.h"



KeyMapper::KeyMapper()
{
	InitMapping();
}

void KeyMapper::InitMapping()
{
	keyMapping[SDLK_UP] = 0;
	keyMapping[SDLK_RIGHT] = 1;
	keyMapping[SDLK_DOWN] = 2;
	keyMapping[SDLK_LEFT] = 3;
	keyMapping[SDLK_F1] = 4;
	keyMapping[SDLK_F2] = 5;
	keyMapping[SDLK_F3] = 6;
	keyMapping[SDLK_F4] = 7;
}


KeyMapper::~KeyMapper()
{
}

int KeyMapper::GetKeyIdByKeyCode(SDL_Keycode key)
{
	return keyMapping[key];
}

bool KeyMapper::IsRecognizedKeyCode(SDL_Keycode key)
{
	map<SDL_Keycode, int>::iterator it = keyMapping.find(key);

	return it != keyMapping.end();
}
