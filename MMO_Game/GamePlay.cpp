#include "GameStateManager.h"

GamePlay::GamePlay()
{
	_OgreManager = StateManager.getOgreManager();
}

GamePlay::GamePlay(OgreManager* om)
{
	_OgreManager = om;
}

GamePlay::~GamePlay()
{
	Ogre::LogManager::getSingleton().logMessage("End of GamePlay");
}

bool GamePlay::gameplayInit()
{
	//CEGUI Init
		if(!_OgreManager->getCEGUIStatus())
		{
			_OgreManager->ceguiInit();

			//Sync mouse position
				CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
				OgreInputManager::Instance()->forceMouseIntoPosition(mousePos.d_x, mousePos.d_y);
			//Sync mouse position end
		}		
	//CEGUI Init end

	//Create Menu
		CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		_CEGUISheet = wmgr.createWindow("DefaultWindow", "OgreGame/MainSheet");

		_QuitButton = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/QuitButton");
		_QuitButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
		_QuitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45, 0) ,CEGUI::UDim(0.475, 0)));
		_QuitButton->setText("Quit");
		_QuitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GamePlay::CEGUIEventQuit, this));
		_CEGUISheet->addChildWindow(_QuitButton);

		CEGUI::System::getSingleton().setGUISheet(_CEGUISheet);
	//Create Menu end

	_OgreManager->getRoot()->clearEventTimes();
	return true;
}

void GamePlay::cleanUp()
{
	CEGUI::WindowManager::getSingleton().destroyAllWindows();
}

void GamePlay::update()
{
	Ogre::WindowEventUtilities::messagePump();

	_OgreManager->getWindow()->update(false);
	
	_OgreManager->getRoot()->renderOneFrame();

	_OgreManager->getWindow()->swapBuffers(true);
}

//Ogre::WindowListener
void GamePlay::windowClosed(Ogre::RenderWindow* rw)
{
	if(rw->getName() == "MainWindow")
	{
		StateManager.ChangeState(CleanupState);
	}
}

// Ogre::FrameListener
bool GamePlay::frameRenderingQueued(const Ogre::FrameEvent& evt )
{
	if(_OgreManager->getWindow()->isClosed())
		return false;

	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

	return true;
}

// OIS::KeyListener
bool GamePlay::keyPressed( const OIS::KeyEvent& evt )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectKeyDown(evt.key);
	sys.injectChar(evt.text);
	return true;
}

bool GamePlay::keyReleased( const OIS::KeyEvent& evt )
{
	CEGUI::System::getSingleton().injectKeyUp(evt.key);
	return true;
}

// OIS::MouseListener
bool GamePlay::mouseMoved( const OIS::MouseEvent& evt )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);

	if (evt.state.Z.rel)
		sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
	return true;
}

bool GamePlay::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonDown(OgreInputManager::Instance()->convertButton(id));
	return true;
}

bool GamePlay::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonUp(OgreInputManager::Instance()->convertButton(id));
	return true;
}

bool GamePlay::CEGUIEventQuit(const CEGUI::EventArgs& arg)
{
	if(StateManager.getMainMenu())
		StateManager.ChangeState(MenuState);
	else
		StateManager.ChangeState(CleanupState);

	return true;
}