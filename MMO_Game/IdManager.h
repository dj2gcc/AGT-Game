#pragma once

class IdManager
{
private:

	int _ItemID;
	int _CharacterID;
	int _ObjectID;
	int _InventoryID;

	IdManager(){ _ItemID = _CharacterID = _ObjectID = _InventoryID = 0; }
	~IdManager(){}

public:

	static IdManager* Instance() { static IdManager instance;  return &instance; }

	int newItemID() { _ItemID++; return _ItemID - 1; }
	int newCharacterID() { _CharacterID++; return _CharacterID - 1; }
	int newObjectID() { _ObjectID++; return _ObjectID - 1; }
	int newInventoryID() { _InventoryID++; return _InventoryID - 1; }
};

#define IDManager IdManager::Instance()