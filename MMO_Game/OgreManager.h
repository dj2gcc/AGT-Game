#pragma once

#include "OGRE\Ogre.h"
#include "OgreRoot.h"
#include "OgreRenderSystem.h"
#include "OgreRenderWindow.h"
#include "OgreWindowEventUtilities.h"
#include "OgreConfigFile.h"

#include "Terrain\OgreTerrain.h"
#include "Terrain\OgreTerrainGroup.h"


#include <CEGUI.h>
#include <CEGUISystem.h>
#include <CEGUISchemeManager.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <string>

class OgreManager
{
private:
	Ogre::Root* lRoot;
	Ogre::RenderWindow* lWindow;
	Ogre::SceneManager* lScene;
	Ogre::ResourceGroupManager* rgm; 

	Ogre::Camera* lCamera;

	CEGUI::OgreRenderer* GUIRenderer;
public:
	OgreManager();
	~OgreManager();

	bool ogreInit();
	void ceguiInit();
	void sceneManagerInit(Ogre::String name);

	bool initRenderSystem();
	Ogre::RenderWindow* createWindow(bool autoCreate, Ogre::String name);
	bool createCamera(Ogre::String name);

	void loadResourcesFromConfig();
	void addResourceGroup(Ogre::String name, bool globalPool);
	void addResourceLocation(Ogre::String location, Ogre::String type, Ogre::String group, bool recursive);

	void attachCamera(Ogre::SceneNode* Node);

	Ogre::RenderWindow* getWindow() { return lWindow; }
	Ogre::Root* getRoot() { return lRoot; }
	Ogre::SceneManager* getSceneManager() { return lScene; }
	Ogre::ResourceGroupManager* getRgm() { return rgm; }
};