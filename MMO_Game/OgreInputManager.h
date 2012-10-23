#include "OIS.h"
#include "OgreFrameListener.h"
#include "OgreWindowEventUtilities.h"
#include "OgreRenderWindow.h"

class OgreInputManager : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{
protected:

	OIS::InputManager* im;
	OIS::Mouse* mouse;
	OIS::Keyboard* keyboard;

	bool initInput(Ogre::RenderWindow* window);

	bool forceMouseIntoPosition(float x, float y);

	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt );
	
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent& evt );
	virtual bool keyReleased( const OIS::KeyEvent& evt );
	
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent& evt );
	virtual bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id );

};