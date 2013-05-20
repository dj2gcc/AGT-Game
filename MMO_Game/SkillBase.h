#pragma once

#include "Structs.h"

class SkillBase
{
protected:

	std::string _Type;
	std::string _Name;

	int _BaseDamage;
	int _Damage;

	float _Cast;

	float _Duration;
	float _Progress;

	double _Applied;

	double _Range;

public:

	virtual ~SkillBase(){}

	std::string getName() { return _Name; }
	std::string getType() { return _Type; }
	float getProgress() { return _Progress; }
	int getDamage() { return _Damage; }
	float getDuration() { return _Duration; }
	float getCast() { return _Cast; }
	double getRange() { return _Range; }
	int getBaseDamage() { return _BaseDamage; }
	double getApplied() { return _Applied; }

	virtual void calculateDamage(Stats attributes) = 0;

	virtual void updateProgress(float time) = 0;

	virtual SkillBase* getCopy(SkillBase* s) = 0;

	void setProgress(float p) { _Progress = p; }
};