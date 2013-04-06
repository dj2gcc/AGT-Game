#include"SteeringBehaviours.h"
#include "Character.h"

float SteeringBehaviours::RandomClamped()
{		
	return ( -1+( 1-(-1) )*( ( float )rand( ) )/( ( float )RAND_MAX ) );
} 

int SteeringBehaviours::rangedRandom(int i1, int i2)
{		
	return ( i1+( i2-i1 )*( ( float )rand( ) )/( ( float )RAND_MAX ) );
} 

Ogre::Vector3 SteeringBehaviours::_Wander(Physics o)
{
	double m_dWanderRadius = 20;
	double m_dWanderDistance = 300;
	double m_dWanderJitter = 20;

	Ogre::Vector3 targetLocal = Ogre::Vector3(RandomClamped() * m_dWanderJitter,0 , RandomClamped() * m_dWanderJitter);

	targetLocal.normalise();

	targetLocal *= m_dWanderRadius;

	//move the target into a position WanderDist in front of the agent
	targetLocal = targetLocal + Ogre::Vector3(0, 0, -m_dWanderDistance);
	return targetLocal;
}

Ogre::Vector3 SteeringBehaviours::_Patrol(Physics o, float tslf)
{
	Ogre::Vector3 difference = Ogre::Vector3(o._Position.x - _PatrolPoints[_NextPoint].x, 0, o._Position.z - _PatrolPoints[_NextPoint].z);
	Ogre::Vector3 distance = difference * difference;

	if(distance.x + distance.y <= 10000)
	{
		_Break += tslf;

		if(_Break >= (float)_BreakTime)
		{
			_NextPoint = rangedRandom(0, 4);
			_Break = 0.0f;
			_BreakTime = rangedRandom(1, 10);
		}
	}

	if(abs(difference.x) >= abs(difference.z))
	{
		return Ogre::Vector3(difference.x / difference.x, 0, difference.z / difference.x);
	}else
	{
		return Ogre::Vector3(difference.x / difference.z, 0, difference.z / difference.z);
	}
}

SteeringBehaviours::SteeringBehaviours(Ogre::Vector3 pos)
{
	_Flags &= 0x00;
	srand(time(0));

	_PatrolPoints[0] = Ogre::Vector3(pos.x + rangedRandom(-3000, 3000), 0, pos.y + rangedRandom(-4000, -4000));
	_PatrolPoints[1] = Ogre::Vector3(pos.x + rangedRandom(-5000, 5000), 0, pos.y + rangedRandom(-3000, -3000));
	_PatrolPoints[2] = Ogre::Vector3(pos.x + rangedRandom(-6000, 6000), 0, pos.y + rangedRandom(-6000, -6000));
	_PatrolPoints[3] = Ogre::Vector3(pos.x + rangedRandom(-1000, 1000), 0, pos.y + rangedRandom(-1000, -1000));
	_PatrolPoints[4] = Ogre::Vector3(pos.x + rangedRandom(-4000, 4000), 0, pos.y + rangedRandom(-4000, -4000));
	_NextPoint = 1;
	_Break = 0.0f;
	_BreakTime = 5;
}

SteeringBehaviours::~SteeringBehaviours()
{
}

void SteeringBehaviours::convertToWorld(Physics &o)
{

}

void SteeringBehaviours::steer(Character* o, float tslf)
{
	if(_Flags & WANDER)
	{
		o->setDirection(_Wander(o->getPhysics()));
		o->setVelocity(Ogre::Vector3(0, 0, 0.2));
	}else
		if(_Flags & PATROL)
		{
			o->setDirection(_Patrol(o->getPhysics(), tslf));
			o->setVelocity(Ogre::Vector3(0, 0, 0.2));
		}
}
