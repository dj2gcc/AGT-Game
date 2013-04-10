#include "BinTree.h"

BinTree::BinTree(void)
{
	root = NULL;
	buildFullTree(NUM_OF_LEVELS, 0, 0, 0,0, 0, 0);
}

BinTree::~BinTree(void)
{
	delete root;
}

BinTree* BinTree::Instance()
{
	if(!_Instance)
	{
		_Instance = new BinTree();
	}

	return _Instance;
}

void BinTree::buildFullTree(int nbrLevels, 
		float cX, float cY, float cZ, 
		float sizeX, float sizeY, float sizeZ)
{
	root = new BinPart(NULL, 0, cX, cY, cZ, sizeX, sizeY, sizeZ);
	root->makeSubPartitions(nbrLevels);
}

void BinTree::processCollisions(int &nbrTests, int &nbrCollisions)
{
	nbrTests = 0;
	nbrCollisions = 0;
	root->ProcessCollisions(nbrTests, nbrCollisions);
}

void BinTree::addObject(Event *obj)
{
	root->addEvent(obj);
}
