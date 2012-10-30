#pragma once

#include "OgreLogManager.h"

class GameStateManager;

class GameState
{
public:

	virtual ~GameState(){}

	virtual void Enter(GameStateManager*) = 0;

	virtual void Execute(GameStateManager*) = 0;

	virtual void Exit(GameStateManager*) = 0;

};