#pragma once

#include "OIS.h"
#include "OgreFrameListener.h"
#include "OgreRenderWindow.h"

class Interface
{
public:

	Interface(){}
	virtual ~Interface(){}

	//Ogre::WindowListener
	virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }

	virtual void windowClosed(Ogre::RenderWindow* rw) {}
	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt ) { return true; }
	
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent& evt ) { return true; }
	virtual bool keyReleased( const OIS::KeyEvent& evt ) { return true; }
	
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent& evt ) { return true; }
	virtual bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id ) { return true; }
	virtual bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id ) { return true; }
};