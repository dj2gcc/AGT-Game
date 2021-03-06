#pragma once
#include "Structs.h"
#include "ApplicationMethods.h"

class Character;

class CombatFunctionality
{

private:

	std::vector<SkillBase*> _SkillBook;
	std::vector<SkillBase*>::iterator _sb;
	
	std::vector<ApplicationMethodBase*> _Effects;
	std::vector<ApplicationMethodBase*>::iterator _e;

	ApplicationMethodBase* _Casting;

	float _CastProgress;

	Character* _Parent;

public:

	CombatFunctionality(Character* p);
	~CombatFunctionality();
	
	Stats _Attributes;

	ApplicationMethodBase* getCast();
	float getCastProgress();

	bool checkInRange(double r);

	void takeDamage(float power);
	void takeHealing(float power);

	void restore();

	bool receiveEffect(ApplicationMethodBase* effect);
	bool castEffect(std::string name);

	bool learnSpell(SkillBase* spell);

	void update(float tslf);


};