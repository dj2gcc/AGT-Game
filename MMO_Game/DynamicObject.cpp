#include "DynamicObject.h"
#include "TerrainManager.h"

DynamicObject::DynamicObject() : Object()
{
	_ID = IDManager->newCharacterID();

	_DefaultAnimation = NULL;
	_AdditionalAnimation = NULL;

	_Body = NULL;
	_BodyNode = NULL;

	_MoveUp = false;
	_MoveDown = false;
	_RotateLeft = false; 
	_RotateRight = false;
	_MoveLeftSide = false;
	_MoveRightSide = false;

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

DynamicObject::DynamicObject(Ogre::String model) : Object()
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
	_Body = OgreManager::Instance()->getSceneManager()->createEntity((Ogre::StringConverter::toString(_ID) + "Body"), model);
	
	_Body->getSkeleton()->setBlendMode(Ogre::SkeletonAnimationBlendMode::ANIMBLEND_CUMULATIVE);

	setDefaultAnimation(Idle);

	_BodyNode = OgreManager::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::StringConverter::toString(_ID) + "Node", Ogre::Vector3(500, 200, 500));
	_ChaseNode = _BodyNode->createChildSceneNode(_BodyNode->getName() + "Chase");
	_BodyNode->attachObject(_Body);
	_ChaseNode->translate(0, 10, -30, Ogre::Node::TS_PARENT);

	_BodyNode->scale(20, 20, 20);

	_MoveUp = false;
	_MoveDown = false;
	_RotateLeft = false; 
	_RotateRight = false;
	_MoveLeftSide = false;
	_MoveRightSide = false;

	_Height = _Body->getBoundingRadius();

	_Orientation.position = _BodyNode->getPosition();
	_Orientation.facing = Ogre::Vector3(1, _Orientation.position.y, 0);

	_Motion.velocity = _Motion.force = Ogre::Vector3(0,0,0);
	_Motion.acceleration = Ogre::Vector3(0, -10, 0);
	_Motion.mass = 70;
	_Motion.airborne = false;
}

DynamicObject::~DynamicObject()
{
	_ChaseNode->detachAllObjects();
	OgreManager::Instance()->getSceneManager()->getRootSceneNode()->removeAndDestroyChild(Ogre::StringConverter::toString(Object::_ID) + "Node");
	OgreManager::Instance()->getSceneManager()->destroyEntity(_Body);
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

void DynamicObject::MoveUp()
{
	_MoveUp = (_MoveUp == false ? true : false);

	if(_Motion.airborne)
		return;

	if(_MoveUp)
	{
		setDefaultAnimation(Run);
	}else
	{
		setDefaultAnimation(Idle);
	}
}

void DynamicObject::MoveDown()
{
	_MoveDown = (_MoveDown == false ? true : false);

	if(_Motion.airborne)
		return;

	if(_MoveDown)
	{
		setDefaultAnimation(Run);
	}else
	{
		setDefaultAnimation(Idle);
	}
}

void DynamicObject::RotateLeft()
{
	_RotateLeft = (_RotateLeft == false ? true : false);
}

void DynamicObject::RotateRight()
{
	_RotateRight = (_RotateRight == false ? true : false);
}

void DynamicObject::MoveLeftSide()
{
	_MoveLeftSide = (_MoveLeftSide == false ? true : false);
}

void DynamicObject::MoveRightSide()
{
	_MoveRightSide = (_MoveRightSide == false ? true : false);
}

void DynamicObject::Jump()
{
	if(!_Motion.airborne)
	{
		_Motion.airborne = true;

		setAdditionalAnimation(JumpLoop, Overriding);

		_Motion.velocity.y = (40 + (_Motion.mass * _Motion.velocity.y) / _Motion.mass);
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
	if(_MoveUp == true && _MoveDown == false)
	{
		_BodyNode->translate(0,0, 800 * tslf, Ogre::Node::TS_LOCAL);
	}

	if(_MoveDown == true && _MoveUp == false)
	{
		_BodyNode->translate(0,0, -800 * tslf, Ogre::Node::TS_LOCAL);
	}

	if(_RotateLeft == true && _RotateRight == false)
	{
		_BodyNode->yaw(Ogre::Radian(0.8 * tslf));
	}
	
	if(_RotateRight == true && _RotateLeft == false)
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

	updateAnimation(tslf);

	if(_Motion.airborne)
	{
		_Motion.velocity.y = _Motion.velocity.y + (_Motion.acceleration.y * (tslf * 20));
		float s = (_Motion.velocity.y * (tslf * 20)) + (0.5 * ((_Motion.acceleration.y * (tslf * 20)) * (_Motion.acceleration.y * (tslf * 20))));
		_BodyNode->setPosition(_BodyNode->getPosition().x, _BodyNode->getPosition().y + s, _BodyNode->getPosition().z);
		if(_BodyNode->getPosition().y - _Height <= TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z))
		{
			_Motion.velocity.y = 0;
			_Motion.airborne = false;

			setAdditionalAnimation(JumpEnd, Overriding);
		}
	}else
	{
		_BodyNode->setPosition(_BodyNode->getPosition().x, TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z) + _Height, _BodyNode->getPosition().z);
	}
}