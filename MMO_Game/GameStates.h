#pragma once

#include "GameState.h"

class GameStateManager;

//Start state
//
//

class GameStateStart : public GameState
{
private:

	GameStateStart(){}

	GameStateStart(const GameStateStart&);
	GameStateStart& operator=(const GameStateStart&);

public:

	~GameStateStart(){}

	static GameStateStart* Instance();

	virtual void Enter(GameStateManager* manager);

	virtual void Execute(GameStateManager* manager);

	virtual void Exit(GameStateManager* manager);

};

//Cleanup state
//
//

class GameStateCleanup : public GameState
{
private:

	GameStateCleanup(){}

	GameStateCleanup(const GameStateCleanup&);
	GameStateCleanup& operator=(const GameStateCleanup&);

public:

	~GameStateCleanup(){}

	static GameStateCleanup* Instance();

	virtual void Enter(GameStateManager* manager);

	virtual void Execute(GameStateManager* manager);

	virtual void Exit(GameStateManager* manager);

};

//Menu State
//
//

class GameStateMenu : public GameState
{
private:

	GameStateMenu(){}

	GameStateMenu(const GameStateMenu&);
	GameStateMenu& operator=(const GameStateMenu&);

public:

	~GameStateMenu(){}

	static GameStateMenu* Instance();

	virtual void Enter(GameStateManager* manager);

	virtual void Execute(GameStateManager* manager);

	virtual void Exit(GameStateManager* manager);

};

//Gameplay State
//
//

class GameStatePlay : public GameState
{
private:

	GameStatePlay(){}

	GameStatePlay(const GameStatePlay&);
	GameStatePlay& operator=(const GameStatePlay&);

public:

	~GameStatePlay(){}

	static GameStatePlay* Instance();

	virtual void Enter(GameStateManager* manager);

	virtual void Execute(GameStateManager* manager);

	virtual void Exit(GameStateManager* manager);

};
