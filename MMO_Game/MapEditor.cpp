#include "GameStateManager.h"

MapEditor::MapEditor()
{
	slotSize = 512;
	data.size = 512 * 4;
	data.buffer = new unsigned char[data.size*data.size];
	_ChangeState = "";
}

MapEditor::~MapEditor()
{
	Ogre::LogManager::getSingleton().logMessage("End of MapEditor");
}

bool MapEditor::mapeditorInit()
{
	//CEGUI Init
		if(!OgreManager::Instance()->getCEGUIStatus())
		{
			OgreManager::Instance()->ceguiInit();

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
		_QuitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3, 0) ,CEGUI::UDim(0.5, 0)));
		_QuitButton->setText("Quit");
		_QuitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MapEditor::CEGUIEventQuit, this));
		_CEGUISheet->addChildWindow(_QuitButton);

		_GenerateButton = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/GenerateButton");
		_GenerateButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
		_GenerateButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.6, 0) ,CEGUI::UDim(0.5, 0)));
		_GenerateButton->setText("Generate");
		_GenerateButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MapEditor::CEGUIEventGenerate, this));
		_CEGUISheet->addChildWindow(_GenerateButton);

		CEGUI::System::getSingleton().setGUISheet(_CEGUISheet);
	//Create gui end

	editorLog.open("EditorLog.txt", std::ios::trunc);

	if(editorLog.fail())
	{
		std::cout << "Could not open/create the EditorLog file." << std::endl;
	}

	return true;
}

void MapEditor::cleanUp()
{
	CEGUI::WindowManager::getSingleton().destroyAllWindows();

	editorLog.close();
}

void MapEditor::update()
{
	Ogre::WindowEventUtilities::messagePump();

	OgreManager::Instance()->getWindow()->update(false);
	
	OgreManager::Instance()->getRoot()->renderOneFrame();

	OgreManager::Instance()->getWindow()->swapBuffers(true);

	if(_ChangeState != "")
	{
		if(_ChangeState == "Quit")
		{
			if(StateManager.getMainMenu())
			{
				_ChangeState = "";
				StateManager.ChangeState(MenuState);
			}else
			{
				_ChangeState = "";
				StateManager.ChangeState(CleanupState);
			}
		}
	}

}

//Ogre::WindowListener
void MapEditor::windowClosed(Ogre::RenderWindow* rw)
{
	if(rw->getName() == "MainWindow")
	{
		StateManager.ChangeState(CleanupState);
	}
}

// Ogre::FrameListener
bool MapEditor::frameRenderingQueued(const Ogre::FrameEvent& evt )
{
	if(OgreManager::Instance()->getWindow()->isClosed())
		return false;

	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

	return true;
}

// OIS::KeyListener
bool MapEditor::keyPressed( const OIS::KeyEvent& evt )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectKeyDown(evt.key);
	sys.injectChar(evt.text);

	return true;
}

bool MapEditor::keyReleased( const OIS::KeyEvent& evt )
{
	CEGUI::System::getSingleton().injectKeyUp(evt.key);
	
	return true;
}

// OIS::MouseListener
bool MapEditor::mouseMoved( const OIS::MouseEvent& evt )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);

	if (evt.state.Z.rel)
		sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
	return true;
}

bool MapEditor::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonDown(OgreInputManager::Instance()->convertButton(id));
	return true;
}

bool MapEditor::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonUp(OgreInputManager::Instance()->convertButton(id));
	return true;
}

bool MapEditor::CEGUIEventQuit(const CEGUI::EventArgs& arg)
{
	_ChangeState = "Quit";

	return true;
}

bool MapEditor::CEGUIEventGenerate(const CEGUI::EventArgs& arg)
{
	makeTerrain(2);
	writeToFiles("");
	return true;
}

float MapEditor::rangedRandom(float f1, float f2)
{		
	return ( f1+( f2-f1 )*( ( float )rand( ) )/( ( float )RAND_MAX ) );
} 

void MapEditor::normalizeTerrain( float* fpHeightData )   
{   
	editorLog << "Normalizing terrain." << std::endl;

	float fMin, fMax;   
	float fHeight;   
	int i;   

	fMin= fpHeightData[0];   
	fMax= fpHeightData[0];   
       
	//find the min/max values of the height fTempBuffer   
	for( i=1; i<data.size*data.size; i++ )   
	{   
		if( fpHeightData[i]>fMax )    
			fMax= fpHeightData[i];   
       
		else if( fpHeightData[i]<fMin )    
			fMin= fpHeightData[i];   
	}   
       
	//find the range of the altitude   
	if( fMax<=fMin )   
		return;   
       
	fHeight= fMax-fMin;   
       
	//scale the values to a range of 0-255 (because I like things that way)   
	for( i=0; i<data.size*data.size; i++ )   
	{
		fpHeightData[i]= ( ( fpHeightData[i]-fMin )/fHeight )*255.0f; 
	}
}   

