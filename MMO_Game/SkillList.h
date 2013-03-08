#pragma once

#include "SkillBase.h"


class Attack : public SkillBase
{
public:

	Attack();
	Attack(Attack& a);
	~Attack();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);
};

class Pain : public SkillBase
{
public:

	Pain();
	Pain(Pain& a);
	~Pain();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);
};

class Heal : public SkillBase
{
public:

	Heal();
	Heal(Heal& a);
	~Heal();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);
};

class StaminaBuff : public SkillBase
{
public:

	StaminaBuff();
	StaminaBuff(StaminaBuff& a);
	~StaminaBuff();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);
};

class PowerDebuff : public SkillBase
{
public:

	PowerDebuff();
	PowerDebuff(PowerDebuff& a);
	~PowerDebuff();

	void calculateDamage(Stats attributes);
	void updateProgress(float time);
};

class Tick : public SkillBase
{
public:

	Tick();
	Tick(Tick& a);
	~Tick();

	void calculateDamage(Stats attributes){}
	void setPower(int p);
	void updateProgress(float time);
};