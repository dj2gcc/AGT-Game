#include "World.h"
#include "SkillList.h"

#include "Character.h"
#include "Equipment.h"

World* World::Instance()
{
  static World instance;

  return &instance;
}

void World::populate()
{
	_Population.push_back(new Character("sinbad.mesh", "Player"));
	_Population.at(0)->fitCamera(OgreManager::Instance()->getCamera());
	_InControl = _Population.at(0);

	_Population.push_back(new Character("sinbad.mesh", "Enemy"));

	_Population.at(0)->_Target = _Population.at(1);
	_Population.at(0)->getCombat()->learnSpell(new Attack());
	_Population.at(0)->getCombat()->learnSpell(new Pain());
	_Population.at(0)->getCombat()->learnSpell(new Heal());

	_Population.at(0)->Equip(new Equipment("Sword.mesh", "Sword", "RHand"));
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
		return _Population.at(id); 
	}else 
	{ 
		return NULL; 
	}
}