bool MapEditor::makeTerrain(float fRoughness )   
{   
	srand(time(0));

	float* fTempBuffer;   
	float fHeight, fHeightReducer;   
	int iRectSize= 512;   
	int ni, nj;   
	int mi, mj;   
	int pmi, pmj;   
	int i, j;   
	int x, z;   
       
	if( fRoughness<0 )   
		fRoughness*= -1;   
       
	fHeight       = ( float )512/2;   
	fHeightReducer= ( float )pow(2, -1*fRoughness);   
       
	int m_iSize= data.size;   
       
	//allocate the memory for our height data   
	fTempBuffer= new float [m_iSize*m_iSize];   
       
	//check to see if memory was successfully allocated   
	if( fTempBuffer==NULL )   
	{   
		//something is seriously wrong here   
		std::cout << "Could not allocate memory for height map";   
		return false;   
	}   
    
	//for(int a=0; a<data.size*data.size; a++ )   
	//{
	//	fTempBuffer[a]= rangedRandom( -fHeight/2, fHeight/2 );
	//}

	fTempBuffer[0] = 0.0f;

	editorLog << "Generating heightmap size " << (data.size * data.size) << "." << std::endl;
      
	while( iRectSize>0 )   
	{   
		/*Diamond step -  
    
		Find the values at the center of the retangles by averaging the values at   
		the corners and adding a random offset:  
     
      
		a.....b  
		.     .    
		.  e  .  
		.     .  
		c.....d     
    
		e  = (a+b+c+d)/4 + random  
      
		In the code below:  
		a = (i,j)  
		b = (ni,j)  
		c = (i,nj)  
		d = (ni,nj)  
		e = (mi,mj)   */   
		for( i=0; i<m_iSize; i+=iRectSize )   
		{   
			for( j=0; j<m_iSize; j+=iRectSize )   
			{   
				ni= ( i+iRectSize )%m_iSize;   
				nj= ( j+iRectSize )%m_iSize;   
     
				mi= ( i+iRectSize/2 );   
				mj= ( j+iRectSize/2 );   
     
				fTempBuffer[mi+mj*m_iSize]= ( float )( ( fTempBuffer[i+j*m_iSize] + fTempBuffer[ni+j*m_iSize] + fTempBuffer[i+nj*m_iSize] + fTempBuffer[ni+nj*m_iSize] )/4 + rangedRandom( -fHeight/2, fHeight/2 ) );   
			}   
		}   
     
		/*Square step -  
    
		Find the values on the left and top sides of each rectangle  
		The right and bottom sides are the left and top sides of the neighboring rectangles,  
		so we don't need to calculate them  
    
		The height m_heightData.m_ucpData wraps, so we're never left hanging.  The right side of the last  
		rectangle in a row is the left side of the first rectangle in the row.  The bottom  
		side of the last rectangle in a column is the top side of the first rectangle in  
		the column  
    
					  .......  
					  .     .  
					  .     .  
					  .  d  .  
					  .     .  
					  .     .  
				......a..g..b  
				.     .     .  
				.     .     .  
				.  e  h  f  .  
				.     .     .  
				.     .     .  
				......c......  
      			g = (d+f+a+b)/4 + random  
				h = (a+c+e+f)/4 + random  
            
		In the code below:  
			a = (i,j)   
			b = (ni,j)   
			c = (i,nj)   
			d = (mi,pmj)   
			e = (pmi,mj)   
			f = (mi,mj)   
			g = (mi,j)  
			h = (i,mj)*/   
		for( i=0; i<m_iSize; i+=iRectSize )   
		{   
			for( j=0; j<m_iSize; j+=iRectSize )   
			{   
       			ni= (i+iRectSize)%m_iSize;   
				nj= (j+iRectSize)%m_iSize;   
       
				mi= (i+iRectSize/2);   
				mj= (j+iRectSize/2);   
      			pmi= (i-iRectSize/2+m_iSize)%m_iSize;   
				pmj= (j-iRectSize/2+m_iSize)%m_iSize;   
                     
				//Calculate the square value for the top side of the rectangle   
				fTempBuffer[mi+j*m_iSize]= ( float )( ( fTempBuffer[i+j*m_iSize]      +   
														fTempBuffer[ni+j*m_iSize]     +   
														fTempBuffer[mi+pmj*m_iSize]   +   
														fTempBuffer[mi+mj*m_iSize] )/4+   
														rangedRandom( -fHeight/2, fHeight/2 ) );   
       			
				//Calculate the square value for the left side of the rectangle   
				fTempBuffer[i+mj*m_iSize]= ( float )( ( fTempBuffer[i+j*m_iSize]      +   
														fTempBuffer[i+nj*m_iSize]     +   
														fTempBuffer[pmi+mj*m_iSize]   +   
														fTempBuffer[mi+mj*m_iSize] )/4+    
														rangedRandom( -fHeight/2, fHeight/2 ) );   
			}   
		}   
       	//reduce the rectangle size by two to prepare for the next   
		//displacement stage   
		iRectSize/= 2;   
		editorLog << "iRectSize = " << iRectSize << std::endl;
		editorLog << "fHeightReducer = " << fHeightReducer << std::endl;
      
		//reduce the height by the height reducer   
		fHeight*= fHeightReducer;   
		editorLog << "fHeight = " << fHeight << std::endl << std::endl << std::endl;
	}  


	normalizeTerrain(fTempBuffer);

	convertToData(fTempBuffer);
       
	//delete temporary buffer   
	if( fTempBuffer )   
	{   
		//delete the data   
		delete[] fTempBuffer;   
	}   
       
	return true;
}  

