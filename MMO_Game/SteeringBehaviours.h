#pragma once

#include"Structs.h"
#include"Ogre.h"

#define WANDER 0x01
#define PATROL 0x02

class SteeringBehaviours
{
private:

	char _Flags;

	Ogre::Vector3 _Wander(Orientation o);
	Ogre::Vector3 _Patrol(Orientation o, float tslf);

	Ogre::Vector3 _PatrolPoints[5];
	int _NextPoint;
	float _Break;
	int _BreakTime;

	inline float RandomClamped();
	inline int rangedRandom(int i1, int i2);
	
public:

	SteeringBehaviours(Ogre::Vector3 pos);
	~SteeringBehaviours();

	void flipWander() { _Flags ^= WANDER; }
	void flipPatrol() { _Flags ^= PATROL; }

	bool getWander() { return _Flags & WANDER; }
	bool getPatrol() { return _Flags & PATROL; }

	void convertToWorld(Orientation &o);

	void steer(Orientation &o, float tslf);
};