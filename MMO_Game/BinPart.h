#pragma once

#include <vector>
using namespace std;

class BinPart
{
private:
	BinPart* parent;
	BinPart* child[8];

	vector<Object3D*> objects;

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

	void addObject(Object3D* obj);

	bool contains(Object3D* obj);

	void removeObject(int id);

	void ProcessCollisions(int &nbrTests, int &nbrCollisions);

	void ProcessBorderCollisions(BinPart* part, int &nbrTests, int &nbrCollisions);

	bool hasChildren(){ return child[0] != NULL; }

	BinPart* getRoot();
};
