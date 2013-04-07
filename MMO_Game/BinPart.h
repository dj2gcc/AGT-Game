#pragma once
#include "Event.h"
#include "AIController.h"

#include <vector>
using namespace std;

class BinPart
{
private:
	BinPart* parent;
	BinPart* child[8];

	vector<Event<AIController*>*> _Events;
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

	void addEvent(Event<AIController*>* obj);

	bool contains(Event<AIController*>* obj);

	void removeEvent(int id);

	bool collidesWith(Event<AIController*>* eve, Character* chara);

	void ProcessCollisions(int &nbrTests, int &nbrCollisions);

	void ProcessBorderCollisions(BinPart* part, int &nbrTests, int &nbrCollisions);

	bool hasChildren(){ return child[0] != NULL; }

	BinPart* getRoot();
};
