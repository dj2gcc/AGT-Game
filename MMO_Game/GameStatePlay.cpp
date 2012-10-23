#include "GameStatePlay.h"

GameStatePlay* GameStatePlay::Instance()
{
  static GameStatePlay instance;

  return &instance;
}

void GameStatePlay::Enter(Game* menu)
{
}

void GameStatePlay::Execute(Game* menu)
{
}

void GameStatePlay::Exit(Game* menu)
{
}