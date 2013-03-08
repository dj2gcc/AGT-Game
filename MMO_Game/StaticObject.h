#include "Object.h"

class StaticObject : public Object
{
private:

	Ogre::Entity* _Body;

public:

	StaticObject(std::string model);
	virtual ~StaticObject();

	Ogre::Entity* getBody() { return _Body; }
};
