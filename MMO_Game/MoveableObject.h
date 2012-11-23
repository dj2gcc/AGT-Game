#pragma once

#include "Object.h"


class MoveableObject : protected Object
{
protected:
	Ogre::Entity* _Body;
	Ogre::AnimationState* _AnimStateTop;
	Ogre::AnimationState* _AnimStateBot;
	Ogre::SceneNode* _BodyNode;
	Ogre::SceneNode* _ChaseNode;

	bool _MoveUp, _MoveDown, _MoveLeft, _MoveRight, _MoveLeftSide, _MoveRightSide;

	float _Height;

public:
	MoveableObject();
	MoveableObject(Ogre::String mesh);
	virtual ~MoveableObject();

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveLeftSide();
	virtual void MoveRightSide();
	virtual void Jump(){}

	virtual void fitCamera(Ogre::Camera* c);

	virtual void update(Ogre::Real tslf);
};