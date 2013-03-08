#include "OgreManager.h"

OgreManager* OgreManager::_Instance = NULL;

OgreManager* OgreManager::Instance()
{
	if(!_Instance)
	{
		_Instance = new OgreManager();
	}

	return _Instance;
}

OgreManager::OgreManager()
{
	_Root = NULL;
	_Window = NULL;
	_Scene = NULL;
	_RGM = NULL;

	_Camera = NULL;

	_GUIRenderer = NULL;
}

OgreManager::~OgreManager()
{
	Ogre::LogManager::getSingleton().logMessage("End of OgreManager");

	delete _Root;
}

bool OgreManager::initRenderSystem()
{
	if(_Root)
		return true;

	Ogre::String lConfigFileName = "";
	Ogre::String lPluginsFileName = "";
	Ogre::String lLogFileName = "MMOLog.LOG";

	_Root = new Ogre::Root(lConfigFileName, lPluginsFileName, lLogFileName);

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
		_Root->loadPlugin(lPluginName);
	}

	const Ogre::RenderSystemList& lRenderSystemList = _Root->getAvailableRenderers();
	if(lRenderSystemList.size() == 0)
	{
		Ogre::LogManager::getSingleton().logMessage("Sorry, no rendersystem was found.");
		return false;
	}

	_Root->setRenderSystem(lRenderSystemList[0]);

	return true;
}

Ogre::RenderWindow* OgreManager::createWindow(bool autoCreate, Ogre::String name, unsigned int xsize, unsigned int ysize)
{
	if(_Window)
		return _Window;

	bool lCreateAWindowAutomatically = autoCreate;
	Ogre::String lWindowTitle = name;
	Ogre::String lCustomCapacities = "";

	if(!(lCreateAWindowAutomatically))
	{
		unsigned int lSizeX = xsize;
		unsigned int lSizeY = ysize;
		
		bool lFullscreen = false;
		
		Ogre::NameValuePairList lParams;
		lParams["vsync"] = "true";

		_Root->initialise(autoCreate);

		_Window = _Root->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
		
	}else
	{
		_Window = _Root->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);
	}

	return _Window;
}

bool OgreManager::sceneManagerInit(Ogre::String name)
{
	if(_Scene)
		return true;

	_Scene = _Root->createSceneManager("TerrainSceneManager", name);

	return true;
}

bool OgreManager::createCamera(Ogre::String name)
{
	if(_Camera)
		return true;

	_Camera = _Scene->createCamera(name);

	unsigned short lMainViewportZOrder = 100;
	Ogre::Viewport* vp = _Window->addViewport(_Camera, lMainViewportZOrder, 0, 0, 1, 1);
	vp->setAutoUpdated(true);
	vp->setBackgroundColour(Ogre::ColourValue(1,0,0));

	float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
	_Camera->setAspectRatio(ratio);

	_Window->setActive(true);
	_Window->setAutoUpdated(false);

	return true;
}

bool OgreManager::loadResourcesFromConfig()
{
	if(_RGM)
		return true;

	Ogre::String resources = "resources";

	if(OGRE_DEBUG_MODE)
	{
		resources.append("_d.cfg");
	}else
	{
		resources.append(".cfg");
	}

	_RGM = &Ogre::ResourceGroupManager::getSingleton();

	Ogre::ConfigFile cf;
	cf.load(resources);

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

	return true;
}

void OgreManager::addResourceGroup(Ogre::String name, bool globalPool)
{
	_RGM->createResourceGroup(name, globalPool);
}

void OgreManager::removeResourceGroup(Ogre::String name)
{
	_RGM->destroyResourceGroup(name);
}

void OgreManager::addResourceLocation(Ogre::String location, Ogre::String type, Ogre::String group, bool recursive)
{
	_RGM->addResourceLocation(location, type, group, recursive);
}


bool OgreManager::ceguiInit()
{
	if(_GUIRenderer)
		return true;

	_GUIRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*_Window);
	
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeels");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().create((CEGUI::utf8*)"TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

	CEGUI::ImagesetManager::getSingleton().create("SkillsImageset.imageset");

	CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());

	return true;
}