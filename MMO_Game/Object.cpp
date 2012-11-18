#include "Object.h"

int Object::_NextID = 0;

Object::Object()
{
	_ID = _NextID;

	_NextID++;
}

Object::~Object()
{
	_NextID = 0;
}