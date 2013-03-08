#pragma once

#include "OgreVector3.h"
#include "OgreVector2.h"
#include "Equipment.h"

struct Orientation{

	Ogre::Vector3 position;
	Ogre::Vector3 facing;
};

struct Stats{
	float hp;
	float maxHp;
	float mp;
	float maxMp;
	float power;
	float defense;
};

struct Physics{
	Ogre::Vector3 velocity;
	Ogre::Vector3 acceleration;
	Ogre::Vector3 force;

	float mass;

	bool airborne;
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

