#include "AIController.h"
#include "BinTree.h"
#include "Event.h"
#include "Delegates.h"

AIController::AIController(Character* object)
{
	_Steering = new SteeringBehaviours(object->getPosition());
	_Controlled = object;
	_Steering->flipPatrol();

	CDelegate1<Character*> delegate;

	delegate.Add(object, AIController::aggro);

	Tree->addObject(new Event(&object->getPosition(), 300.0f, delegate));
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