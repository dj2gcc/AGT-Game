#pragma once

#include "OgreManager.h"
#include "TerrainManager.h"

class Object
{
protected:
	static int _NextID;

	int _ID;

public:
	Object();
	virtual ~Object();

	int getID() { return _ID; }
};