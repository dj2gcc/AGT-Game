
template <class object_type>

class State
{
public:

	virtual ~State(){}

	virtual void Enter(object_type*) = 0;

	virtual void Execute(object_type*) = 0;

	virtual void Exit(object_type*) = 0;

};