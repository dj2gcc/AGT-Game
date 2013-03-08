#pragma once

#include "OgreStringConverter.h"

#include "Terrain\OgreTerrain.h"
#include "Terrain\OgreTerrainGroup.h"

#include "OgreManager.h"

#include "PageListener.h"

class TerrainManager
{
private:

	TerrainManager();
	~TerrainManager();

	OgreManager* _OgreManager;

	Ogre::Light* _Light;

	Ogre::TerrainGlobalOptions* _TerrainGlobalOptions;
	Ogre::TerrainGroup* _TerrainGroup;

//	PageListener* _PageListener;

public:

	static TerrainManager* Instance();

	void terrainInit(Ogre::String file, OgreManager* o);

	void initialiseResources();
	void createLight();
	void setGlobalOptions();
	void setDefaultImportSettings();

	void setupPaging();


	void clearTerrainManager();

	Ogre::ManualObject* createTerrainDecal(Ogre::String& name, Ogre::String& material, Ogre::String& resourceGroup = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
	void setTerrainDecal(Ogre::ManualObject* decal, Ogre::Real x, Ogre::Real z, Ogre::Real rad);
	Ogre::Real getTerrainHeight(Ogre::Real x, Ogre::Real z);

	Ogre::TerrainGroup* getTerrainGroup() { return _TerrainGroup;}
};

