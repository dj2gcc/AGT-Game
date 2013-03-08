#pragma once

#include "Telegram.h"
#include "World.h"
#include "Clock.h"
#include<set>
class Character;

struct classcomp {
  bool operator() (const Telegram& lhs, const Telegram& rhs) const
  {return lhs.dispatchTime<rhs.dispatchTime;}
};


class MessageDispatcher
{
private:

	std::set<Telegram, classcomp> _PriorityQ;

	void _Discharge(Character *receiver,Telegram& msg);

	void* getObject(int id);

	MessageDispatcher(){}

public:

	static MessageDispatcher* Instance();

	void DispatchMessage(double delay, int sender, int receiver, std::string type, void* message);

	void DispatchDelayedMessages();
};

#define Dispatch MessageDispatcher::Instance()