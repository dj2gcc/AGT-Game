#pragma once 

#include "DynamicObject.h"
#include "StateMachine.h"
#include<string.h>
#include<vector>

#include "Telegram.h"
#include "MessageDispatcher.h"
#include "CombatFunctionality.h"
#include "Inventory.h"

class Character : public DynamicObject
{
protected:

	std::string _Name;
	CombatFunctionality* _Combat;
	Inventory* _Inventory;

	Equip _Equip;

	StateMachine<Character>* _States;

	int _Exp, _ExpToLvl, _Level;

public:
	Character* _Target;

	Character(Ogre::String mesh, std::string name);
	~Character();

	bool Equip(Equipment* e);

	bool HandleMessage(Telegram& msg);

	std::string getName(){ return _Name;}
	CombatFunctionality* getCombat() { return _Combat; }
	StateMachine<Character>* getStateMachine() { return _States; }
	Inventory* getInventory() { return _Inventory; }
	int getLevel() { return _Level; }
	int getExp() { return _Exp; }
	int getExpToLvl() { return _ExpToLvl; }

	void update(Ogre::Real tslf);
};