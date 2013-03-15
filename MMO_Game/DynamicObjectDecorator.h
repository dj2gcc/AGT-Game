#include "DynamicObject.h"

class DynamicObjectDecorator : public DynamicObject
{
public:

	virtual void update(Ogre::Real tslf) = 0;
};