#include "MessageDispatcher.h"
#include "Character.h"


MessageDispatcher* MessageDispatcher::Instance()
{
  static MessageDispatcher instance;

  return &instance;
}

void MessageDispatcher::_Discharge(Character *receiver,Telegram& msg)
{
  if (!receiver->HandleMessage(msg))
  {
    //make handle message return a text error
  }
}

void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, std::string type, void* message)
{
  Character* pSender   = _World->getCharacter(sender);
  Character* pReceiver = _World->getCharacter(receiver);

  if (pReceiver == NULL)
  {
    //no receiver warning
    return;
  }
  
  Telegram msg(sender, receiver, type, delay, message);
                        
  if(delay <= 0.0f)                                                        
  {
    _Discharge(pReceiver, msg);
  }else
  {
    double CurrentTime = Time->Global();

    msg.dispatchTime = CurrentTime + delay;

    _PriorityQ.insert(msg);               
  }
}

void MessageDispatcher::DispatchDelayedMessages()
{  
  double CurrentTime = Time->Global();

  while(!_PriorityQ.empty() && (_PriorityQ.begin()->dispatchTime < CurrentTime) && (_PriorityQ.begin()->dispatchTime > 0))
  {
    Telegram msg = *_PriorityQ.begin();

    Character* pReceiver = _World->getCharacter(msg.receiver);

    _Discharge(pReceiver, msg);

    _PriorityQ.erase(_PriorityQ.begin());
  }
}



