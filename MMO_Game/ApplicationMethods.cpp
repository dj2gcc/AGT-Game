#include "ApplicationMethods.h"
#include "MessageDispatcher.h"
#include "Character.h"

// Dot

Dot::Dot(SkillBase* s, int sender) : ApplicationMethodBase(s, sender)
{
}

void Dot::update(Character* c, float tslf)
{
	c->getCombat()->takeDamage((((tslf * 100) / _Skill->getDuration()) / 100) * _Skill->getDamage());
	_Skill->updateProgress(tslf);
}

// Dot end

// Hot

Hot::Hot(SkillBase* s, int sender) : ApplicationMethodBase(s, sender)
{
}

void Hot::update(Character* c, float tslf)
{
	c->getCombat()->takeHealing((((tslf * 100) / _Skill->getDuration()) / 100) * _Skill->getDamage());
	_Skill->updateProgress(tslf);
}

// Hot end

// Debuff

Debuff::Debuff(SkillBase* s, int sender) : ApplicationMethodBase(s, sender)
{
}

void Debuff::update(Character* c, float tslf)
{
}

// Debuff end

// Buff

Buff::Buff(SkillBase* s, int sender) : ApplicationMethodBase(s, sender)
{
}

void Buff::update(Character* c, float tslf)
{
}

// Buff end

// Instant

Instant::Instant(SkillBase* s, int sender) : ApplicationMethodBase(s, sender)
{
}

void Instant::update(Character* c, float tslf)
{
	c->getCombat()->takeDamage(_Skill->getDamage());
	_Skill->updateProgress(tslf);
}

// Instant end

// Channeling

Channeling::Channeling(SkillBase* s, int sender) : ApplicationMethodBase(s, sender)
{
}

void Channeling::update(Character* c, float tslf)
{
	Tick* t = new Tick();
	t->setPower(((tslf * 100) / _Skill->getDuration()) * _Skill->getDamage());

	Dispatch->DispatchMessage(0, c->getID(), c->_Target->getID(), "Combat", new Instant(t, this->getSenderID()));
}

// Channeling end