#include "MoveableObject.h"

MoveableObject::MoveableObject() : Object()
{
	_Body = NULL;
	_AnimStateTop = NULL;
	_AnimStateBot = NULL;
	_BodyNode = NULL;

	_MoveUp = false;
	_MoveDown = false;
	_MoveLeft = false; 
	_MoveRight = false;
	_MoveLeftSide = false;
	_MoveRightSide = false;

	_Height = 0;
}

MoveableObject::MoveableObject(Ogre::String mesh) : Object()
{
	_Body = OgreManager::Instance()->getSceneManager()->createEntity(Ogre::StringConverter::toString(Object::_ID) + "Body", mesh);
	
	_Body->getSkeleton()->setBlendMode(Ogre::SkeletonAnimationBlendMode::ANIMBLEND_CUMULATIVE);
	_AnimStateTop = _Body->getAnimationState("IdleTop");
	_AnimStateBot = _Body->getAnimationState("IdleBase");

	_AnimStateTop->setLoop(true);
	_AnimStateBot->setLoop(true);
	_AnimStateTop->setEnabled(true);
	_AnimStateBot->setEnabled(true);

	_BodyNode = OgreManager::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::StringConverter::toString(Object::_ID) + "Node", Ogre::Vector3(500, 200, 500));
	_ChaseNode = _BodyNode->createChildSceneNode(_BodyNode->getName() + "Chase");
	_BodyNode->attachObject(_Body);
	_ChaseNode->translate(0, 10, -30, Ogre::Node::TS_PARENT);

	_BodyNode->scale(20, 20, 20);

	_MoveUp = false;
	_MoveDown = false;
	_MoveLeft = false; 
	_MoveRight = false;
	_MoveLeftSide = false;
	_MoveRightSide = false;

	_Height = _Body->getBoundingRadius();
}

MoveableObject::~MoveableObject()
{
	//_ChaseNode->detachAllObjects();
	//_BodyNode->detachAllObjects();
	//_BodyNode->removeAndDestroyAllChildren();
	OgreManager::Instance()->getSceneManager()->getRootSceneNode()->removeAndDestroyChild(Ogre::StringConverter::toString(Object::_ID) + "Node");
	OgreManager::Instance()->getSceneManager()->destroyEntity(_Body);
}

void MoveableObject::MoveUp()
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

void MoveableObject::MoveDown()
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

void MoveableObject::MoveLeft()
{
	_MoveLeft = (_MoveLeft == false ? true : false);
}

void MoveableObject::MoveRight()
{
	_MoveRight = (_MoveRight == false ? true : false);
}

void MoveableObject::MoveLeftSide()
{
	_MoveLeftSide = (_MoveLeftSide == false ? true : false);
}

void MoveableObject::MoveRightSide()
{
	_MoveRightSide = (_MoveRightSide == false ? true : false);
}

void MoveableObject::fitCamera(Ogre::Camera* c)
{
	_ChaseNode->attachObject(c);
	c->lookAt(_BodyNode->getPosition() + Ogre::Vector3(0, 0, 30));
}

void MoveableObject::update(Ogre::Real tslf)
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

	_BodyNode->setPosition(_BodyNode->getPosition().x, TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z) + _Height, _BodyNode->getPosition().z);
}