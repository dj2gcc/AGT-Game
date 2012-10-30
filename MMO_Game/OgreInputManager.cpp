#include "OgreManager.h"
#include "GameStateManager.h"

OgreInputManager* OgreInputManager::_Instance = NULL;
Interface* OgreInputManager::_Interface = NULL;

OgreInputManager* OgreInputManager::Instance()
{
	if(!_Instance)
	{
		_Instance = new OgreInputManager();
		_Instance->initInput(OgreManager::Instance()->getWindow());
	}

	return _Instance;
}

void OgreInputManager::setInterface(Interface* i)
{
	_Interface = i;
}

OgreInputManager::OgreInputManager()
{
}

OgreInputManager::~OgreInputManager()
{
	Ogre::LogManager::getSingleton().logMessage("End of InputManager");
	//system("pause");
}

bool OgreInputManager::initInput(Ogre::RenderWindow* window)
{
	OIS::ParamList pl;

	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	window->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	
	_InputManager = OIS::InputManager::createInputSystem(pl);
	
	_Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject(OIS::OISMouse, false));
	_Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject(OIS::OISKeyboard, false));
	
	unsigned int width, height, depth;
	int top, left;
	window->getMetrics(width, height, depth, left, top);
	const OIS::MouseState & ms = _Mouse->getMouseState();
	ms.width = width;
	ms.height = height;

	_Mouse->setBuffered(true);
	_Keyboard->setBuffered(true);

	_Mouse->setEventCallback(this);
	_Keyboard->setEventCallback(this);

	Ogre::WindowEventUtilities::addWindowEventListener(OgreManager::Instance()->getWindow(), this);

	OgreManager::Instance()->getRoot()->addFrameListener(this);

	return true;
}

bool OgreInputManager::forceMouseIntoPosition(float x, float y)
{
	OIS::MouseState &mutableMouseState = const_cast<OIS::MouseState &>(_Mouse->getMouseState());
	mutableMouseState.X.abs = x;
	mutableMouseState.Y.abs = y;

	return true;
}

CEGUI::MouseButton OgreInputManager::convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}

//Ogre::WindowListener
bool OgreInputManager::windowClosing(Ogre::RenderWindow* rw)
{
	if(_Interface)
	{
		_Interface->windowClosing(rw);
	}
	return true;
}

void OgreInputManager::windowClosed(Ogre::RenderWindow* rw)
{
	if(_Interface)
	{
		_Interface->windowClosed(rw);
	}
}

// Ogre::FrameListener
bool OgreInputManager::frameRenderingQueued(const Ogre::FrameEvent& evt )
{
	_Keyboard->capture();
	_Mouse->capture();

	if(_Interface)
	{
		_Interface->frameRenderingQueued(evt);
	}
	return true;
}

// OIS::KeyListener
bool OgreInputManager::keyPressed( const OIS::KeyEvent& evt )
{
	if(_Interface)
	{
		_Interface->keyPressed(evt);
	}
	return true;
}

bool OgreInputManager::keyReleased( const OIS::KeyEvent& evt )
{
	if(_Interface)
	{
		_Interface->keyReleased(evt);
	}
	return true;
}

// OIS::MouseListener
bool OgreInputManager::mouseMoved( const OIS::MouseEvent& evt )
{
	if(_Interface)
	{
		_Interface->mouseMoved(evt);
	}
	return true;
}

bool OgreInputManager::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	if(_Interface)
	{
		_Interface->mousePressed(evt, id);
	}
	return true;
}

bool OgreInputManager::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	if(_Interface)
	{
		_Interface->mouseReleased(evt, id);
	}
	return true;
}

void OgreInputManager::destroyInputManager()
{
	if(_InputManager) {
        if(_Mouse) {
            _InputManager->destroyInputObject(_Mouse);
            _Mouse = NULL;
        }
 
        if(_Keyboard) {
            _InputManager->destroyInputObject(_Keyboard);
            _Keyboard = NULL;
        }
 
		/*delete _Instance;
		_Instance = NULL;*/

        _InputManager->destroyInputSystem(_InputManager);
        _InputManager = NULL;
    }
}