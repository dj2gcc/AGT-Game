#include "DynamicObject.h"
#include "TerrainManager.h"

DynamicObject::DynamicObject() : Object()
{
	_ID = IDManager->newCharacterID();

	_DefaultAnimation = NULL;
	_AdditionalAnimation = NULL;

	_Body = NULL;
	_BodyNode = NULL;

	_Height = 0;

	_States._Dance = "Dance";
	_States._DrawWeapons = "DrawSwords";
	_States._IdleBase = "IdleBase"; 
	_States._IdleTop = "IdleTop";
	_States._JumpEnd = "JumpEnd";
	_States._JumpLoop = "JumpLoop";
	_States._JumpStart = "JumpStart";
	_States._RunBase = "RunBase";
	_States._RunTop = "RunTop"; 
	_States._Attack1 = "SliceHorizontal";
	_States._Attack2 = "SliceVertical";
	
}

DynamicObject::DynamicObject(Ogre::String model, Ogre::Vector3 p) : Object()
{
	_DefaultAnimation = NULL;
	_AdditionalAnimation = NULL;

	_States._Dance = "Dance";
	_States._DrawWeapons = "DrawSwords";
	_States._IdleBase = "IdleBase"; 
	_States._IdleTop = "IdleTop";
	_States._JumpEnd = "JumpEnd";
	_States._JumpLoop = "JumpLoop";
	_States._JumpStart = "JumpStart";
	_States._RunBase = "RunBase";
	_States._RunTop = "RunTop"; 
	_States._Attack1 = "SliceHorizontal";
	_States._Attack2 = "SliceVertical";

	_ID = IDManager->newCharacterID();
	_Body = OgreManager::Instance()->getSceneManager()->createEntity(("B" + Ogre::StringConverter::toString(_ID)), model);
	
	_Body->getSkeleton()->setBlendMode(Ogre::SkeletonAnimationBlendMode::ANIMBLEND_CUMULATIVE);

	setDefaultAnimation(Idle);

	_BodyNode = OgreManager::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::StringConverter::toString(_ID) + "Node", p);
	_ChaseNode = _BodyNode->createChildSceneNode(_BodyNode->getName() + "Chase");
	_BodyNode->attachObject(_Body);
	_ChaseNode->translate(0, 10, -30, Ogre::Node::TS_PARENT);

	_BodyNode->scale(20, 20, 20);

	_Height = _Body->getBoundingRadius();

	_BodyNode->setPosition(_BodyNode->getPosition().x, TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z) + _Height, _BodyNode->getPosition().z);

	_Motion._Position = _BodyNode->getPosition();
	_Motion._Facing = Ogre::Vector3(1, _Motion._Position.y, 0);

	_Motion._Velocity = _Motion._Force = _Motion._Rotation = Ogre::Vector3(0,0,0);
	_Motion._Acceleration = Ogre::Vector3(0, -10, 0);
	_Motion._Mass = 70;
	_Motion._Airborne = false;

	
	_Motion._MovementSpeed = 800;
	_Motion._RotationSpeed = 0.8;
}

DynamicObject::~DynamicObject()
{
	_ChaseNode->detachAllObjects();
	OgreManager::Instance()->getSceneManager()->getRootSceneNode()->removeAndDestroyChild(Ogre::StringConverter::toString(Object::_ID) + "Node");
	OgreManager::Instance()->getSceneManager()->destroyEntity(_Body);
}

void DynamicObject::setPosition(Ogre::Vector3 p)
{
	_BodyNode->setPosition(p);
	_Motion._Position = p;
}

void DynamicObject::defineAnimationStates(AnimationStates states)
{
	_States = states;
}

