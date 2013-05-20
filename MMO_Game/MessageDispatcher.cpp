#include "MessageDispatcher.h"
#include "Controller.h"


MessageDispatcher* MessageDispatcher::Instance()
{
  static MessageDispatcher instance;

  return &instance;
}

void MessageDispatcher::_Discharge(Controller *receiver,Telegram& msg)
{
  if (!receiver->HandleMessage(msg))
  {
    //make handle message return a text error
  }
}

void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, std::string type, void* message)
{
  Controller* pSender   = _World->getController(sender);
  Controller* pReceiver = _World->getController(receiver);

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

    Controller* pReceiver = _World->getController(msg.receiver);

    _Discharge(pReceiver, msg);

    _PriorityQ.erase(_PriorityQ.begin());
  }
}



