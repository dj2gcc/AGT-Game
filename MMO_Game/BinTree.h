#pragma once

#include"BinPart.h"

const int NUM_OF_LEVELS = 4;

class BinTree
{
private:

	static BinTree* _Instance;

	BinTree(void);

	~BinTree(void);

	void buildFullTree(int nbrLevels, 
		float cX, float cY, float cZ, 
		float sizeX, float sizeY, float sizeZ);

public:
	BinPart* root;

	static BinTree* Instance();

	void processCollisions(int &nbrTests, int &nbrCollisions);

	void addObject(Event* obj);
};

#define Tree BinTree::Instance()