#pragma once

#include "Object.h"
#include "SteeringBehaviours.h"
#include "Structs.h"

enum AnimationPlan
{
	Overriding = 0,
	Overlaping = 1
};

enum Animation
{
	Dance,
	DrawWeapons,
	Idle,
	JumpEnd,
	JumpLoop,
	JumpStart,
	Run,
	Attack1,
	Attack2
};

class DynamicObject : public Object
{
protected:
	Orientation _Orientation;

	Physics _Motion;

	AnimationStates _States;

	Ogre::AnimationState* _DefaultAnimation;
	Ogre::AnimationState* _AdditionalAnimation;
	AnimationPlan _AnimationPlan;

	Ogre::Entity* _Body;
	Ogre::SceneNode* _BodyNode;
	Ogre::SceneNode* _ChaseNode;

	bool _MoveUp, _MoveDown, _RotateLeft, _RotateRight, _MoveLeftSide, _MoveRightSide;

	float _Height;

	SteeringBehaviours* _Steering;

public:
	DynamicObject();
	DynamicObject(Ogre::String model);
	virtual ~DynamicObject();

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void RotateLeft();
	virtual void RotateRight();
	virtual void MoveLeftSide();
	virtual void MoveRightSide();
	virtual void Jump();

	void defineAnimationStates(AnimationStates states);

	void setDefaultAnimation(Animation animation);

	void setAdditionalAnimation(Animation animation, AnimationPlan plan);

	std::string getAnimationName(Animation animation);

	void updateAnimation(Ogre::Real tslf);

	Ogre::AnimationState* AdditionalAnimation() const{ return _AdditionalAnimation; }
	Ogre::AnimationState* DefaultAnimation() const{ return _DefaultAnimation; }

	virtual void fitCamera(Ogre::Camera* c);

	virtual void update(Ogre::Real tslf);
};