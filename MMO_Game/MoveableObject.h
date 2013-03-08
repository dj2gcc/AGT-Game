#pragma once

#include "Object.h"
#include "SteeringBehaviours.h"

class MoveableObject : protected Object
{
protected:
	Ogre::Real _LocalTimer;

	Orientation _Orientation;

	Physics _Motion;

	Ogre::Entity* _Body;
	Ogre::AnimationState* _AnimStateTop;
	Ogre::AnimationState* _AnimStateBot;
	Ogre::SceneNode* _BodyNode;
	Ogre::SceneNode* _ChaseNode;

	bool _MoveUp, _MoveDown, _RotateLeft, _RotateRight, _MoveLeftSide, _MoveRightSide;

	float _Height;

	SteeringBehaviours* _Steering;

public:
	MoveableObject();
	MoveableObject(Ogre::String mesh);
	virtual ~MoveableObject();

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void RotateLeft();
	virtual void RotateRight();
	virtual void MoveLeftSide();
	virtual void MoveRightSide();
	virtual void Jump(){}

	virtual void fitCamera(Ogre::Camera* c);

	virtual void update(Ogre::Real tslf);
};