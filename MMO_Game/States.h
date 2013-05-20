#pragma once

#include "StateBase.h"
class Character;

class Alive : public StateBase<Character>
{
private:
	
	Alive() : StateBase<Character>(){ _Name = "Alive"; }
	~Alive(){}

	float _Timer;

public:

	static Alive* Instance();
	
	float getTimer(){ return _Timer; }

	void Enter(Character* o);

	bool Execute(Character* o, float tslf);

	void Exit(Character* o);

	bool OnMessage(Character* o, const Telegram& t);
};

class Dead : public StateBase<Character>
{
private:
	
	Dead() : StateBase<Character>(){ _Name = "Dead"; }
	~Dead(){}

	float _Timer;

public:

	static Dead* Instance();
	
	float getTimer(){ return _Timer; }

	void Enter(Character* o);

	bool Execute(Character* o, float tslf);

	void Exit(Character* o);

	bool OnMessage(Character* o, const Telegram& t);
};