#include "StaticObject.h"


StaticObject::StaticObject(std::string model) : Object()
{
	_Body = OgreManager::Instance()->getSceneManager()->createEntity((Ogre::StringConverter::toString(_ID) + "Body"), model);
}

StaticObject::~StaticObject()
{
	OgreManager::Instance()->getSceneManager()->destroyEntity(_Body);
}