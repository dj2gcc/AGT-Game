#include"SteeringBehaviours.h"

float SteeringBehaviours::RandomClamped()
{		
	return ( -1+( 1-(-1) )*( ( float )rand( ) )/( ( float )RAND_MAX ) );
} 

int SteeringBehaviours::rangedRandom(int i1, int i2)
{		
	return ( i1+( i2-i1 )*( ( float )rand( ) )/( ( float )RAND_MAX ) );
} 

Ogre::Vector3 SteeringBehaviours::_Wander(Orientation o)
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

Ogre::Vector3 SteeringBehaviours::_Patrol(Orientation o, float tslf)
{
	Ogre::Vector3 difference = Ogre::Vector3(o.position.x - _PatrolPoints[_NextPoint].x, o.position.y - _PatrolPoints[_NextPoint].y, 0);
	Ogre::Vector3 distance = difference * difference;

	if(distance.x + distance.y <= 100)
	{
		_Break += tslf;

		if(_Break >= (float)_BreakTime)
		{
			_NextPoint = rangedRandom(0, 4);
			_Break = 0.0f;
			_BreakTime = rangedRandom(1, 10);
		}
	}

	if(abs(difference.x) >= abs(difference.y))
	{
		return Ogre::Vector3(difference.x / difference.x, difference.y / difference.x, 0);
	}else
	{
		return Ogre::Vector3(difference.x / difference.y, difference.y / difference.y, 0);
	}
}

SteeringBehaviours::SteeringBehaviours(Ogre::Vector3 pos)
{
	_Flags &= 0x00;
	srand(time(0));

	Ogre::Vector3 _PatrolPoints[5];
	_PatrolPoints[0] = Ogre::Vector3(pos.x + rangedRandom(-300, 300), pos.y + rangedRandom(-400, -400), 0);
	_PatrolPoints[1] = Ogre::Vector3(pos.x + rangedRandom(-500, 500), pos.y + rangedRandom(-300, -300), 0);
	_PatrolPoints[2] = Ogre::Vector3(pos.x + rangedRandom(-600, 600), pos.y + rangedRandom(-600, -600), 0);
	_PatrolPoints[3] = Ogre::Vector3(pos.x + rangedRandom(-100, 100), pos.y + rangedRandom(-100, -100), 0);
	_PatrolPoints[4] = Ogre::Vector3(pos.x + rangedRandom(-400, 400), pos.y + rangedRandom(-400, -400), 0);
	_NextPoint = 1;
	_Break = 0.0f;
	_BreakTime = 5;
}

SteeringBehaviours::~SteeringBehaviours()
{
}

void SteeringBehaviours::convertToWorld(Orientation &o)
{

}

void SteeringBehaviours::steer(Orientation &o, float tslf)
{
	if(_Flags & WANDER)
	{
		o.facing =  _Wander(o);
	}

	if(_Flags & PATROL)
	{
		o.facing = _Patrol(o, tslf);
	}
}
