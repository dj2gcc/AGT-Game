#pragma once

#include"SkillList.h"

class Character;

class ApplicationMethodBase
{
protected:

	SkillBase* _Skill;

public:

	ApplicationMethodBase(SkillBase* s){ _Skill = s; }

	virtual ~ApplicationMethodBase(){}

	SkillBase* getSkill() { return _Skill; }

	virtual void update(Character* c, float tslf) {}
};