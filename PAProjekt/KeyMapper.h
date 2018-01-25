#pragma once
#include <map>
#include "SDL.h"
#include <functional>
#include <algorithm>

using namespace std;

class KeyMapper
{
private:
	map<SDL_Keycode, int> keyMapping;
public:
	KeyMapper();
	void InitMapping();
	~KeyMapper();

	int GetKeyIdByKeyCode(SDL_Keycode key);
	bool IsEscapeKeyCode(SDL_Keycode key) { return key == SDLK_ESCAPE; }
	bool IsRecognizedKeyCode(SDL_Keycode key);
};

