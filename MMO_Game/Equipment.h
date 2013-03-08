#pragma once

#include "StaticObject.h"

class Character;

class Equipment : public StaticObject
{
private:

	std::string _Type;

	std::string _Name;

	int _Width;
	int _Height;

public:

	Equipment(std::string model, std::string name, std::string type);
	~Equipment();

	bool Equip(Character* c);

	std::string getType() { return _Type; }
	std::string getName() { return _Name; }
	int getWidth() { return _Width; }
	int getHeight() { return _Height; }
};