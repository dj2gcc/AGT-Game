#include "Character.h"
#include "TerrainManager.h"


Character::Character(Ogre::String mesh, std::string name, Ogre::Vector3 p) : DynamicObject(mesh, p)
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

	_StartPosition = p;
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

			if(msg.sender == _Target->getID())
			{
				_Target = NULL;
			}
		}
	return true;
}

void Character::update(Ogre::Real tslf)
{
	
	if(!_States->Update(tslf))
		return;

	Ogre::Radian rotation = Ogre::Radian(_Motion._Rotation.y * 0.8 * tslf);
	Ogre::Vector3 translate = Ogre::Vector3(_Motion._Velocity.x * _Motion._MovementSpeed * tslf , _Motion._Velocity.y * _Motion._MovementSpeed * tslf, _Motion._Velocity.z * _Motion._MovementSpeed * tslf);

	_BodyNode->yaw(rotation);

	Ogre::Vector3 temp = _BodyNode->getPosition();

	_BodyNode->translate(_Motion._Velocity.x * _Motion._MovementSpeed * tslf , _Motion._Velocity.y * _Motion._MovementSpeed * tslf, _Motion._Velocity.z * _Motion._MovementSpeed * tslf, Ogre::Node::TS_LOCAL);
	
	if(_BodyNode->getPosition().x > 5999 || _BodyNode->getPosition().x < -5999 || _BodyNode->getPosition().z > 5999 || _BodyNode->getPosition().z < -5999)
	{
		_BodyNode->setPosition(temp);
	}

	updateAnimation(tslf);

	float difference = _BodyNode->getPosition().y;

	if(_Motion._Airborne)
	{
		_Motion._Velocity.y = _Motion._Velocity.y + (_Motion._Acceleration.y * (tslf * 20));
		float s = (_Motion._Velocity.y * (tslf * 20)) + (0.5 * ((_Motion._Acceleration.y * (tslf * 20)) * (_Motion._Acceleration.y * (tslf * 20))));
		_BodyNode->setPosition(_BodyNode->getPosition().x, _BodyNode->getPosition().y + s, _BodyNode->getPosition().z);
		if(_BodyNode->getPosition().y - _Height <= TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z))
		{
			_Motion._Velocity.y = 0;
			_Motion._Airborne = false;

			setAdditionalAnimation(JumpEnd, Overriding);
		}
	}else
	{
		_BodyNode->setPosition(_BodyNode->getPosition().x, TerrainManager::Instance()->getTerrainHeight(_BodyNode->getPosition().x, _BodyNode->getPosition().z) + _Height, _BodyNode->getPosition().z);
		difference = _BodyNode->getPosition().y - difference;

		if(difference > 10)
		{
			_BodyNode->setPosition(temp);
		}
	}

	_Motion._Position = _BodyNode->getPosition();

	_Combat->update(tslf);
}