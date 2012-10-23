//Damian Jurkiewicz 0901454
#include "OgreManager.h"
#include "MainMenu.h"


void main()
{
	OgreManager* _OgreManager = new OgreManager();

	

	MainMenu* menu = new MainMenu(_OgreManager);

	menu->menuInit();

	menu->update();
}