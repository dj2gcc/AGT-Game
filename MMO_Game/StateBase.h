class Telegram;

template <class object_type>

class StateBase
{
public:

	virtual ~StateBase(){}

	virtual void Enter(object_type* o) {}

	virtual bool Execute(object_type* o, float tslf) { return true; }

	virtual void Exit(object_type* o) {}

	virtual bool OnMessage(object_type* o, const Telegram& t) {return true;}
};