#pragma once

#include "SkillBase.h"


class Attack : public SkillBase
{
public:

	Attack();
	Attack(SkillBase* a)
	{
		_Type = a->getType();
		_Name = a->getName();
		_BaseDamage = a->getBaseDamage();
		_Damage = a->getDamage();
		_Cast = a->getCast();
		_Duration = a->getDuration();
		_Progress = a->getProgress();
		_Applied = a->getApplied();
		_Range = a->getRange();
	}
	~Attack();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);

	SkillBase* getCopy(SkillBase* s);
};

class Pain : public SkillBase
{
public:

	Pain();
	Pain(SkillBase* a)
	{
		_Type = a->getType();
		_Name = a->getName();
		_BaseDamage = a->getBaseDamage();
		_Damage = a->getDamage();
		_Cast = a->getCast();
		_Duration = a->getDuration();
		_Progress = a->getProgress();
		_Applied = a->getApplied();
		_Range = a->getRange();
	}
	~Pain();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);

	SkillBase* getCopy(SkillBase* s);
};

class Heal : public SkillBase
{
public:

	Heal();
	Heal(SkillBase* a)
	{
		_Type = a->getType();
		_Name = a->getName();
		_BaseDamage = a->getBaseDamage();
		_Damage = a->getDamage();
		_Cast = a->getCast();
		_Duration = a->getDuration();
		_Progress = a->getProgress();
		_Applied = a->getApplied();
		_Range = a->getRange();
	}
	~Heal();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);

	SkillBase* getCopy(SkillBase* s);
};

class StaminaBuff : public SkillBase
{
public:

	StaminaBuff();
	StaminaBuff(SkillBase* a)
	{
		_Type = a->getType();
		_Name = a->getName();
		_BaseDamage = a->getBaseDamage();
		_Damage = a->getDamage();
		_Cast = a->getCast();
		_Duration = a->getDuration();
		_Progress = a->getProgress();
		_Applied = a->getApplied();
		_Range = a->getRange();
	}
	~StaminaBuff();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);

	SkillBase* getCopy(SkillBase* s);
};

class PowerDebuff : public SkillBase
{
public:

	PowerDebuff();
	PowerDebuff(SkillBase* a)
	{
		_Type = a->getType();
		_Name = a->getName();
		_BaseDamage = a->getBaseDamage();
		_Damage = a->getDamage();
		_Cast = a->getCast();
		_Duration = a->getDuration();
		_Progress = a->getProgress();
		_Applied = a->getApplied();
		_Range = a->getRange();
	}
	~PowerDebuff();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);

	SkillBase* getCopy(SkillBase* s);
};

class Tick : public SkillBase
{
public:

	Tick();
	Tick(SkillBase* a)
	{
		_Type = a->getType();
		_Name = a->getName();
		_BaseDamage = a->getBaseDamage();
		_Damage = a->getDamage();
		_Cast = a->getCast();
		_Duration = a->getDuration();
		_Progress = a->getProgress();
		_Applied = a->getApplied();
		_Range = a->getRange();
	}
	~Tick();

	void calculateDamage(Stats attributes){}
	void setPower(int p);
	void updateProgress(float time);

	SkillBase* getCopy(SkillBase* s);
};