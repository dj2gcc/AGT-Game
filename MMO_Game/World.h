#pragma once


#include<vector>

#include "Ogre.h"

class Character;
class DynamicObject;
class Controller;

class World
{
private:

	std::vector<Controller*> _Population;
	std::vector<Controller*>::iterator _p;

	Controller* _InControl;

	World(){}
	~World(){}

public:

	static World* Instance();

	void populate();
	void destroy();

	void update(Ogre::Real tslf);

	Controller* getPlayerController() { return _Population.at(0); }
	Character* getPlayer();
	Controller* getInControl() { return _InControl; }
	Character* getCharacter(int id);
};

#define _World World::Instance()