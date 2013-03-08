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
}

Attack::Attack(Attack& a)
{
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

// Attack end

// Pain : public SkillBase

Pain::Pain()
{
	_Type = "Dot";
	_Name = "Pain";

	_BaseDamage = 50;
	_Damage = 50;

	_Cast = 2;

	_Duration = 3;

	_Progress = 0;

	_Applied = Time->Global();
}

Pain::Pain(Pain& a)
{
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
}

Heal::Heal(Heal& a)
{
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
}

StaminaBuff::StaminaBuff(StaminaBuff& a)
{
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
}

PowerDebuff::PowerDebuff(PowerDebuff& a)
{
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
}

Tick::Tick(Tick& a)
{
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

//Tick end