#pragma once 

#include "MoveableObject.h"

class PhysicsObject : public MoveableObject
{
protected:

	Ogre::Vector3 _Velocity;
	Ogre::Vector3 _Acceleration;
	Ogre::Vector3 _Force;

	float _Mass;

	bool _AirBorne;

public:
	PhysicsObject(Ogre::String mesh);
	~PhysicsObject();
	
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveLeftSide();
	void MoveRightSide();
	void Jump();

	void fitCamera(Ogre::Camera* c);

	void update(Ogre::Real tslf);

	void applyImpulse(float ft, char axis);
};