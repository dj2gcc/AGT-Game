#pragma once

#include"Structs.h"
#include"Ogre.h"

class Character;

#define WANDER 0x01
#define PATROL 0x02
#define CHASE 0x04

class SteeringBehaviours 
{
private:
	char _Flags;

	Ogre::Vector3 _Wander(Physics o);
	void _Patrol(Character* o, float tslf);
	void _Chase(Character* o);

	Ogre::Vector3 _PatrolPoints[5];
	int _NextPoint;
	float _Break;
	int _BreakTime;

	Character* _ChaseTarget;
	double _Range;

	inline float RandomClamped();
	inline int rangedRandom(int i1, int i2);
	
public:

	SteeringBehaviours(Ogre::Vector3 pos);
	~SteeringBehaviours();

	void setChaseData(Character* tar, double r);

	void flipWander() { _Flags ^= WANDER; }
	void flipPatrol() { _Flags ^= PATROL; }
	void flipChase() { _Flags ^= CHASE; }

	bool getWander() { return _Flags & WANDER; }
	bool getPatrol() { return _Flags & PATROL; }
	bool getChase() { return _Flags & CHASE; }

	void convertToWorld(Physics &o);

	void steer(Character* o, float tslf);
};