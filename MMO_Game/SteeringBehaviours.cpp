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

	targetLocal = targetLocal + Ogre::Vector3(0, 0, -m_dWanderDistance);
	return targetLocal;
}

void SteeringBehaviours::_Patrol(Character* o, float tslf)
{
	Ogre::Vector3 difference = Ogre::Vector3(o->getPhysics()._Position.x - _PatrolPoints[_NextPoint].x, 0, o->getPhysics()._Position.z - _PatrolPoints[_NextPoint].z);
	double distance = sqrt((difference.x * difference.x) + (difference.z * difference.z));

	if(distance <= 100)
	{
		_Break += tslf;

		if(_Break >= (float)_BreakTime)
		{
			_NextPoint = rangedRandom(0, 4);
			_Break = 0.0f;
			_BreakTime = rangedRandom(1, 10);
		}

		o->setVelocity(Ogre::Vector3(0, 0, 0));
	}else
	{
		o->setVelocity(Ogre::Vector3(0, 0, 0.2));
	}

	if(abs(difference.x) >= abs(difference.z))
	{
		if(difference.x < 0)
		{
			o->setDirection(Ogre::Vector3(difference.x / (difference.x * -1), 0, difference.z / (difference.x * -1)));
		}else
		{
			o->setDirection(Ogre::Vector3(difference.x / difference.x, 0, difference.z / difference.x));
		}
	}else
	{
		if(difference.z < 0)
		{
			o->setDirection(Ogre::Vector3(difference.x / (difference.z * -1), 0, difference.z / (difference.z * -1)));
		}else
		{
			o->setDirection(Ogre::Vector3(difference.x / difference.z, 0, difference.z / difference.z));
		}
	}
}

void SteeringBehaviours::_Chase(Character* o)
{
	if(!_ChaseTarget)
		return;

	Ogre::Vector3 difference = Ogre::Vector3(o->getPhysics()._Position.x - _ChaseTarget->getPosition().x, 0, o->getPhysics()._Position.z - _ChaseTarget->getPosition().z);
	double distance = sqrt((difference.x * difference.x) + (difference.z * difference.z));

	if(distance <= _Range)
	{
		o->setVelocity(Ogre::Vector3(0,0,0));
		return;
	}else
	{
		o->setVelocity(Ogre::Vector3(0, 0, 0.2));

		if(abs(difference.x) >= abs(difference.z))
		{
			if(difference.x < 0)
			{
				o->setDirection(Ogre::Vector3(difference.x / (difference.x * -1), 0, difference.z / (difference.x * -1)));
			}else
			{
				o->setDirection(Ogre::Vector3(difference.x / difference.x, 0, difference.z / difference.x));
			}
		}else
		{
			if(difference.z < 0)
			{
				o->setDirection(Ogre::Vector3(difference.x / (difference.z * -1), 0, difference.z / (difference.z * -1)));
			}else
			{
				o->setDirection(Ogre::Vector3(difference.x / difference.z, 0, difference.z / difference.z));
			}
		}
	}
}

void SteeringBehaviours::setChaseData(Character* tar, double r)
{
	_ChaseTarget = tar;
	_Range = r > 0 ? r : 10;
}

SteeringBehaviours::SteeringBehaviours(Ogre::Vector3 pos)
{
	_Flags &= 0x00;
	srand(time(0));

	_PatrolPoints[0] = Ogre::Vector3(pos.x + rangedRandom(-1000, 1000), 0, pos.y + rangedRandom(-1000, 1000));
	_PatrolPoints[1] = Ogre::Vector3(pos.x + rangedRandom(-1000, 1000), 0, pos.y + rangedRandom(-1000, 1000));
	_PatrolPoints[2] = Ogre::Vector3(pos.x + rangedRandom(-1000, 1000), 0, pos.y + rangedRandom(-1000, 1000));
	_PatrolPoints[3] = Ogre::Vector3(pos.x + rangedRandom(-1000, 1000), 0, pos.y + rangedRandom(-1000, 1000));
	_PatrolPoints[4] = Ogre::Vector3(pos.x + rangedRandom(-1000, 1000), 0, pos.y + rangedRandom(-1000, 1000));
	_NextPoint = 1;
	_Break = 0.0f;
	_BreakTime = 3;

	_ChaseTarget = NULL;
	_Range = 100;
}

SteeringBehaviours::~SteeringBehaviours()
{
}

void SteeringBehaviours::convertToWorld(Physics &o)
{

}

void SteeringBehaviours::steer(Character* o, float tslf)
{
	if(_Flags & CHASE)
	{
		_Chase(o);
	}

	if(_Flags & WANDER)
	{
		o->setDirection(_Wander(o->getPhysics()));
		o->setVelocity(Ogre::Vector3(0, 0, 0.2));
	}

	if(_Flags & PATROL)
	{
		_Patrol(o, tslf);
	}
}
