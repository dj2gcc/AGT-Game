#pragma once

#include "Controller.h"
#include "SteeringBehaviours.h"

class AIController : public Controller
{
private:

	SteeringBehaviours* _Steering;

public:

	AIController(Character* object);
	~AIController();

	void update(Ogre::Real tslf);
};