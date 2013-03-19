#include "GameStateManager.h"
#include "PlayerController.h"

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
	//Resource Group Init
		_OgreManager->addResourceGroup(Ogre::String("GameResources"), false);

		char buffer[MAX_PATH]; 
		GetModuleFileName( NULL, buffer, MAX_PATH ); 
		std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" ); 
		std::string s = std::string( buffer ).substr( 0, pos); 

		_OgreManager->addResourceLocation(Ogre::String(s + "\\Resources\\"), Ogre::String("FileSystem"), Ogre::String("GameResources"), false);
		_OgreManager->getRgm()->initialiseResourceGroup(Ogre::String("GameResources"));
	//Resource Group Init End

	//Terrain Init
		TerrainManager::Instance()->terrainInit(Ogre::String("terrain.png"), _OgreManager);
	//Terrain Init end

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

	//Create gui
		CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		_CEGUISheet = wmgr.createWindow("DefaultWindow", "OgreGame/MainSheet");

		_QuitButton = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/QuitButton");
		_QuitButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
		_QuitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45, 0) ,CEGUI::UDim(0.475, 0)));
		_QuitButton->setText("Quit");
		_QuitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GamePlay::CEGUIEventQuit, this));
		_CEGUISheet->addChildWindow(_QuitButton);

		_QuitButton->hide();

		CEGUI::System::getSingleton().setGUISheet(_CEGUISheet);
	//Create gui end

	//Init control settings
		_Up = OIS::KC_W;
		_Down = OIS::KC_S;
		_Left = OIS::KC_A;
		_Right = OIS::KC_D;
		_LeftSide = OIS::KC_Q;
		_RightSide = OIS::KC_E;
		_Jump = OIS::KC_SPACE;
		_Inventory = OIS::KC_B;

	//Init control settings end

	//Initialise world data

		//_World = new World();

		_World->populate();
	//Initialise world data end

	//Init GUI

		GUI->initialise(_CEGUISheet, _World->getPlayer());

	//Init GUI end

	_OgreManager->getRoot()->clearEventTimes();

	return true;
}

void GamePlay::cleanUp()
{
	CEGUI::WindowManager::getSingleton().destroyAllWindows();
	_OgreManager->removeResourceGroup("GameResources");
	TerrainManager::Instance()->clearTerrainManager();

	_World->destroy();

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

	Time->update(evt.timeSinceLastFrame);

	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

	_World->update(evt.timeSinceLastFrame);

	GUI->update(evt.timeSinceLastFrame);

	return true;
}

// OIS::KeyListener
bool GamePlay::keyPressed( const OIS::KeyEvent& evt )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectKeyDown(evt.key);
	sys.injectChar(evt.text);

	_World->getInControl()->keyPressed(evt);


	if(evt.key == OIS::KC_ESCAPE)
	{
		if(_QuitButton->isVisible())
		{
			_QuitButton->hide();
		}else
		{
			_QuitButton->setVisible(true);
		}
	}

	return true;
}

bool GamePlay::keyReleased( const OIS::KeyEvent& evt )
{
	CEGUI::System::getSingleton().injectKeyUp(evt.key);

	_World->getInControl()->keyReleased(evt);

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
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMouseButtonDown(OgreInputManager::Instance()->convertButton(id));

	if(id == 0 && sys.getWindowContainingMouse() == _CEGUISheet)
	{
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();

		//then send a raycast straight out from the camera at the mouse's position
		Ogre::Ray mouseRay = _OgreManager->getCamera()->getCameraToViewportRay(mousePos.d_x/float(evt.state.width), mousePos.d_y/float(evt.state.height));
	
		Ogre::RaySceneQuery* mRayScnQuery;

		mRayScnQuery = _OgreManager->getSceneManager()->createRayQuery(Ogre::Ray());

		mRayScnQuery->setRay(mouseRay);

		Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
		Ogre::RaySceneQueryResult::iterator iter = result.begin();

		bool hit = false;

		for(iter; iter != result.end(); iter++)
		{
			if(iter->movable && iter->movable->getName() != "" && iter->movable->getName().at(0) == 'B')
			{
				std::string id = iter->movable->getName();
				id.erase(0,1);

				_World->getPlayer()->_Target = _World->getCharacter(atoi(id.c_str()));
				GUI->showTarget(true);

				hit = true;
			}
		}

		if(!hit)
		{
			_World->getPlayer()->_Target = NULL;
			GUI->showTarget(false);
		}
	}
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