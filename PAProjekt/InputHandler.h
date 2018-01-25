#pragma once
#include "SDL.h"
#include "KeyMapper.h"

enum InputType
{
	KeyDown,
	KeyUp
};

static int keymap;
static int releasemap;
static int ackmap;

class InputHandler
{
private:
	KeyMapper mapper;

public:
	InputHandler();
	InputHandler(KeyMapper mapper);
	~InputHandler();

	bool HandleInput(SDL_Keycode key, InputType typeOfInput);
	int GetKey(int id);
	void ReleaseKeys();
	void MarkKeyUp(int key);
	void MarkKeyDown(int key);
};



