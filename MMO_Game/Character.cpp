#include "Character.h"
#include "TerrainManager.h"


Character::Character(Ogre::String mesh, std::string name) : DynamicObject(mesh)
{
	_Name = name;
	_Combat = new CombatFunctionality(this);
	_Inventory = new Inventory(6, 6, "BackPack");

	_States = new StateMachine<Character>(this);
	_States->SetCurrentState(Alive::Instance());

	_Target = NULL;

	_Exp = 0;
	_ExpToLvl = 100;
	_Level = 1;
}

Character::~Character()
{
}

bool Character::Equip(Equipment* e)
{
	if(e->getType() == "RHand")
	{
		_Equip.RHand = e;
		_Body->attachObjectToBone("Handle.R", e->getBody());		
	}else
		if(e->getType() == "LHand")
		{
			_Equip.LHand = e;
			_Body->attachObjectToBone("Handle.L", e->getBody());
		}else
		{
			return false;
		}

	return true;
}

bool Character::HandleMessage(Telegram& msg)
{
	if(_States->CurrentState()->OnMessage(this, msg) == false)
	{
		return false;
	}

	if(msg.type == "Combat")
	{
		_Combat->receiveEffect((ApplicationMethodBase*)msg.message);
	}else
		if(msg.type == "CombatEnd")
		{
			_Exp += 10;

			if(_Exp >= _ExpToLvl)
			{
				_Exp = 0;
				_Level++;
			}
		}
	return true;
}

void Character::update(Ogre::Real tslf)
{
	if(_MoveUp == true && _MoveDown == false)
	{
		_BodyNode->translate(0,0, 800 * tslf, Ogre::Node::TS_LOCAL);
	}

	if(_MoveDown == true && _MoveUp == false)
	{
		_BodyNode->translate(0,0, -800 * tslf, Ogre::Node::TS_LOCAL);
	}

	if(_RotateLeft == true && _RotateRight == false)
	{
		_BodyNode->yaw(Ogre::Radian(0.8 * tslf));
	}
	
	if(_RotateRight == true && _RotateLeft == false)
	{
		_BodyNode->yaw(Ogre::Radian(-0.8 * tslf));
	}

	if(_MoveLeftSide == true && _MoveRightSide == false)
	{
		_BodyNode->translate(800 * tslf , 0, 0, Ogre::Node::TS_LOCAL);
	}

	if(_MoveRightSide == true && _MoveLeftSide == false)
	{
		_BodyNode->translate(-800 * tslf , 0, 0, Ogre::Node::TS_LOCAL);
	}

	updateAnimation(tslf);

	if(_Motion.airborne)
	{
		_Motion.velocity.y = _Motion.velocity.y + (_Motion.acceleration.y * (tslf * 20));
		float s = (_Motion.velocity.y * (tslf * 20)) + (0.5 * ((_Motion.acceleration.y * (tslf * 20)) * (_Motion.acceleration.y * (tslf * 20))));
		_BodyNode->setPosition(_BodyNode->getPosition().x, _BodyNode->getPosition().y + s, _BodyNode->getPosition().z);
		if(_BodyNode->getPosition().y - _Height <= TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z))
		{
			_Motion.velocity.y = 0;
			_Motion.airborne = false;

			setAdditionalAnimation(JumpEnd, Overriding);
		}
	}else
	{
		_BodyNode->setPosition(_BodyNode->getPosition().x, TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z) + _Height, _BodyNode->getPosition().z);
	}

	_Combat->update(tslf);
	_States->Update(tslf);
}