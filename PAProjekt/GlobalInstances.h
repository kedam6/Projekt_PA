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
#include "CaveFactory.h"
#include "GameFactory.h"
#include "GameInfoFactory.h"
#include "ColorRepository.h"
#include "InputHandler.h"
#include "KeyMapper.h"
#include "FpsLimitter.h"
#include "NoiseMaker.h"
#include "Sin32LookupTable.h"
#include "Sin64LookupTable.h"
#include "ActionMapping.h"
#include "ActionHandler.h"

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
	StageCreator stageCreator;
	ColorRepository colorRepo;
	//CaveFactory caveFactory;
	//GameFactory gameFactory;
	//GameInfoFactory gameInfoFactory;
	InputHandler inputHandler;
	KeyMapper keyMapper;
	FpsLimitter fpsLimit;
	Sin32LookupTable sin32LUT;
	NoiseMaker noiseMaker;
	GameManager gameManager;
	ActionHandler actionHandler;
	ActionMapping actionMapping;

public:
	GlobalInstances()
	{
		posChecker = PositionChecker();
		graphics = Graphics();
		gameEffects = GameEffects();
		support = GameSupport();
		keyMapper = KeyMapper();
		colorRepo = ColorRepository();
		fpsLimit = FpsLimitter();
		//caveFactory = CaveFactory();
		//gameFactory = GameFactory();
		//gameInfoFactory = GameInfoFactory();
		inputHandler = InputHandler(keyMapper);
		sdlUtils = SdlUtils(inputHandler, fpsLimit);
		renderer = Renderer(colorRepo);
		noiseMaker = NoiseMaker(gameSupport);
		stageCreator = StageCreator(graphics);
		actionMapping = ActionMapping(posChecker, gameEffects, gameSupport, inputHandler);
		actionHandler = ActionHandler(actionMapping);
		initializer = GameInitInfo(graphics, renderer, posChecker, gameEffects, support, noiseMaker, stageCreator);
		gameManager = GameManager(sdlUtils, initializer, renderer, posChecker, graphics, gameEffects, support, actionHandler);
		engine = Engine(sdlUtils, initializer, renderer, posChecker, graphics, gameEffects, support, gameManager);
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


