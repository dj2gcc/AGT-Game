#pragma once

#include "OgreManager.h"
#include "OgreInputManager.h"
#include "Interface.h"

#include <CEGUI.h>
#include <CEGUISystem.h>

#include<string>


class GamePlay : public Interface
{
private:

	OgreManager* _OgreManager;

	CEGUI::Window* _CEGUISheet;
	CEGUI::Window* _QuitButton;

public:

	GamePlay();
	GamePlay(OgreManager* om);
	~GamePlay();

	bool gameplayInit();

	void update();

	void cleanUp();

	bool CEGUIEventQuit(const CEGUI::EventArgs& arg);

	//Ogre::WindowListener
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
};