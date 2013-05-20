#include "SkillList.h"
#include "Clock.h"

// Attack : public SkillBase

Attack::Attack()
{
	_Type = "Instant";
	_Name = "Attack";

	_BaseDamage = 5;
	_Damage = 5;

	_Cast = 0;

	_Duration = 0;

	_Progress = 0;

	_Applied = Time->Global();

	_Range = 100;
}

Attack::~Attack()
{
}

void Attack::calculateDamage(Stats attributes)
{
	_Damage = _BaseDamage + (attributes.power * _BaseDamage);
}

void Attack::updateProgress(float time)
{
	_Progress += time;
}

SkillBase* Attack::getCopy(SkillBase* s)
{
	return new Attack(s);
}

// Attack end

// Pain : public SkillBase

Pain::Pain()
{
	_Type = "Dot";
	_Name = "Pain";

	_BaseDamage = 30;
	_Damage = 30;

	_Cast = 2;

	_Duration = 3;

	_Progress = 0;

	_Applied = Time->Global();

	_Range = 900;
}

Pain::~Pain()
{
}

void Pain::calculateDamage(Stats attributes)
{
	_Damage = _BaseDamage + (attributes.power * _BaseDamage);
}

void Pain::updateProgress(float time)
{
	_Progress += time;
}

SkillBase* Pain::getCopy(SkillBase* s)
{
	return new Pain(s);
}

// Pain end

// Heal : public SkillBase

Heal::Heal()
{
	_Type = "Hot";
	_Name = "Heal";

	_BaseDamage = 50;
	_Damage = 50;

	_Cast = 2;

	_Duration = 3;

	_Progress = 0;

	_Applied = Time->Global();

	_Range = 500;
}

Heal::~Heal()
{
}

void Heal::calculateDamage(Stats attributes)
{
	_Damage = _BaseDamage + (attributes.power * _BaseDamage);
}

void Heal::updateProgress(float time)
{
	_Progress += time;
}

SkillBase* Heal::getCopy(SkillBase* s)
{
	return new Heal(s);
}

// Heal end

// StaminaBuff : public SkillBase

StaminaBuff::StaminaBuff()
{
	_Type = "Buff";
	_Name = "Stambuff";

	_BaseDamage = 50;
	_Damage = 50;

	_Cast = 2000;

	_Duration = 3000;

	_Progress = 0;

	_Applied = Time->Global();

	_Range = 100;
}

StaminaBuff::~StaminaBuff()
{
}

void StaminaBuff::calculateDamage(Stats attributes)
{
	_Damage = _BaseDamage + (attributes.power * _BaseDamage);
}

void StaminaBuff::updateProgress(float time)
{
	_Progress += time;
}

SkillBase* StaminaBuff::getCopy(SkillBase* s)
{
	return new StaminaBuff(s);
}

// StaminaBuff end

// PowerDebuff : public SkillBase

PowerDebuff::PowerDebuff()
{
	_Type = "Debuff";
	_Name = "Powdebuff";

	_BaseDamage = 10;
	_Damage = 10;

	_Cast = 2000;

	_Duration = 3000;

	_Progress = 0;

	_Applied = Time->Global();

	_Range = 100;
}

PowerDebuff::~PowerDebuff()
{
}

void PowerDebuff::calculateDamage(Stats attributes)
{
	_Damage = _BaseDamage + (attributes.power * _BaseDamage);
}

void PowerDebuff::updateProgress(float time)
{
	_Progress += time;
}

SkillBase* PowerDebuff::getCopy(SkillBase* s)
{
	return new PowerDebuff(s);
}

// PowerDebuff end

// Tick : public SkillBase

Tick::Tick()
{
	_Type = "Tick";
	_Name = "Tick";

	_BaseDamage = 0;
	_Damage = 0;

	_Cast = 0;

	_Duration = 0;

	_Progress = 0;

	_Applied = Time->Global();

	_Range = 9999999999;
}

Tick::~Tick()
{
}

void Tick::setPower(int p)
{
	_Damage = p;
}

void Tick::updateProgress(float time)
{
	_Progress += time;
}

SkillBase* Tick::getCopy(SkillBase* s)
{
	return new Tick(s);
}

//Tick end