void DynamicObject::setDefaultAnimation(Animation animation)
{
	std::string animName;

	animName = getAnimationName(animation);

	if(_AdditionalAnimation && _AnimationPlan == Overriding || animName == "" || _DefaultAnimation && animName == _DefaultAnimation->getAnimationName())
		return;

	if(_DefaultAnimation)
	{
		if(_DefaultAnimation->getAnimationName() == _States._IdleBase)
		{
			_DefaultAnimation->setEnabled(false);
			_DefaultAnimation = _Body->getAnimationState(_States._IdleTop);
			_DefaultAnimation->setEnabled(false);
		}else
			if(_DefaultAnimation->getAnimationName() == _States._RunBase)
			{
				_DefaultAnimation->setEnabled(false);
				_DefaultAnimation = _Body->getAnimationState(_States._RunTop);
				_DefaultAnimation->setEnabled(false);
			}else
			{
				_DefaultAnimation->setEnabled(false);
			}
	}

	if(animation == Idle)
	{
		_DefaultAnimation = _Body->getAnimationState(_States._IdleTop);
		_DefaultAnimation->setLoop(true);
		_DefaultAnimation->setEnabled(true);
		_DefaultAnimation = _Body->getAnimationState(_States._IdleBase);
		_DefaultAnimation->setLoop(true);
		_DefaultAnimation->setEnabled(true);
	}else
		if(animation == Run)
		{
			_DefaultAnimation = _Body->getAnimationState(_States._RunTop);
			_DefaultAnimation->setLoop(true);
			_DefaultAnimation->setEnabled(true);
			_DefaultAnimation = _Body->getAnimationState(_States._RunBase);
			_DefaultAnimation->setLoop(true);
			_DefaultAnimation->setEnabled(true);
		}else
		{
			_DefaultAnimation = _Body->getAnimationState(animName);
			_DefaultAnimation->setLoop(true);
			_DefaultAnimation->setEnabled(true);
		}
}

void DynamicObject::setAdditionalAnimation(Animation animation, AnimationPlan plan)
{
	if(_AdditionalAnimation)
	{
		_AdditionalAnimation->setTimePosition(0);
		_AdditionalAnimation->setEnabled(false);
	}

	switch(plan)
	{
	case Overlaping:
		_AdditionalAnimation = _Body->getAnimationState(getAnimationName(animation));
		_AdditionalAnimation->setLoop(false);
		_AdditionalAnimation->setEnabled(true);
		break;
	case Overriding:

		if(_DefaultAnimation)
		{
			if(_DefaultAnimation->getAnimationName() == _States._IdleBase)
			{
				_DefaultAnimation->setEnabled(false);
				_Body->getAnimationState(_States._IdleTop)->setEnabled(false);
			}else
				if(_DefaultAnimation->getAnimationName() == _States._RunBase)
				{
					_DefaultAnimation->setEnabled(false);
					_Body->getAnimationState(_States._RunTop)->setEnabled(false);
				}else
				{
					_DefaultAnimation->setEnabled(false);
				}
		}

		_AdditionalAnimation = _Body->getAnimationState(getAnimationName(animation));
		_AdditionalAnimation->setLoop(false);
		_AdditionalAnimation->setEnabled(true);
		break;
	default:
		break;
	}

	_AnimationPlan = plan;
}

std::string DynamicObject::getAnimationName(Animation animation)
{
	switch(animation)
	{
	case Dance:
		return _States._Dance;
		break;
	case DrawWeapons:
		return _States._DrawWeapons;
		break;
	case Idle:
		return _States._IdleBase;
		break;
	case JumpEnd:
		return _States._JumpEnd;
		break;
	case JumpLoop:
		return _States._JumpLoop;
		break;
	case JumpStart:
		return _States._JumpStart;
		break;
	case Run:
		return _States._RunBase;
		break;
	case Attack1:
		return _States._Attack1;
		break;
	case Attack2:
		return _States._Attack2;
		break;
	default:
		return std::string("");
	}
}

void DynamicObject::fitCamera(Ogre::Camera* c)
{
	_ChaseNode->attachObject(c);
	c->lookAt(_BodyNode->getPosition() + Ogre::Vector3(0, 0, 30));
}

void DynamicObject::setDirection(Ogre::Vector3 dir)
{
	_Motion._Facing = dir;
	_BodyNode->setDirection(dir, Ogre::Node::TS_WORLD);
}
void DynamicObject::setVelocity(Ogre::Vector3 vel)
{
	_Motion._Velocity = vel;

	if(_Motion._Velocity.x == 0 && _Motion._Velocity.y == 0 && _Motion._Velocity.z == 0)
	{
		setDefaultAnimation(Idle);
	}else
	{
		setDefaultAnimation(Run);
	}
}

void DynamicObject::adjustVelocity(Ogre::Vector3 vel)
{
	_Motion._Velocity += vel;

	if(_Motion._Velocity.x == 0 && _Motion._Velocity.y == 0 && _Motion._Velocity.z == 0)
	{
		setDefaultAnimation(Idle);
	}else
	{
		setDefaultAnimation(Run);
	}
}

