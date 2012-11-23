#include "Object.h"

int Object::_NextID = 1;

Object::Object()
{
	_ID = _NextID;

	_NextID++;
}

Object::~Object()
{
}