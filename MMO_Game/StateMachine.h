#include "State.h"

template <class object_type>

class StateMachine
{
private:

	object_type* _Owner;

	State<object_type*> _CurrentState;

	State<object_type*> _PreviousState;

	State<object_type*> _GlobalState;

public:

	StateMachine(object_type* owner):_Owner(owner), _CurrentState(NULL), _PreviousState(NULL), _GlobalState(NULL) {}

	void SetCurrentState(State<object_type*> s) {_CurrentState = s;}
	void SetPreviousState(State<object_type*> s) {_PreviousState = s;}
	void SetGlobalState(State<object_type*> s) {_GlobalState = s;}

	void Update()const
	{
		if(_GlobalState)
			_GlobalState->Execute(_Owner);

		if(_CurrentState)
			_CurrentState->Execute(_Owner);
	}

	void ChangeState(State<object_type>* newState)
	{
		assert(newState && "<StateMachine::ChangeState>: Trying to change to a null state");

		_PreviousState = _CurrentState;

		_CurrentState->Exit(_Owner);

		_CurrentState = newState;

		_CurrentState->Enter(_Owner);
	}

	State<object_type>* CurrentState() const{ return _CurrentState; }
	State<object_type>* PreviousState() const{ return _PreviousState; }
	State<object_type>* GlobalState() const{ return _GlobalState; }
};