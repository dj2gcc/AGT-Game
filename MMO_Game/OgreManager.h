#pragma once

#include "OGRE\Ogre.h"
#include "OgreRoot.h"
#include "OgreRenderSystem.h"
#include "OgreRenderWindow.h"
#include "OgreWindowEventUtilities.h"
#include "OgreConfigFile.h"
#include "OgreLogManager.h"

#include <CEGUI.h>
#include <CEGUISystem.h>
#include <CEGUISchemeManager.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <string>

class OgreManager
{
private:

	OgreManager();
	~OgreManager();

	static OgreManager* _Instance;

	Ogre::Root* _Root;
	Ogre::RenderWindow* _Window;
	Ogre::SceneManager* _Scene;
	Ogre::ResourceGroupManager* _RGM; 

	Ogre::Camera* _Camera;

	CEGUI::OgreRenderer* _GUIRenderer;
public:

	static OgreManager* Instance();

	void destroyOgreManager(){ if(_Instance) delete _Instance; }

	bool initRenderSystem();
	Ogre::RenderWindow* createWindow(bool autoCreate, Ogre::String name, unsigned int xsize = 800, unsigned int ysize = 600);
	bool sceneManagerInit(Ogre::String name);

	bool createCamera(Ogre::String name);

	bool loadResourcesFromConfig();
	
	void addResourceGroup(Ogre::String name, bool globalPool);
	void addResourceLocation(Ogre::String location, Ogre::String type, Ogre::String group, bool recursive);

	bool ceguiInit();

	void attachCamera(Ogre::SceneNode* Node);

	Ogre::RenderWindow* getWindow() { return _Window; }
	Ogre::Root* getRoot() { return _Root; }
	Ogre::SceneManager* getSceneManager() { return _Scene; }
	Ogre::ResourceGroupManager* getRgm() { return _RGM; }
	bool getCEGUIStatus() { if(_GUIRenderer) return true; else return false; }
};