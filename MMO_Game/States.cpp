#include "States.h"
#include "Character.h"

Alive* Alive::Instance()
{
	static Alive instance;

	return &instance;
}

void Alive::Enter(Character* o)
{
	_Timer = 0;
}

bool Alive::Execute(Character* o, float tslf) 
{ 
	_Timer += tslf; 
	return true;
}


void Alive::Exit(Character* o) 
{
}

bool Alive::OnMessage(Character* o, const Telegram& t) 
{
	return true;
}

Dead* Dead::Instance()
{
	static Dead instance;

	return &instance;
}

void Dead::Enter(Character* o) 
{
	_Timer = 0;

	if(o->getName() == "Enemy")
	{
		o->setPosition(Ogre::Vector3(o->getStartPosition().x, o->getStartPosition().y - 6000, o->getStartPosition().z));
	}else
		if(o->getName() == "Player")
		{
			o->setPosition(o->getStartPosition());
			_Timer = 60;
			_World->resetAllTargets();
		}
}

bool Dead::Execute(Character* o, float tslf) 
{ 
	_Timer += tslf; 

	if(_Timer >= 60)
	{
		if(o->getName() == "Enemy")
		{
			o->setPosition(o->getStartPosition());
		}

		o->getStateMachine()->ChangeState(Alive::Instance());
	}
	return false;
}

void Dead::Exit(Character* o) 
{
	o->getCombat()->restore();
}

bool Dead::OnMessage(Character* o, const Telegram& t) 
{
	return false;
}
