#include "CombatFunctionality.h"
#include "MessageDispatcher.h"
#include "Character.h"
#include "ApplicationMethods.h"

CombatFunctionality::CombatFunctionality(Character* p)
{
	_Parent = p;
	_Casting = NULL;
	_CastProgress = 0;

	_Attributes.defense = 0.2f;
	_Attributes.hp = 100.0f;
	_Attributes.maxHp = 100.0f;
	_Attributes.maxMp = 100.0f;
	_Attributes.mp = 100.0f;
	_Attributes.power = 0.5f;
}

CombatFunctionality::~CombatFunctionality()
{
	_Casting = NULL;
}

ApplicationMethodBase* CombatFunctionality::getCast()
{
	return _Casting;
}

float CombatFunctionality::getCastProgress()
{
	if(_Casting)
	{
		return _CastProgress;
	}else
	{
		return -1.0f;
	}
}

void CombatFunctionality::takeDamage(float damage)
{
	if((damage - _Attributes.defense) < 0)
	{
	}else
	{
		_Attributes.hp -= damage - (_Attributes.defense * damage);
	}

	if(_Attributes.hp < 0)
	{
		_Attributes.hp = 0;
	}
}

void CombatFunctionality::takeHealing(float healing)
{
	_Attributes.hp += healing;

	if(_Attributes.hp > _Attributes.maxHp)
		_Attributes.hp = _Attributes.maxMp;
}

bool CombatFunctionality::receiveEffect(ApplicationMethodBase* effect)
{
	_Effects.push_back(effect);
	return true;
}

bool CombatFunctionality::castEffect(std::string name)
{
	if(!_Casting && _Parent->_Target != NULL)
	{
		for(_sb = _SkillBook.begin(); _sb != _SkillBook.end(); _sb++)
		{
			if((*_sb)->getName() == name)
			{
				(*_sb)->calculateDamage(_Attributes);
				(*_sb)->setProgress(0.0f);
				if((*_sb)->getType() == "Dot")
				{
					_Casting = new Dot((*_sb), _Parent->getID());
				}else
					if((*_sb)->getType() == "Hot")
					{
						_Casting = new Hot((*_sb), _Parent->getID());
					}else
						if((*_sb)->getType() == "Buff")
						{
							_Casting = new Buff((*_sb), _Parent->getID());
						}else
							if((*_sb)->getType() == "Debuff")
							{
								_Casting = new Debuff((*_sb), _Parent->getID());
							}else
								if((*_sb)->getType() == "Channeling")
								{
									_Casting = new Channeling((*_sb), _Parent->getID());
								}else
									if((*_sb)->getType() == "Instant")
									{
										_Casting = new Instant((*_sb), _Parent->getID());
									}
				return true;
			}
		}
	}

	return false;
}

bool CombatFunctionality::learnSpell(SkillBase* spell)
{
	for(_sb = _SkillBook.begin(); _sb != _SkillBook.end(); _sb++)
	{
		if((*_sb)->getName() == spell->getName())
		{
			return false;
		}
	}

	_SkillBook.push_back(spell);
	return true;
}

void CombatFunctionality::update(float tslf)
{
	if(_Casting)
	{
		if(_Parent->_Target)
		{
			_CastProgress += tslf;

			if(_CastProgress >= _Casting->getSkill()->getCast())
			{
				_Parent->setAdditionalAnimation(Attack2, Overlaping);
				Dispatch->DispatchMessageA(0, _Parent->getID(), _Parent->_Target->getID(), "Combat", _Casting);
				_Casting = NULL;
				_CastProgress = 0;
			}
		}else
		{
			_Casting = NULL;
			_CastProgress = 0;
		}
	}

	for(_e = _Effects.begin(); _e != _Effects.end(); )
	{
		(*_e)->update(_Parent, tslf);

		if(_Attributes.hp == 0)
		{
			Dispatch->DispatchMessageA(0, _Parent->getID(), (*_e)->getSenderID(), "CombatEnd", _Parent);
			break;
		}

		if((*_e)->getSkill()->getProgress() >= (*_e)->getSkill()->getDuration())
		{
			delete *_e;  
			_e = _Effects.erase(_e);

		}else
		{
			_e++;
		}
	}

	if(_Attributes.hp == 0)
	{
		_Effects.clear();
		_Parent->getStateMachine()->ChangeState(Dead::Instance());
	}
}
