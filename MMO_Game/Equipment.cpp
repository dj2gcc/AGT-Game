#include "Equipment.h"
#include "Character.h"

Equipment::Equipment(std::string model, std::string name, std::string type) : StaticObject(model)
{
	_Type = type;
	_Name = name;
	_ID = IDManager->newItemID();
}

Equipment::~Equipment()
{
}

bool Equipment::Equip(Character* c)
{
	if(c->Equip(this))
	{
		return true;
	}else
	{
		return false;
	}
}