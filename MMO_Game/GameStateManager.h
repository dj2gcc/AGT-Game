#pragma once

#include "OgreManager.h"
#include "OgreInputManager.h"
#include "Interface.h"
#include "MainMenu.h"
#include "GamePlay.h"
#include "GameStates.h"

#define MenuState GameStateMenu::Instance()
#define PlayState GameStatePlay::Instance()
#define CleanupState GameStateCleanup::Instance()
#define StartState GameStateStart::Instance()
#define LoadingState GameStateLoading::Instance()

#define StateManager _GameStateManager

class GameStateManager
{
private:

	bool _GameStatus;

	OgreInputManager* _InputManager;

	OgreManager* _OgreManager;

	MainMenu* _MainMenu;

	GamePlay* _GamePlay;

	GameState* _PreviousState;
	GameState* _CurrentState;

	void SetCurrentState(GameState* newState);

public:

	GameStateManager();
	~GameStateManager();

	void ChangeState(GameState* newState);

	void run();

	OgreManager* getOgreManager() { return _OgreManager; }
	MainMenu* getMainMenu() { return _MainMenu; }
	GamePlay* getGame() { return _GamePlay; }
	GameState* getCurrentState() { return _CurrentState; }

	friend class GameStateStart;
	friend class GameStateCleanup;
	friend class GameStatePlay;
	friend class GameStateMenu;
};

extern GameStateManager _GameStateManager;