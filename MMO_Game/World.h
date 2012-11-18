#include "PhysicsObject.h"
#include<vector>

class World
{
private:

	std::vector<Object*> _WorldObjects;
	std::vector<Object*>::iterator _woi;

	PhysicsObject* _Player;

	MoveableObject* _InControl;

public:

	World();
	~World();

	void populate();

	void update(Ogre::Real tslf);

	MoveableObject* getPlayer() { return _Player; }
	MoveableObject* getInControl() { return _InControl; }
};