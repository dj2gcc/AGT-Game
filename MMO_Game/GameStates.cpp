#include "GameStates.h"
#include "GameStateManager.h"

#define mainmenu manager->_MainMenu
#define gameplay manager->_GamePlay
#define ogremanager manager->getOgreManager()

//Start State functions
//
//

GameStateStart* GameStateStart::Instance()
{
  static GameStateStart instance;

  return &instance;
}

void GameStateStart::Enter(GameStateManager* manager)
{
	ogremanager->initRenderSystem();

	ogremanager->createWindow(false, "MainWindow");

	ogremanager->sceneManagerInit("MainSceneManager");

	ogremanager->createCamera("MainCamera");

	ogremanager->loadResourcesFromConfig();

	OgreInputManager::Instance()->initInput(ogremanager->getWindow());
}

void GameStateStart::Execute(GameStateManager* manager)
{
	manager->ChangeState(MenuState);
}

void GameStateStart::Exit(GameStateManager* manager)
{
}

//Cleanup State functions
//
//

GameStateCleanup* GameStateCleanup::Instance()
{
  static GameStateCleanup instance;

  return &instance;
}

void GameStateCleanup::Enter(GameStateManager* manager)
{	
}

void GameStateCleanup::Execute(GameStateManager* manager)
{
	manager->_GameStatus = false;
	
	OgreInputManager::Instance()->destroyInputManager();
}

void GameStateCleanup::Exit(GameStateManager* manager)
{
}

//Menu State functions
//
//

GameStateMenu* GameStateMenu::Instance()
{
  static GameStateMenu instance;

  return &instance;
}

void GameStateMenu::Enter(GameStateManager* manager)
{
	if(!mainmenu)
		mainmenu = new MainMenu(ogremanager);

	mainmenu->menuInit();
	manager->_InputManager->setInterface(mainmenu);
}

void GameStateMenu::Execute(GameStateManager* manager)
{
	mainmenu->update();
}

void GameStateMenu::Exit(GameStateManager* manager)
{
	mainmenu->cleanUp();
}

//GamePlay State functions
//
//

GameStatePlay* GameStatePlay::Instance()
{
  static GameStatePlay instance;

  return &instance;
}

void GameStatePlay::Enter(GameStateManager* manager)
{
	if(!gameplay)
		gameplay = new GamePlay(ogremanager);

	
	gameplay->gameplayInit();
	manager->_InputManager->setInterface(gameplay);
}

void GameStatePlay::Execute(GameStateManager* manager)
{
	gameplay->update();
}

void GameStatePlay::Exit(GameStateManager* manager)
{
	gameplay->cleanUp();
}
