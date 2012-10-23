
#include "State.h"
#include "MainMenu.h"

class GameStateMenu : public State<MainMenu>
{
private:

	GameStateMenu(){}

	GameStateMenu(const GameStateMenu&);
	GameStateMenu& operator=(const GameStateMenu&);

public:

	~GameStateMenu(){}

	static GameStateMenu* Instance();

	virtual void Enter(MainMenu* menu);

	virtual void Execute(MainMenu* menu);

	virtual void Exit(MainMenu* menu);

};