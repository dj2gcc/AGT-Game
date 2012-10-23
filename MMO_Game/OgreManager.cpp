#include "OgreManager.h"

OgreManager::OgreManager()
{
	lWindow = NULL;
	lCamera = NULL;
	//rgm = &Ogre::ResourceGroupManager::getSingleton();
}

OgreManager::~OgreManager()
{
	Ogre::LogManager::getSingleton().logMessage("End of Ogre");

	lRoot->destroySceneManager(lScene);
	lRoot->detachRenderTarget("Ogre Game");
	lWindow->destroy();
	delete lWindow;

	delete lCamera;
}

bool OgreManager::initRenderSystem()
{
	Ogre::String lConfigFileName = "";
	Ogre::String lPluginsFileName = "";
	Ogre::String lLogFileName = "OgreLog.LOG";

	lRoot = new Ogre::Root(lConfigFileName, lPluginsFileName, lLogFileName);

	typedef std::vector <Ogre::String> Strings;

	Strings lPluginNames;

	lPluginNames.push_back("RenderSystem_GL");
	lPluginNames.push_back("Plugin_ParticleFX");
	lPluginNames.push_back("Plugin_CgProgramManager");
	lPluginNames.push_back("Plugin_OctreeSceneManager");

	Strings::iterator lIter = lPluginNames.begin();
	Strings::iterator lIterEnd = lPluginNames.end();

	for(;lIter != lIterEnd; lIter++)
	{
		Ogre::String& lPluginName = (*lIter);
		
		bool lIsInDebugMode = OGRE_DEBUG_MODE;
		if(lIsInDebugMode)
		{
			lPluginName.append("_d");
		}
		lRoot->loadPlugin(lPluginName);
	}

	const Ogre::RenderSystemList& lRenderSystemList = lRoot->getAvailableRenderers();
	if(lRenderSystemList.size() == 0)
	{
		Ogre::LogManager::getSingleton().logMessage("Sorry, no rendersystem was found.");
		return false;
	}

	lRoot->setRenderSystem(lRenderSystemList[0]);

	return true;
}

Ogre::RenderWindow* OgreManager::createWindow(bool autoCreate, Ogre::String name)
{
	bool lCreateAWindowAutomatically = autoCreate;
	Ogre::String lWindowTitle = name;
	Ogre::String lCustomCapacities = "";

	if(!(lCreateAWindowAutomatically))
	{
		unsigned int lSizeX = 800;
		unsigned int lSizeY = 600;
		
		bool lFullscreen = false;
		
		Ogre::NameValuePairList lParams;
		lParams["vsync"] = "true";

		lRoot->initialise(autoCreate);

		lWindow = lRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
		
	}else
	{
		lWindow = lRoot->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);
	}

	return lWindow;
}

bool OgreManager::ogreInit()
{
	
	initRenderSystem();

	//lWindow = createWindow(false, Ogre::String("MainWindow"));

	return true;

}

void OgreManager::sceneManagerInit(Ogre::String name)
{

	lScene = lRoot->createSceneManager("TerrainSceneManager", name);
}

bool OgreManager::createCamera(Ogre::String name)
{
	lCamera = lScene->createCamera(name);

	unsigned short lMainViewportZOrder = 100;
	Ogre::Viewport* vp = lWindow->addViewport(lCamera, lMainViewportZOrder, 0, 0, 1, 1);
	vp->setAutoUpdated(true);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,1));

	float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
	lCamera->setAspectRatio(ratio);

	lWindow->setActive(true);
	lWindow->setAutoUpdated(false);

	return true;
}

void OgreManager::loadResourcesFromConfig()
{
	//std::string mResourcesCfg;

	//#ifdef _DEBUG
 //   mResourcesCfg = "resources_d.cfg";
	//#else
 //   mResourcesCfg = "resources.cfg";
	//#endif

	rgm = &Ogre::ResourceGroupManager::getSingleton();

	Ogre::ConfigFile cf;
	cf.load("resources_d.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;

	while(seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for(i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
}

void OgreManager::addResourceGroup(Ogre::String name, bool globalPool)
{
	rgm->createResourceGroup(name, globalPool);
}

void OgreManager::addResourceLocation(Ogre::String location, Ogre::String type, Ogre::String group, bool recursive)
{
	rgm->addResourceLocation(location, type, group, recursive);

	//rgm->initialiseResourceGroup(group);
	//rgm->initialiseAllResourceGroups();
}

void OgreManager::attachCamera(Ogre::SceneNode* Node)
{
	if(lCamera)
	{
		lCamera->setPosition(Node->getPosition());
		Node->attachObject(lCamera);
	}
}

void OgreManager::ceguiInit()
{
	GUIRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*lWindow);
	
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeels");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().create((CEGUI::utf8*)"TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

	CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());
}
