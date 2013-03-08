#include"SteeringBehaviours.h"

float SteeringBehaviours::RandomClamped()
{		
	return ( -1+( 1-(-1) )*( ( float )rand( ) )/( ( float )RAND_MAX ) );
} 

Ogre::Vector3 SteeringBehaviours::_Wander(Orientation o)
{
	srand(time(0));

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

SteeringBehaviours::SteeringBehaviours()
{
	_Flags = 0;
}

SteeringBehaviours::~SteeringBehaviours()
{
}

void SteeringBehaviours::wanderOn()
{
	_Flags = 1;
}

void SteeringBehaviours::wanderOff()
{
	_Flags = 0;
}

void SteeringBehaviours::convertToWorld(Orientation &o)
{

}

void SteeringBehaviours::steer(Orientation &o)
{
	if(_Flags == 1)
	{
		o.facing =  _Wander(o);
	}
}
