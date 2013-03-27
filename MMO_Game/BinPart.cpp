#include "BinPart.h"

#include "BinTree.h"


BinPart::BinPart(BinPart *parent, int level, 
	float cX, float cY, float cZ, 
	float sizeX, float sizeY, float sizeZ)
{
	this->parent = parent;
	this->level = level;
	this->cX = cX;
	this->cY = cY;
	this->cZ = cZ;

	lowX = cX - sizeX/2;
	highX = cX + sizeX/2;
	lowY = cY - sizeY/2;
	highY = cY + sizeY/2;
	lowZ = cZ - sizeZ/2;
	highZ = cZ + sizeZ/2;

	child[0] = NULL;
	child[1] = NULL;
	child[2] = NULL;
	child[3] = NULL;
	child[4] = NULL;
	child[5] = NULL;
	child[6] = NULL;
	child[7] = NULL;
}

BinPart::~BinPart(void)
{
	if(hasChildren())
	{
		delete child[0];
		delete child[1];
		delete child[2];
		delete child[3];
		delete child[4];
		delete child[5];
		delete child[6];
		delete child[7];
	}
	_Events.clear();
}

BinPart* BinPart::getRoot()
{
	if(parent == NULL)
		return this;
	else
		return parent->getRoot();
}

bool BinPart::contains(Event<Controller*>* obj)
{
	float nLowX = obj->getPosition().x - obj->getRadius();
	float nHighX = obj->getPosition().x + obj->getRadius();
	float nLowY = obj->getPosition().y - obj->getRadius();
	float nHighY = obj->getPosition().y + obj->getRadius();
	float nLowZ = obj->getPosition().z - obj->getRadius();
	float nHighZ = obj->getPosition().z + obj->getRadius();

	bool result = (nLowX > lowX && nHighX < highX && 
				nLowY > lowY && nHighY < highY &&
				nLowZ > lowZ && nHighZ < highZ);
	return result;
}

void BinPart::addEvent(Event<Controller*> *obj)
{
	if(!hasChildren())
	{
		obj->_Part = this;
		objects.push_back(obj);
		return;
	}
	int p = 0;

	if(obj->getPosition().x < cX && obj->getPosition().y < cY)
	{
		p += (obj->getPosition().z < cZ) ? 0 : 4;
	}else
		if(obj->getPosition().x > cX && obj->getPosition().y < cY)
		{
			p += (obj->getPosition().z < cZ) ? 2 : 6;
		}else
			if(obj->getPosition().x < cX && obj->getPosition().y > cY)
			{
				p += (obj->getPosition().z < cZ) ? 1 : 5;
			}else
				if(obj->getPosition().x > cX && obj->getPosition().y > cY)
				{
					p += (obj->getPosition().z < cZ) ? 3 : 7;
				}


	if(child[p]->contains(obj))
	{
		child[p]->addEvent(obj);
	}else
	{
		obj->_Part = this;
		objects.push_back(obj);
	}
}

void BinPart::removeEvent(int id)
{
	vector<Event<Controller*>*>::iterator it;
	for(it = objects.begin(); it != objects.end(); ++it)
	{
		if((*it)->getID() == id)
		{
			objects.erase(it);
			break;
		}
	}
}

bool BinPart::collidesWith(Event<Controller*>* eve, Character* chara)
{
}

void BinPart::ProcessCollisions(int &nbrTests, int &nbrCollisions)
{
	if(hasChildren())
	{
		child[0]->ProcessCollisions(nbrTests, nbrCollisions);
		child[1]->ProcessCollisions(nbrTests, nbrCollisions);
		child[2]->ProcessCollisions(nbrTests, nbrCollisions);
		child[3]->ProcessCollisions(nbrTests, nbrCollisions);
		child[4]->ProcessCollisions(nbrTests, nbrCollisions);
		child[5]->ProcessCollisions(nbrTests, nbrCollisions);
		child[6]->ProcessCollisions(nbrTests, nbrCollisions);
		child[7]->ProcessCollisions(nbrTests, nbrCollisions);
	}

	int n = _Events.size();
	if(n >= 2)
	{
		for(int i = 0; i < n-1; i++)
		{
			for(int j = i+1; j < n; j++)
			{
				nbrTests++;
				if(objects[i]->collidesWith(objects[j]))
					nbrCollisions++;
			}
		}
	}
	if(n >= 1 && parent != NULL)
	{
		parent->ProcessBorderCollisions(this, nbrTests, nbrCollisions);
	}
}

void BinPart::ProcessBorderCollisions(BinPart* part, int &nbrTests, int &nbrCollisions)
{
	int nPart = part->_Events.size();
	int n = _Events.size();

	if(n > 0)
	{
		for(int i = 0; i < nPart; i++)
		{
			for(int j = 0; j < n; j++)
			{
				nbrTests++;
				if(part->_Events[i]->collidesWith(objects[j]))
					nbrCollisions++;
			}
		}
	}
	if(parent != NULL)
	{
		parent->ProcessBorderCollisions(part, nbrTests, nbrCollisions);
	}
}


void BinPart::makeSubPartitions(int nbrLevels)
{
		if(level < nbrLevels -1)
	{
		float newSizeX = (highX - lowX) /2;
		float newSizeY = (highY - lowY) /2;
		float newSizeZ = (highZ - lowZ) /2;

		child[0] = new BinPart(this, level + 1, cX - newSizeX/2, cY - newSizeY/2, cZ - newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[1] = new BinPart(this, level + 1, cX - newSizeX/2, cY + newSizeY/2, cZ - newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[2] = new BinPart(this, level + 1, cX + newSizeX/2, cY - newSizeY/2, cZ - newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[3] = new BinPart(this, level + 1, cX + newSizeX/2, cY + newSizeY/2, cZ - newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[4] = new BinPart(this, level + 1, cX - newSizeX/2, cY - newSizeY/2, cZ + newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[5] = new BinPart(this, level + 1, cX - newSizeX/2, cY + newSizeY/2, cZ + newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[6] = new BinPart(this, level + 1, cX + newSizeX/2, cY - newSizeY/2, cZ + newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[7] = new BinPart(this, level + 1, cX + newSizeX/2, cY + newSizeY/2, cZ + newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[0]->makeSubPartitions(nbrLevels);
		child[1]->makeSubPartitions(nbrLevels);
		child[2]->makeSubPartitions(nbrLevels);
		child[3]->makeSubPartitions(nbrLevels);
		child[4]->makeSubPartitions(nbrLevels);
		child[5]->makeSubPartitions(nbrLevels);
		child[6]->makeSubPartitions(nbrLevels);
		child[7]->makeSubPartitions(nbrLevels);
	}
}
