#include "World.h"
#include "SkillList.h"

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
	_Population.push_back(new PlayerController(new Character("sinbad.mesh", "Player")));
	_Population.at(0)->getControlled()->fitCamera(OgreManager::Instance()->getCamera());
	_InControl = _Population.at(0);

	_Population.push_back(new AIController(new Character("sinbad.mesh", "Enemy")));

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

Character* World::getPlayer() 
{ 
	return _Population.at(0)->getControlled(); 
}
