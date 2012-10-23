
#include "State.h"

class Game;

class GameStatePlay : public State<Game>
{
private:

	GameStatePlay(){}

public:

	~GameStatePlay(){}

	static GameStatePlay* Instance();

	virtual void Enter(Game* menu);

	virtual void Execute(Game* menu);

	virtual void Exit(Game* menu);

};