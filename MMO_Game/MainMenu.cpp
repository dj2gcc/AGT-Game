#include "MainMenu.h"

MainMenu::MainMenu(OgreManager* om)
{
	_OgreManager = new OgreManager();
}

MainMenu::~MainMenu()
{
}

bool MainMenu::menuInit()
{
	_OgreManager->initRenderSystem();

	_OgreManager->createWindow(false, "MainWindow");

	//Resource Group Init
		_OgreManager->loadResourcesFromConfig();
		_OgreManager->addResourceGroup(Ogre::String("GameResources"), false);

		char buffer[MAX_PATH]; 
		GetModuleFileName( NULL, buffer, MAX_PATH ); 
		std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" ); 
		std::string s = std::string( buffer ).substr( 0, pos); 

		_OgreManager->addResourceLocation(Ogre::String(s + "\\Resources\\"), Ogre::String("FileSystem"), Ogre::String("GameResources"), false);
		_OgreManager->getRgm()->initialiseResourceGroup(Ogre::String("GameResources"));
	//Resource Group Init End

	//Camera and Window init

		

		_OgreManager->sceneManagerInit("MainSceneManager");

		_OgreManager->createCamera("MainCamera");

	//Camera and Window init end

	//Input Init
		initInput(_OgreManager->getWindow());

		mouse->setBuffered(true);
		keyboard->setBuffered(true);

		mouse->setEventCallback(this);
		keyboard->setEventCallback(this);

		Ogre::WindowEventUtilities::addWindowEventListener(_OgreManager->getWindow(), this);

		_OgreManager->getRoot()->addFrameListener(this);
	//Input Init end

	//CEGUI Init
		_OgreManager->ceguiInit();
	//CEGUI Init end

	//Create Menu
		CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		_CEGUISheet = wmgr.createWindow("DefaultWindow", "OgreGame/MainSheet");

		_PlayButton = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/PlayButton");
		_PlayButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
		_PlayButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3, 0) ,CEGUI::UDim(0.5, 0)));
		_PlayButton->setText("Play");
		_CEGUISheet->addChildWindow(_PlayButton);

		_QuitButton = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/QuitButton");
		_QuitButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
		_QuitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.6, 0) ,CEGUI::UDim(0.5, 0)));
		_QuitButton->setText("Quit");
		_CEGUISheet->addChildWindow(_QuitButton);

		CEGUI::System::getSingleton().setGUISheet(_CEGUISheet);
	//Create Menu end

	CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
	forceMouseIntoPosition(mousePos.d_x, mousePos.d_y);
	
	_OgreManager->getRoot()->clearEventTimes();
		return true;
}

void MainMenu::update()
{
	while(!_OgreManager->getWindow()->isClosed())
	{
		Ogre::WindowEventUtilities::messagePump();

		_OgreManager->getWindow()->update(false);
	
		_OgreManager->getRoot()->renderOneFrame();

		_OgreManager->getWindow()->swapBuffers(true);
	}
		
}

// Ogre::FrameListener
bool MainMenu::frameRenderingQueued(const Ogre::FrameEvent& evt )
{
	mouse->capture();
	keyboard->capture();

	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

	return true;
}

// OIS::KeyListener
bool MainMenu::keyPressed( const OIS::KeyEvent& evt )
{
	return true;
}

bool MainMenu::keyReleased( const OIS::KeyEvent& evt )
{
	return true;
}

// OIS::MouseListener
bool MainMenu::mouseMoved( const OIS::MouseEvent& evt )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
	// Scroll wheel.
	if (evt.state.Z.rel)
		sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
	return true;
}

bool MainMenu::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	return true;
}

bool MainMenu::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	return true;
}
