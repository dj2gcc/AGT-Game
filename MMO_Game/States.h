#pragma once

#include "StateBase.h"
class Character;

class Alive : public StateBase<Character>
{
private:
	
	Alive() : StateBase<Character>(){}
	~Alive(){}

public:

	static Alive* Instance();

	void Enter(Character* o);

	void Execute(Character* o, float tslf);

	void Exit(Character* o);

	bool OnMessage(Character* o, const Telegram& t);
};

class Dead : public StateBase<Character>
{
private:
	
	Dead() : StateBase<Character>(){}
	~Dead(){}

public:

	static Dead* Instance();

	void Enter(Character* o);

	void Execute(Character* o, float tslf);

	void Exit(Character* o);

	bool OnMessage(Character* o, const Telegram& t);
};