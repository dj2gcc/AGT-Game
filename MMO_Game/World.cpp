#include "World.h"

World::World()
{
	_Player = NULL;
	_InControl = NULL;
}

World::~World()
{
	if(_Player)
		delete _Player;

	_Player = NULL;
	_InControl = NULL;
}

void World::populate()
{
	_Player = new PhysicsObject("sinbad.mesh");
	_Player->fitCamera(OgreManager::Instance()->getCamera());
	_InControl = _Player;
}

void World::update(Ogre::Real tslf)
{
	_InControl->update(tslf);
}