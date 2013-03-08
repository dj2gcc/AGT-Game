#pragma once

#include "Equipment.h"
#include<string.h>

class Inventory
{
private:

	int _ID;

	std::string _Name;

	Equipment** _Contents;

	int _Width;
	int _Height;

public:

	Inventory(int x, int y, std::string name);
	~Inventory();

	bool checkSpace(Equipment* item, int x, int y);
	bool addItemAtSquare(Equipment* item, int x, int y);

	void showContent();
};