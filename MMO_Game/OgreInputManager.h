#pragma once

#include "OIS.h"
#include "OgreFrameListener.h"
#include "OgreWindowEventUtilities.h"
#include "OgreRenderWindow.h"
#include "OgreLogManager.h"

#include "CEGUI.h"

#include "Interface.h"

class OgreInputManager : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{
private:

	OgreInputManager();
	~OgreInputManager();

	static Interface* _Interface;

	OIS::InputManager* _InputManager;
	OIS::Mouse* _Mouse;
	OIS::Keyboard* _Keyboard;

	//Ogre::WindowListener
	bool windowClosing(Ogre::RenderWindow* rw);

	void windowClosed(Ogre::RenderWindow* rw);

	// Ogre::FrameListener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt );
	
	// OIS::KeyListener
	bool keyPressed( const OIS::KeyEvent& evt );
	bool keyReleased( const OIS::KeyEvent& evt );
	
	// OIS::MouseListener
	bool mouseMoved( const OIS::MouseEvent& evt );
	bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id );

public:

	bool initInput(Ogre::RenderWindow* window);

	static OgreInputManager* Instance();

	void setInterface(Interface* i);

	bool forceMouseIntoPosition(float x, float y);

	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

	void destroyInputManager();
	
};