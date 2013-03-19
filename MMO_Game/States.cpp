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
}

bool Dead::Execute(Character* o, float tslf) 
{ 
	_Timer += tslf; 

	if(_Timer >= 60)
	{
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
