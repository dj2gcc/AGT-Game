#include "OgreInputManager.h"

bool OgreInputManager::initInput(Ogre::RenderWindow* window)
{
	OIS::ParamList pl;

	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	window->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	
	im = OIS::InputManager::createInputSystem(pl);
	
	mouse = static_cast<OIS::Mouse*>(im->createInputObject(OIS::OISMouse, false));
	keyboard = static_cast<OIS::Keyboard*>(im->createInputObject(OIS::OISKeyboard, false));
	
	unsigned int width, height, depth;
	int top, left;
	window->getMetrics(width, height, depth, left, top);
	const OIS::MouseState & ms = mouse->getMouseState();
	ms.width = width;
	ms.height = height;

	return true;
}

bool OgreInputManager::forceMouseIntoPosition(float x, float y)
{
	OIS::MouseState &mutableMouseState = const_cast<OIS::MouseState &>(mouse->getMouseState());
	mutableMouseState.X.abs = x;
	mutableMouseState.Y.abs = y;

	return true;
}

// Ogre::FrameListener
bool OgreInputManager::frameRenderingQueued(const Ogre::FrameEvent& evt )
{
	return true;
}

// OIS::KeyListener
bool OgreInputManager::keyPressed( const OIS::KeyEvent& evt )
{
	return true;
}

bool OgreInputManager::keyReleased( const OIS::KeyEvent& evt )
{
	return true;
}

// OIS::MouseListener
bool OgreInputManager::mouseMoved( const OIS::MouseEvent& evt )
{
	return true;
}

bool OgreInputManager::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	return true;
}

bool OgreInputManager::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	return true;
}