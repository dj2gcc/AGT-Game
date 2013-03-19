#pragma once

#include"BinPart.h"

class BinTree
{
public:
	BinPart* root;

	BinTree(void);

	~BinTree(void);

	void buildFullTree(int nbrLevels, 
		float cX, float cY, float cZ, 
		float sizeX, float sizeY, float sizeZ);

	void processCollisions(int &nbrTests, int &nbrCollisions);

	void addObject(Object3D* obj);
};
