#pragma once

#include "OgreVector3.h"
#include "OgreVector2.h"
#include "Equipment.h"

struct Stats{
	float hp;
	float maxHp;
	float mp;
	float maxMp;
	float power;
	float defense;
};

struct Physics{
	Ogre::Vector3 _Velocity;
	Ogre::Vector3 _Acceleration;
	Ogre::Vector3 _Force;

	Ogre::Vector3 _Rotation;

	Ogre::Vector3 _Position;
	Ogre::Vector3 _Facing;

	int _MovementSpeed;
	float _RotationSpeed;

	float _Mass;

	bool _Airborne;
};

struct Equip
{
	Equipment* RHand;
	Equipment* LHand;
};

struct AnimationStates
{
	std::string _Dance;
	std::string _DrawWeapons;
	std::string _IdleBase; 
	std::string _IdleTop;
	std::string _JumpEnd;
	std::string _JumpLoop;
	std::string _JumpStart;
	std::string _RunBase;
	std::string _RunTop; 
	std::string _Attack1;
	std::string _Attack2;
};

