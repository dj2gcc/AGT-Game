#pragma once

#include "ApplicationMethodBase.h"

class Dot : public ApplicationMethodBase //Damage Over Time
{
public:

	Dot(SkillBase* s, int sender);
	~Dot()
	{
		delete _Skill;
	}

	void update(Character* c, float tslf);
};

class Hot : public ApplicationMethodBase  // Heal Over Time
{
public:

	Hot(SkillBase* s, int sender);
	~Hot()
	{
		delete _Skill;
	}

	void update(Character* c, float tslf);
};

class Debuff : public ApplicationMethodBase
{
public:

	Debuff(SkillBase* s, int sender);
	~Debuff()
	{
		delete _Skill;
	}

	void update(Character* c, float tslf);
};

class Buff : public ApplicationMethodBase
{
public:

	Buff(SkillBase* s, int sender);
	~Buff()
	{
		delete _Skill;
	}

	void update(Character* c, float tslf);
};

class Instant : public ApplicationMethodBase
{
public:

	Instant(SkillBase* s, int sender);
	~Instant()
	{
		delete _Skill;
	}

	void update(Character* c, float tslf);
};

class Channeling : public ApplicationMethodBase
{
public:

	Channeling(SkillBase* s, int sender);
	~Channeling()
	{
		delete _Skill;
	}

	void update(Character* c, float tslf);
};