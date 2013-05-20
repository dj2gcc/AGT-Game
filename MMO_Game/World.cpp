#include "World.h"
#include "SkillList.h"
#include "Event.h"
#include "Equipment.h"
#include "PlayerController.h"
#include "AIController.h"

World* World::Instance()
{
  static World instance;

  return &instance;
}

void World::populate()
{
	_Population.push_back(new PlayerController(new Character("sinbad.mesh", "Player", Ogre::Vector3(-5550, 1000, 5550))));
	_Population.at(0)->getControlled()->fitCamera(OgreManager::Instance()->getCamera());
	_InControl = _Population.at(0);

	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy", Ogre::Vector3(0, 1000, 0))));
	_Population.at(1)->getControlled()->getCombat()->learnSpell(new Attack());
	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy", Ogre::Vector3(-2000, 1000, -2000))));
	_Population.at(2)->getControlled()->getCombat()->learnSpell(new Attack());
	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy", Ogre::Vector3(0, 1000, 2000))));
	_Population.at(3)->getControlled()->getCombat()->learnSpell(new Attack());
	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy", Ogre::Vector3(-2000, 1000, 0))));
	_Population.at(4)->getControlled()->getCombat()->learnSpell(new Attack());
	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy", Ogre::Vector3(-3500, 1000, 0))));
	_Population.at(5)->getControlled()->getCombat()->learnSpell(new Attack());
	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy", Ogre::Vector3(-3500, 1000, -3500))));
	_Population.at(6)->getControlled()->getCombat()->learnSpell(new Attack());
	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy", Ogre::Vector3(3500, 1000, 3500))));
	_Population.at(7)->getControlled()->getCombat()->learnSpell(new Attack());
	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy", Ogre::Vector3(3000, 1000, -3000))));
	_Population.at(8)->getControlled()->getCombat()->learnSpell(new Attack());

	_Population.at(0)->getControlled()->getCombat()->learnSpell(new Attack());
	_Population.at(0)->getControlled()->getCombat()->learnSpell(new Pain());
	_Population.at(0)->getControlled()->getCombat()->learnSpell(new Heal());

	_Population.at(0)->getControlled()->Equip(new Equipment("Sword.mesh", "Sword", "RHand"));
}

void World::destroy()
{
	for(_p = _Population.begin(); _p != _Population.end(); _p++)
	{
		delete *_p;
	}
	_InControl = NULL;
}

void World::update(Ogre::Real tslf)
{
	for(_p = _Population.begin(); _p != _Population.end(); _p++)
	{
		(*_p)->update(tslf);
	}

	ProcessCollisions();
}

Character* World::getCharacter(int id)
{ 
	if(id < _Population.size() && id >= 0)
	{
		return _Population.at(id)->getControlled(); 
	}else 
	{ 
		return NULL; 
	}
}

Controller* World::getController(int id)
{ 
	if(id < _Population.size() && id >= 0)
	{
		return _Population.at(id); 
	}else 
	{ 
		return NULL; 
	}
}


Character* World::getPlayer() 
{ 
	return _Population.at(0)->getControlled(); 
}

void World::addEvent(Event* obj)
{
	_Events.push_back(obj);
}

void World::removeEvent(int id)
{
	std::vector<Event*>::iterator it;
	for(it = _Events.begin(); it != _Events.end(); ++it)
	{
		if((*it)->getID() == id)
		{
			delete * it;
			_Events.erase(it);
			break;
		}
	}
}

void World::ProcessCollisions()
{
	std::vector<Event*>::iterator it;
	for(it = _Events.begin(); it != _Events.end(); ++it)
	{
		if(collidesWith((*it), _Population.at(0)->getControlled()))
		{
			(*it)->executeEvent(_Population.at(0)->getControlled());
			break;
		}
	}
}

bool World::collidesWith(Event* eve, Character* chara)
{
	// Square of distance between cube centres
	float d2 = eve->getPosition().distance(chara->getPosition());
	// Square of the sum of the collision radii
	float sr2 = eve->getRadius() + chara->getCollisionRadius();

	if(d2 < sr2)
	{
		return true;
	}
	return false;
}

void World::resetAllTargets()
{
	for(int i = 1; i < _Population.size(); i++)
	{
		_Population.at(i)->resetTarget();
	}
}