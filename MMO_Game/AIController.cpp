#include "AIController.h"
#include "BinTree.h"
#include "Event.h"

AIController::AIController(Character* object)
{
	_Steering = new SteeringBehaviours(object->getPosition());
	_Controlled = object;
	_Steering->flipPatrol();
}

AIController::~AIController()
{
}

void aggro(Character* c)
{
}

void AIController::update(Ogre::Real tslf)
{
	_Steering->steer(_Controlled, tslf);
	_Controlled->update(tslf);
}