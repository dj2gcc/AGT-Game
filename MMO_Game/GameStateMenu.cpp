#include "GameStateMenu.h"

GameStateMenu* GameStateMenu::Instance()
{
  static GameStateMenu instance;

  return &instance;
}

void GameStateMenu::Enter(MainMenu* menu)
{
}

void GameStateMenu::Execute(MainMenu* menu)
{
}

void GameStateMenu::Exit(MainMenu* menu)
{
}