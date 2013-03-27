#pragma once

#include "Event.h"
#include "Controller.h"

#include <vector>
using namespace std;

class BinPart
{
private:
	BinPart* parent;
	BinPart* child[8];

	vector<Event<Controller*>*> _Events;
	vector<Character*> _Characters;

	float cX, cY, cZ;

	float lowX, highX;
	float lowY, highY;
	float lowZ, highZ;

	int level;

	BinPart(void){}

public:

	BinPart(BinPart* parent, int level, 
		float cX, float cY, float cZ, 
		float sizeX, float sizeY, float sizeZ);

	~BinPart(void);

	void makeSubPartitions(int nbrLevels);

	void addEvent(Event<Controller*>* obj);

	bool contains(Event<Controller*>* obj);

	void removeEvent(int id);

	bool collidesWith(Event<Controller*>* eve, Character* chara);

	void ProcessCollisions(int &nbrTests, int &nbrCollisions);

	void ProcessBorderCollisions(BinPart* part, int &nbrTests, int &nbrCollisions);

	bool hasChildren(){ return child[0] != NULL; }

	BinPart* getRoot();
};
