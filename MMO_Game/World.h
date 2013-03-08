#pragma once


#include<vector>

#include "Ogre.h"

class Character;
class DynamicObject;

class World
{
private:

	std::vector<Character*> _Population;
	std::vector<Character*>::iterator _p;

	DynamicObject* _InControl;

	World(){}
	~World(){}

public:

	static World* Instance();

	void populate();
	void destroy();

	void update(Ogre::Real tslf);

	Character* getPlayer() { return _Population.at(0); }
	DynamicObject* getInControl() { return _InControl; }
	Character* getCharacter(int id);
};

#define _World World::Instance()