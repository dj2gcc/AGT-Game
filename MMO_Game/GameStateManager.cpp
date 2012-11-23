#include "GameStateManager.h"

GameStateManager _GameStateManager;

GameStateManager::GameStateManager()
{
	_GameStatus = true;

	_OgreManager = OgreManager::Instance();

	_MainMenu = NULL;

	_GamePlay = NULL;

	_PreviousState = NULL;

	SetCurrentState(StartState);
}

GameStateManager::~GameStateManager()
{
	Ogre::LogManager::getSingleton().logMessage("End of GameStateManager");
	
	if(_GamePlay)
		delete _GamePlay;
	
	if(_MainMenu)
		delete _MainMenu;

	if(_MapEditor)
		delete _MapEditor;

	_OgreManager->destroyOgreManager();
	
}

void GameStateManager::SetCurrentState(GameState* newState)
{
	assert(newState && "<GameStateManager::SetCurrentState>: Trying to set a null state");

	_CurrentState = newState;

	_CurrentState->Enter(this);
}

void GameStateManager::ChangeState(GameState* newState)
{
	assert(newState && "<GameStateManager::ChangeState>: Trying to change to a null state");

	_PreviousState = _CurrentState;

	_CurrentState->Exit(this);

	_CurrentState = newState;

	_CurrentState->Enter(this);
}

void GameStateManager::run()
{
	while(_GameStatus)
	{
		_CurrentState->Execute(this);
	}
}