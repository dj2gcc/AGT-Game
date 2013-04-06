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

	Physics _Motion;

	AnimationStates _States;

	Ogre::AnimationState* _DefaultAnimation;
	Ogre::AnimationState* _AdditionalAnimation;
	AnimationPlan _AnimationPlan;

	Ogre::Entity* _Body;
	Ogre::SceneNode* _BodyNode;
	Ogre::SceneNode* _ChaseNode;

	float _Height;

	SteeringBehaviours* _Steering;

public:
	DynamicObject();
	DynamicObject(Ogre::String model);
	virtual ~DynamicObject();

	void setDirection(Ogre::Vector3 dir);
	void adjustVelocity(Ogre::Vector3 vel);
	void setVelocity(Ogre::Vector3 vel);
	void setRotation(Ogre::Vector3 rot);
	void Jump();

	void defineAnimationStates(AnimationStates states);

	void setDefaultAnimation(Animation animation);

	void setAdditionalAnimation(Animation animation, AnimationPlan plan);

	std::string getAnimationName(Animation animation);

	void updateAnimation(Ogre::Real tslf);

	Ogre::AnimationState* AdditionalAnimation() const{ return _AdditionalAnimation; }
	Ogre::AnimationState* DefaultAnimation() const{ return _DefaultAnimation; }
	Ogre::Vector3 getPosition() { return _BodyNode->getPosition(); }
	Ogre::Real getCollisionRadius() { return _Body->getBoundingRadius(); }
	Physics getPhysics() { return _Motion; }

	void fitCamera(Ogre::Camera* c);

	virtual void update(Ogre::Real tslf);
};