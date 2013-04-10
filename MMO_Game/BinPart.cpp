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

bool BinPart::contains(Event* obj)
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

void BinPart::addEvent(Event* obj)
{
	if(!hasChildren())
	{
		obj->_Part = this;
		_Events.push_back(obj);
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
		_Events.push_back(obj);
	}
}

void BinPart::removeEvent(int id)
{
	vector<Event*>::iterator it;
	for(it = _Events.begin(); it != _Events.end(); ++it)
	{
		if((*it)->getID() == id)
		{
			_Events.erase(it);
			break;
		}
	}
}

bool BinPart::collidesWith(Event* eve, Character* chara)
{
	// Square of distance between cube centres
	float d2 = eve->getPosition().distance(chara->getPosition());
	// Square of the sum of the collision radii
	float sr2 = (eve->getRadius() + chara->getCollisionRadius()) * (eve->getRadius() + chara->getCollisionRadius());
	// Swap velocities
	if(d2 < sr2)
	{
		return true;
	}
	return false;
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

	int c = _Characters.size();
	int e = _Events.size();
	if(e > 0 && c > 0)
	{
		for(int i = 0; i < e-1; i++)
		{
			for(int j = i+1; j < c; j++)
			{
				nbrTests++;
				if(collidesWith(_Events[i], _Characters[j]))
				{
					_Events[i]->executeEvent(_Characters[j]);
					nbrCollisions++;
				}
			}
		}
	}
	if(e >= 1 && parent != NULL)
	{
		parent->ProcessBorderCollisions(this, nbrTests, nbrCollisions);
	}
}

void BinPart::ProcessBorderCollisions(BinPart* part, int &nbrTests, int &nbrCollisions)
{
	int nPart = part->_Events.size();
	int c = _Characters.size();

	if(c > 0)
	{
		for(int i = 0; i < nPart; i++)
		{
			for(int j = 0; j < c; j++)
			{
				nbrTests++;
				if(collidesWith(part->_Events[i], _Characters[j]))
				{
					_Events[i]->executeEvent(_Characters[j]);
					nbrCollisions++;
				}
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
