#pragma once

#include "OgreManager.h"
#include "IdManager.h"


class Object
{
protected:
	int _ID;
public:
	Object();
	virtual ~Object();

	int getID() { return _ID; }
};