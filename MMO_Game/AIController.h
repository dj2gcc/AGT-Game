#pragma once

#include "Controller.h"
#include "SteeringBehaviours.h"

class AIController : public Controller
{
private:

	SteeringBehaviours* _Steering;

	float _Cooldown;

	int _EventID;

	std::string _CurrentState;

public:

	AIController(Character* object);
	~AIController();

	bool HandleMessage(Telegram& msg);

	void resetTarget();

	void aggro(Character* c);

	void update(Ogre::Real tslf);
};