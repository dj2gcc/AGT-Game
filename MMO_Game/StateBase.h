#include<string>

class Telegram;

template <class object_type>

class StateBase
{
protected:

	std::string _Name;

public:

	virtual ~StateBase(){}

	virtual void Enter(object_type* o) {}

	virtual bool Execute(object_type* o, float tslf) { return true; }

	virtual void Exit(object_type* o) {}

	virtual bool OnMessage(object_type* o, const Telegram& t) {return true;}

	std::string getStateName() { return _Name; }
};