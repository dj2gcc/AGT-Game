#pragma once

#include "OgreManager.h"
#include "OgreInputManager.h"
#include "TerrainManager.h"
#include "Interface.h"

#include <CEGUI.h>
#include <CEGUISystem.h>

#include <iostream>
#include <fstream>
#include <ctime>
#include "windows.h"

#include<string>

#include "World.h"

struct mapData
{
	unsigned char* buffer;
	int size;
};


class MapEditor : public Interface
{
private:

	CEGUI::Window* _CEGUISheet;
	CEGUI::Window* _QuitButton;
	CEGUI::Window* _GenerateButton;

	mapData data;

	std::ofstream editorLog;

	int slotSize;

	std::string _ChangeState;

public:

	MapEditor();
	~MapEditor();

	void normalizeTerrain(float* fpHeightData);

	bool makeTerrain(float fRoughness);

	inline float rangedRandom(float f1, float f2);	

	bool convertToData(float* buffer);

	bool writeToFiles(char* name);

		bool mapeditorInit();

		void update();

		void cleanUp();

		bool CEGUIEventQuit(const CEGUI::EventArgs& arg);

		bool CEGUIEventGenerate(const CEGUI::EventArgs& arg);

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