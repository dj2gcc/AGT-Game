#pragma once

#include"SkillList.h"

class Character;

class ApplicationMethodBase
{
protected:

	SkillBase* _Skill;

	int _SenderID;

public:

	ApplicationMethodBase(SkillBase* s, int senderId){ _Skill = s; _SenderID = senderId; }

	virtual ~ApplicationMethodBase(){}

	SkillBase* getSkill() { return _Skill; }
	int getSenderID() { return _SenderID; }

	virtual void update(Character* c, float tslf) {}
};