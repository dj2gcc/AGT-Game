#include "PhysicsObject.h"


PhysicsObject::PhysicsObject(Ogre::String mesh) : MoveableObject(mesh)
{
	_Velocity = Ogre::Vector3(0, 0, 0);
	_Acceleration = Ogre::Vector3(0, -10, 0);
	_Force = Ogre::Vector3(0, 0, 0);

	_Mass = 70;

	_AirBorne = false;
}

PhysicsObject::~PhysicsObject()
{
	
}
	
void PhysicsObject::MoveUp()
{
	_MoveUp = (_MoveUp == false ? true : false);

	if(_MoveUp)
	{
		_AnimStateTop->setEnabled(false);
		_AnimStateBot->setEnabled(false); 

		_AnimStateTop = _Body->getAnimationState("RunTop");
		_AnimStateBot = _Body->getAnimationState("RunBase");

		_AnimStateTop->setLoop(true);
		_AnimStateBot->setLoop(true);
		_AnimStateTop->setEnabled(true);
		_AnimStateBot->setEnabled(true);
	}else
	{
		_AnimStateTop->setEnabled(false);
		_AnimStateBot->setEnabled(false);

		_AnimStateTop = _Body->getAnimationState("IdleTop");
		_AnimStateBot = _Body->getAnimationState("IdleBase");

		_AnimStateTop->setLoop(true);
		_AnimStateBot->setLoop(true);
		_AnimStateTop->setEnabled(true);
		_AnimStateBot->setEnabled(true);
	}
}

void PhysicsObject::MoveDown()
{
	_MoveDown = (_MoveDown == false ? true : false);

	if(_MoveDown)
	{
		_AnimStateTop->setEnabled(false);
		_AnimStateBot->setEnabled(false); 

		_AnimStateTop = _Body->getAnimationState("RunTop");
		_AnimStateBot = _Body->getAnimationState("RunBase");

		_AnimStateTop->setLoop(true);
		_AnimStateBot->setLoop(true);
		_AnimStateTop->setEnabled(true);
		_AnimStateBot->setEnabled(true);
	}else
	{
		_AnimStateTop->setEnabled(false);
		_AnimStateBot->setEnabled(false);

		_AnimStateTop = _Body->getAnimationState("IdleTop");
		_AnimStateBot = _Body->getAnimationState("IdleBase");

		_AnimStateTop->setLoop(true);
		_AnimStateBot->setLoop(true);
		_AnimStateTop->setEnabled(true);
		_AnimStateBot->setEnabled(true);
	}
}

void PhysicsObject::MoveLeft()
{
	_MoveLeft = (_MoveLeft == false ? true : false);
}

void PhysicsObject::MoveRight()
{
	_MoveRight = (_MoveRight == false ? true : false);
}

void PhysicsObject::MoveLeftSide()
{
	_MoveLeftSide = (_MoveLeftSide == false ? true : false);
}

void PhysicsObject::MoveRightSide()
{
	_MoveRightSide = (_MoveRightSide == false ? true : false);
}

void PhysicsObject::fitCamera(Ogre::Camera* c)
{
	_ChaseNode->attachObject(c);
	c->lookAt(_BodyNode->getPosition() + Ogre::Vector3(0, 0, 30));
}

void PhysicsObject::update(Ogre::Real tslf)
{
	if(_MoveUp == true && _MoveDown == false)
	{
		_BodyNode->translate(0,0, 800 * tslf, Ogre::Node::TS_LOCAL);
	}

	if(_MoveDown == true && _MoveUp == false)
	{
		_BodyNode->translate(0,0, -800 * tslf, Ogre::Node::TS_LOCAL);
	}

	if(_MoveLeft == true && _MoveRight == false)
	{
		_BodyNode->yaw(Ogre::Radian(0.8 * tslf));
	}
	
	if(_MoveRight == true && _MoveLeft == false)
	{
		_BodyNode->yaw(Ogre::Radian(-0.8 * tslf));
	}

	if(_MoveLeftSide == true && _MoveRightSide == false)
	{
		_BodyNode->translate(800 * tslf , 0, 0, Ogre::Node::TS_LOCAL);
	}

	if(_MoveRightSide == true && _MoveLeftSide == false)
	{
		_BodyNode->translate(-800 * tslf , 0, 0, Ogre::Node::TS_LOCAL);
	}

	if(_AnimStateTop)
	{
		_AnimStateTop->addTime(tslf);
		_AnimStateBot->addTime(tslf);
	}

	float ptslf = tslf * 20;

	if(_AirBorne)
	{
		_Velocity.y = _Velocity.y + (_Acceleration.y * ptslf);
		float s = (_Velocity.y * ptslf) + (0.5 * ((_Acceleration.y * ptslf) * (_Acceleration.y * ptslf)));
		_BodyNode->setPosition(_BodyNode->getPosition().x, _BodyNode->getPosition().y + s, _BodyNode->getPosition().z);
		if(_BodyNode->getPosition().y - _Height <= TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z))
		{
			_Velocity.y = 0;
			_AirBorne = false;
		}
	}else
	{
		_BodyNode->setPosition(_BodyNode->getPosition().x, TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z) + _Height, _BodyNode->getPosition().z);
	}
}

void PhysicsObject::Jump()
{
	//if(!_AirBorne)
	{
		_AirBorne = true;
		applyImpulse(40, 'y');
	}
}

void PhysicsObject::applyImpulse(float ft, char axis)
{
	switch(axis)
	{
	case 'x':
		_Velocity.x = (ft + (_Mass * _Velocity.x) / _Mass);
		break;
	case 'y':
		_Velocity.y = (ft + (_Mass * _Velocity.y) / _Mass);
		break;
	case 'z':
		_Velocity.z = (ft + (_Mass * _Velocity.z) / _Mass);
		break;
	default:
		Ogre::LogManager::getSingleton().logMessage("WARNING: Trying to apply impulse on an unknown axis.");
		break;
	}
}