#include "States.h"

template <class object_type>

class StateMachine
{
private:

	object_type* _Owner;

	StateBase<object_type>* _CurrentState;

	StateBase<object_type>* _PreviousState;

	StateBase<object_type>* _GlobalState;

public:

	StateMachine(object_type* owner):_Owner(owner)
	{
		_CurrentState = NULL;
		_PreviousState = NULL;
		_GlobalState = NULL;
	}

	void SetCurrentState(StateBase<object_type>* s) {_CurrentState = s;}
	void SetPreviousState(StateBase<object_type>* s) {_PreviousState = s;}
	void SetGlobalState(StateBase<object_type>* s) {_GlobalState = s;}

	void Update(float tslf)const
	{
		if(_GlobalState)
			_GlobalState->Execute(_Owner, tslf);

		if(_CurrentState)
			_CurrentState->Execute(_Owner, tslf);
	}

	void ChangeState(StateBase<object_type>* newState)
	{
		assert(newState && "<StateMachine::ChangeState>: Trying to change to a null state");

		_CurrentState->Exit(_Owner);

		_PreviousState = _CurrentState;

		_CurrentState = newState;

		_CurrentState->Enter(_Owner);
	}

	StateBase<object_type>* CurrentState() const{ return _CurrentState; }
	StateBase<object_type>* PreviousState() const{ return _PreviousState; }
	StateBase<object_type>* GlobalState() const{ return _GlobalState; }
};