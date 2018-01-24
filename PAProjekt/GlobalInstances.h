#pragma once
#include "Engine.h"
#include "GameSupport.h"
#include "Graphics.h"
#include "Renderer.h"
#include "PositionChecker.h"
#include "GameInitInfo.h"
#include "SdlUtils.h"


class GlobalInstances
{
private:
	Engine engine;
	GameSupport gameSupport;
	Graphics graphics;
	Renderer renderer;
	PositionChecker posChecker;
	GameInitInfo initializer;
	GameEffects gameEffects;
	GameSupport support;
	SdlUtils sdlUtils;

	//singleton
	//GlobalInstances(GlobalInstances const&);
	//void operator=(GlobalInstances const&);

public:
	GlobalInstances()
	{
		initializer = GameInitInfo();
		renderer = Renderer();
		posChecker = PositionChecker();
		graphics = Graphics();
		gameEffects = GameEffects();
		support = GameSupport();
		sdlUtils = SdlUtils();
		engine = Engine(sdlUtils, initializer, renderer, posChecker, graphics, gameEffects, support);
	}
	~GlobalInstances();


	//singleton
	static GlobalInstances& Instance()
	{
		static GlobalInstances instance;
		return instance;
	}

	GlobalInstances(GlobalInstances const&) = delete;
	void operator=(GlobalInstances const&) = delete;

	template<typename T>
	T GetItem();
};


