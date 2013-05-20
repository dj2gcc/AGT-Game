#pragma once


#include<vector>

#include "Ogre.h"

class Character;
class DynamicObject;
class Controller;
class Event;

class World
{
private:

	std::vector<Controller*> _Population;
	std::vector<Controller*>::iterator _p;

	std::vector<Event*> _Events;

	Controller* _InControl;

	World(){}
	~World(){}

public:

	static World* Instance();

	void populate();
	void destroy();

	void update(Ogre::Real tslf);

	void addEvent(Event* obj);
	void removeEvent(int id);

	void resetAllTargets();

	void ProcessCollisions();
	bool collidesWith(Event* eve, Character* chara);

	Controller* getPlayerController() { return _Population.at(0); }
	Character* getPlayer();
	Controller* getInControl() { return _InControl; }
	Character* getCharacter(int id);
	Controller* getController(int id);
};

#define _World World::Instance()