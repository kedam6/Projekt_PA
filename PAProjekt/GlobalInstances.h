#pragma once
#include "Engine.h"
#include "GameSupport.h"
#include "Graphics.h"
#include "Renderer.h"
#include "PositionChecker.h"
#include "GameInitInfo.h"
#include "SdlUtils.h"
#include "NoiseMaker.h"
#include "StageCreator.h"

//slabe podejscie do DI ale coz

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
	NoiseMaker noiseMaker;
	StageCreator stageCreator;

public:
	GlobalInstances()
	{
		
		renderer = Renderer();
		posChecker = PositionChecker();
		graphics = Graphics();
		gameEffects = GameEffects();
		support = GameSupport();
		sdlUtils = SdlUtils();
		noiseMaker = NoiseMaker();
		stageCreator = StageCreator(graphics);
		initializer = GameInitInfo(graphics, renderer, posChecker, gameEffects, support, noiseMaker, stageCreator);
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


