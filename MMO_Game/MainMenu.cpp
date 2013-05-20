#include "GameStateManager.h"

MainMenu::MainMenu() : Interface()
{
	_OgreManager = StateManager.getOgreManager();
	_ChangeState = "";
}

MainMenu::MainMenu(OgreManager* om) : Interface()
{
	_OgreManager = om;
	_ChangeState = "";
}

MainMenu::~MainMenu()
{
	Ogre::LogManager::getSingleton().logMessage("End of MainMenu");
}

bool MainMenu::menuInit()
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

		_PlayButton = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/PlayButton");
		_PlayButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
		_PlayButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3, 0) ,CEGUI::UDim(0.5, 0)));
		_PlayButton->setText("Play");
		_PlayButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::CEGUIEventPlay, this));
		_CEGUISheet->addChildWindow(_PlayButton);

		_QuitButton = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/QuitButton");
		_QuitButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
		_QuitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.6, 0) ,CEGUI::UDim(0.5, 0)));
		_QuitButton->setText("Quit");
		_QuitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::CEGUIEventQuit, this));
		_CEGUISheet->addChildWindow(_QuitButton);

		_EditButton = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/EditButton");
		_EditButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
		_EditButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45, 0) ,CEGUI::UDim(0.6, 0)));
		_EditButton->setText("Edit");
		_EditButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::CEGUIEventEdit, this));
		_CEGUISheet->addChildWindow(_EditButton);

		CEGUI::System::getSingleton().setGUISheet(_CEGUISheet);
	//Create Menu end

	_OgreManager->getRoot()->clearEventTimes();
	return true;
}

void MainMenu::cleanUp()
{
	CEGUI::WindowManager::getSingleton().destroyAllWindows();
}

void MainMenu::update()
{
	Ogre::WindowEventUtilities::messagePump();

	_OgreManager->getWindow()->update(false);
	
	_OgreManager->getRoot()->renderOneFrame();

	_OgreManager->getWindow()->swapBuffers(true);

	if(_ChangeState != "")
	{
		if(_ChangeState == "Quit")
		{
			_ChangeState = "";
			StateManager.ChangeState(CleanupState);			
		}else
			if(_ChangeState == "Play")
			{
				_ChangeState = "";
				StateManager.ChangeState(PlayState);
			}else
				if(_ChangeState == "Edit")
				{
					_ChangeState = "";
					StateManager.ChangeState(EditState);
				}
	}
}

//Ogre::WindowListener
void MainMenu::windowClosed(Ogre::RenderWindow* rw)
{
	if(rw->getName() == "MainWindow")
	{
		StateManager.ChangeState(CleanupState);
	}
}

// Ogre::FrameListener
bool MainMenu::frameRenderingQueued(const Ogre::FrameEvent& evt )
{
	if(_OgreManager->getWindow()->isClosed())
		return false;

	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

	return true;
}

// OIS::KeyListener
bool MainMenu::keyPressed( const OIS::KeyEvent& evt )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectKeyDown(evt.key);
	sys.injectChar(evt.text);
	return true;
}

bool MainMenu::keyReleased( const OIS::KeyEvent& evt )
{
	CEGUI::System::getSingleton().injectKeyUp(evt.key);
	return true;
}

// OIS::MouseListener
bool MainMenu::mouseMoved( const OIS::MouseEvent& evt )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);

	if (evt.state.Z.rel)
		sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
	return true;
}

bool MainMenu::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonDown(OgreInputManager::Instance()->convertButton(id));
	return true;
}

bool MainMenu::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonUp(OgreInputManager::Instance()->convertButton(id));
	return true;
}

bool MainMenu::CEGUIEventPlay(const CEGUI::EventArgs& arg)
{
	_ChangeState = "Play";
	return true;
}

bool MainMenu::CEGUIEventQuit(const CEGUI::EventArgs& arg)
{
	_ChangeState = "Quit";

	return true;
}

bool MainMenu::CEGUIEventEdit(const CEGUI::EventArgs& arg)
{
	_ChangeState = "Edit";

	return true;
}