#pragma once

#include"Structs.h"
#include"Ogre.h"

class SteeringBehaviours
{
private:

	int _Flags;

	Ogre::Vector3 _Wander(Orientation o);

	inline float RandomClamped();
	
public:

	SteeringBehaviours();
	~SteeringBehaviours();

	void wanderOn();
	void wanderOff();

	void convertToWorld(Orientation &o);

	void steer(Orientation &o);
};