bool MapEditor::convertToData(float* buffer)
{
	editorLog << "Converting to char." << std::endl;
	//transfer the terrain into our class's unsigned char height buffer   
	for(int z = 0; z < data.size; z++ )   
	{   
		for(int x = 0; x < data.size; x++ ) 
		{
			data.buffer[(z*data.size) + x] = (unsigned char)buffer[( z*data.size )+x];   
		}
	}   

	return true;
}

bool MapEditor::writeToFiles(char* name)
{
	editorLog << "Writing to files." << std::endl;

	HANDLE file = NULL;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER fileInfo;
    RGBTRIPLE *image;
    DWORD write = 0;
	image = new RGBTRIPLE[slotSize*slotSize];
 
    fileHeader.bfType = 19778;                                                                    //Sets our type to BM or bmp
    fileHeader.bfSize = sizeof(fileHeader.bfOffBits) + sizeof(RGBTRIPLE);                                                //Sets the size equal to the size of the header struct
    fileHeader.bfReserved1 = 0;                                                                    //sets the reserves to 0
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);                    //Sets offbits equal to the size of file and info header
 
    fileInfo.biSize = sizeof(BITMAPINFOHEADER);
    fileInfo.biWidth = slotSize;
    fileInfo.biHeight = slotSize;
    fileInfo.biPlanes = 1;
    fileInfo.biBitCount = 24;
    fileInfo.biCompression = BI_RGB;
	fileInfo.biSizeImage = slotSize * slotSize * 3;
    fileInfo.biXPelsPerMeter = 0;
    fileInfo.biYPelsPerMeter = 0;
    fileInfo.biClrImportant = 0;
    fileInfo.biClrUsed = 0;

	int tempX, tempY, j, i;

	std::string tempName, address;

	char buffer[MAX_PATH]; 
	GetModuleFileName( NULL, buffer, MAX_PATH ); 
	std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" ); 
	address = std::string( buffer ).substr( 0, pos); 

	address += "\\Resources\\TerrainData2";

	if(CreateDirectory(address.c_str(), NULL) == 0)
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)
			std::cout << "Failed to create the terraindata folder, already exists." << std::endl;

		if(GetLastError() == ERROR_PATH_NOT_FOUND)
		{
			std::cout << "Failed to create the terraindata folder, path not found." << std::endl;
			return false;
		}
	}

	address += "\\";

	j = i = 0;

	std::ofstream outFile;

	do{
		do{
		tempName = "terrainData" + Ogre::StringConverter::toString(j / slotSize) + Ogre::StringConverter::toString(i / slotSize) + ".txt";
		outFile.open(address + tempName, std::ios::trunc);

		if(outFile.fail())
		{
			std::cout << "Could not open/create the " << tempName << " text file." << std::endl;
		}

		editorLog << "Writing to file " << tempName << "." << std::endl;
			for(int n = 0; n < slotSize * slotSize; n++)
			{
				tempX = n % slotSize;
				tempY = n / slotSize;

				image[n].rgbtBlue = data.buffer[(i+tempX) + ((j + tempY) * data.size)];
				image[n].rgbtGreen = data.buffer[(i+tempX) + ((j + tempY) * data.size)];
				image[n].rgbtRed = data.buffer[(i+tempX) + ((j + tempY) * data.size)];

				float tempFloat = (float)data.buffer[(i+tempX) + ((j + tempY) * data.size)];

				outFile << "x : " << tempX << " y : " << tempY << " value : " << tempFloat << std::endl;
			}
		outFile.close();

		tempName = (std::string)name + Ogre::StringConverter::toString(j / slotSize) + Ogre::StringConverter::toString(i / slotSize) + ".bmp";

		editorLog << "Writing to file " << tempName << "." << std::endl;

		file = CreateFile((address+tempName).c_str() ,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

		if(file == INVALID_HANDLE_VALUE)
		{
			std::cout << "Failed to create a map file." << std::endl;
			return false;
		}else
		{
			std::cout << "File " << tempName << " created." << std::endl;
		}
		WriteFile(file,&fileHeader,sizeof(fileHeader),&write,NULL);
		WriteFile(file,&fileInfo,sizeof(fileInfo),&write,NULL);

		WriteFile(file, image, fileInfo.biSizeImage, &write, NULL);
 
		CloseHandle(file);

		file = NULL;

		i += slotSize;

		}while(i < data.size);

	i = 0;

	j += slotSize;

	}while(j < data.size);

	return true;
}