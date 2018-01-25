#include "InputHandler.h"



InputHandler::InputHandler()
{
}

InputHandler::InputHandler(KeyMapper mapper)
{
	this->mapper = mapper;
}


InputHandler::~InputHandler()
{
}

bool InputHandler::HandleInput(SDL_Keycode keyCode, InputType typeOfInput)
{
	if (mapper.IsEscapeKeyCode(keyCode))
		return false;

	if (mapper.IsRecognizedKeyCode(keyCode))
	{
		int keyId = mapper.GetKeyIdByKeyCode(keyCode);

		switch (typeOfInput)
		{
		case InputType::KeyDown:
			MarkKeyDown(keyId);
			break;
		case InputType::KeyUp:
			MarkKeyUp(keyId);
			break;
		};
	}

	return true;
}

int InputHandler::GetKey(int key)
{
	if ((keymap >> key) & 1)
	{
		ackmap |= (1 << key);
		return 1;
	}
	return 0;
}

void InputHandler::ReleaseKeys()
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


void InputHandler::MarkKeyUp(int key)
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




void InputHandler::MarkKeyDown(int key)
{
	keymap = 1 << key;
	ackmap &= ~(1 << key);
}
