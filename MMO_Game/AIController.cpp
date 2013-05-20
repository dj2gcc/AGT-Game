#include "AIController.h"
#include "Event.h"

AIController::AIController(Character* object)
{
	_Steering = new SteeringBehaviours(object->getPosition());
	_Controlled = object;
	_Steering->flipPatrol();
	_EventID = -1;

	_World->addEvent(new Event(_Controlled, 1000.0f, EventDelegate::from_method<AIController, &AIController::aggro>(this), _EventID));

	_Cooldown = 0;
	_CurrentState = _Controlled->getStateMachine()->CurrentState()->getStateName();
}

AIController::~AIController()
{
}

bool AIController::HandleMessage(Telegram& msg)
{
	if(msg.type == "CombatEnd")
	{
		_Steering->setChaseData(NULL, 90);
		_Steering->flipChase();
		_Steering->flipPatrol();
	}

	_Controlled->HandleMessage(msg);
	return true;
}

void AIController::aggro(Character* c)
{
	_Controlled->_Target = c;

	_Steering->flipPatrol();

	_Steering->setChaseData(c, 90);
	_Steering->flipChase();

	if(_EventID >= 0)
	{
		_World->removeEvent(_EventID);
		_EventID = -1;
	}
}

void AIController::resetTarget()
{
	if(_Controlled->_Target)
	{
		_Steering->setChaseData(NULL, 90);
		_Steering->flipChase();
		_Steering->flipPatrol();

		_Controlled->_Target = NULL;

		if(_EventID < 0)
		{
			_World->addEvent(new Event(_Controlled, 1000.0f, EventDelegate::from_method<AIController, &AIController::aggro>(this), _EventID));
		}
	}
}

void AIController::update(Ogre::Real tslf)
{
	if(_CurrentState == _Controlled->getStateMachine()->CurrentState()->getStateName())
	{
		if(_CurrentState == "Dead")
		{
			_Controlled->update(tslf);
			return;
		}
	}else
	{
		_CurrentState = _Controlled->getStateMachine()->CurrentState()->getStateName();

		if(_CurrentState == "Dead")
		{
			_Controlled->_Target = NULL;

			if(_Steering->getChase())
			{
				_Steering->setChaseData(NULL, 90);
				_Steering->flipChase();
				_Steering->flipPatrol();
			}

			if(_EventID >= 0)
			{
				_World->removeEvent(_EventID);
				_EventID = -1;
			}

			_Controlled->update(tslf);

			return;
		}else
			if(_CurrentState == "Alive")
			{
				_World->addEvent(new Event(_Controlled, 1000.0f, EventDelegate::from_method<AIController, &AIController::aggro>(this), _EventID));
			}
	}

	_Steering->steer(_Controlled, tslf);
	_Controlled->update(tslf);

	if(_Controlled->_Target)
	{
		if(_Cooldown <= 0)
		{
			if(_Controlled->getCombat()->checkInRange(100))
			{
				_Controlled->getCombat()->castEffect("Attack");
				_Cooldown = 2;
			}
		}else
		{
			_Cooldown -= tslf;
		}
	}
}