void DynamicObject::setRotation(Ogre::Vector3 rot)
{
	_Motion._Rotation = rot;
}

void DynamicObject::Jump()
{
	if(!_Motion._Airborne)
	{
		_Motion._Airborne = true;

		setAdditionalAnimation(JumpLoop, Overriding);

		_Motion._Velocity.y = (/*40*/ + (_Motion._Mass * _Motion._Velocity.y) / _Motion._Mass);
	}
}

void DynamicObject::updateAnimation(Ogre::Real tslf)
{
	if(_AdditionalAnimation)
	{
		_AdditionalAnimation->addTime(tslf);

		if(_AdditionalAnimation->hasEnded())
		{
			if(_AnimationPlan == Overriding)
			{
				_AdditionalAnimation->setTimePosition(0);
				_AdditionalAnimation->setEnabled(false);
				_AdditionalAnimation = NULL;

				if(_DefaultAnimation->getAnimationName() == _States._IdleBase)
				{
					_DefaultAnimation->setEnabled(true);
					_Body->getAnimationState(_States._IdleTop)->setEnabled(true);
				}else
					if(_DefaultAnimation->getAnimationName() == _States._RunBase)
					{
						_DefaultAnimation->setEnabled(true);
						_Body->getAnimationState(_States._RunTop)->setEnabled(true);
					}else
					{
						_DefaultAnimation->setEnabled(true);
					}
			}else
			{
				_AdditionalAnimation->setTimePosition(0);
				_AdditionalAnimation->setEnabled(false);
				_AdditionalAnimation = NULL;
			}
		}else
			if(_AnimationPlan == Overlaping)
			{
				if(_DefaultAnimation->getAnimationName() == _States._IdleBase)
				{
					_DefaultAnimation->addTime(tslf);
					_Body->getAnimationState(_States._IdleTop)->addTime(tslf);
				}else
					if(_DefaultAnimation->getAnimationName() == _States._RunBase)
					{
						_DefaultAnimation->addTime(tslf);
						_Body->getAnimationState(_States._RunTop)->addTime(tslf);
					}else
					{
						_DefaultAnimation->addTime(tslf);
					}
			}
	}else
	{
		if(_DefaultAnimation->getAnimationName() == _States._IdleBase)
		{
			_DefaultAnimation->addTime(tslf);
			_Body->getAnimationState(_States._IdleTop)->addTime(tslf);
		}else
			if(_DefaultAnimation->getAnimationName() == _States._RunBase)
			{
				_DefaultAnimation->addTime(tslf);
				_Body->getAnimationState(_States._RunTop)->addTime(tslf);
			}else
			{
				_DefaultAnimation->addTime(tslf);
			}
	}
}

void DynamicObject::update(Ogre::Real tslf)
{
	_BodyNode->yaw(Ogre::Radian(_Motion._Rotation.y * _Motion._RotationSpeed * tslf));

	_BodyNode->translate(_Motion._Velocity.x * _Motion._MovementSpeed * tslf , _Motion._Velocity.y * _Motion._MovementSpeed * tslf, _Motion._Velocity.z * _Motion._MovementSpeed * tslf, Ogre::Node::TS_LOCAL);

	updateAnimation(tslf);

	if(_Motion._Airborne)
	{
		_Motion._Velocity.y = _Motion._Velocity.y + (_Motion._Acceleration.y * (tslf * 20));
		float s = (_Motion._Velocity.y * (tslf * 20)) + (0.5 * ((_Motion._Acceleration.y * (tslf * 20)) * (_Motion._Acceleration.y * (tslf * 20))));
		_BodyNode->setPosition(_BodyNode->getPosition().x, _BodyNode->getPosition().y + s, _BodyNode->getPosition().z);
		if(_BodyNode->getPosition().y - _Height <= TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z))
		{
			_Motion._Velocity.y = 0;
			_Motion._Airborne = false;

			setAdditionalAnimation(JumpEnd, Overriding);
		}
	}else
	{
		_BodyNode->setPosition(_BodyNode->getPosition().x, TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z) + _Height, _BodyNode->getPosition().z);
	}

	_Motion._Position = _BodyNode->getPosition();
}