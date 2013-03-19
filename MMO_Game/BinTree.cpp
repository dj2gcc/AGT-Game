#include "BinTree.h"

BinTree::BinTree(void)
{
	root = NULL;
}

BinTree::~BinTree(void)
{
	delete root;
}

void BinTree::BuildFullTree(int nbrLevels, 
		float cX, float cY, float cZ, 
		float sizeX, float sizeY, float sizeZ)
{
	root = new BinPart(NULL, 0, cX, cY, cZ, sizeX, sizeY, sizeZ);
	root->makeSubPartitions(nbrLevels);
}

void BinTree::ProcessCollisions(int &nbrTests, int &nbrCollisions)
{
	nbrTests = 0;
	nbrCollisions = 0;
	root->ProcessCollisions(nbrTests, nbrCollisions);
}

void BinTree::addObject(Object3D *obj)
{
	root->addObject(obj);
}
