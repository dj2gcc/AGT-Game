#include "StateBase.h"

class Character;

class Active : public StateBase<Character*>
{
public:

	~Active(){}
	
	void Enter(Character* o);

	void Execute(Character* o, float tslf);

	void Exit(Character* o);

	bool OnMessage(Character* o, const Telegram& t);
};

class Dead : public StateBase<Character*>
{
public:

	~Dead(){}
	
	void Enter(Character* o);

	void Execute(Character* o, float tslf);

	void Exit(Character* o);

	bool OnMessage(Character* o, const Telegram& t);
};
