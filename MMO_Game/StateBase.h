class Telegram;

template <class object_type>

class StateBase
{
protected:

	float _Timer;

public:

	virtual ~StateBase(){}

	float getTimer(){ return _Timer; }

	virtual void Enter(object_type* o) {}

	virtual void Execute(object_type* o, float tslf) {}

	virtual void Exit(object_type* o) {}

	virtual bool OnMessage(object_type* o, const Telegram& t) {return true;}
};