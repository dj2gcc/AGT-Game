#include "TerrainManager.h"

TerrainManager::TerrainManager()
{
}

TerrainManager::~TerrainManager()
{
}

TerrainManager* TerrainManager::Instance()
{
	static TerrainManager _Instance;

	return &_Instance;
}

void TerrainManager::initialiseResources()
{
	_OgreManager->addResourceGroup(Ogre::String("TerrainResources"), false);

	char buffer[MAX_PATH]; 
	GetModuleFileName( NULL, buffer, MAX_PATH ); 
	std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" ); 
	std::string s = std::string( buffer ).substr( 0, pos); 
	
	_OgreManager->addResourceLocation(Ogre::String(s + "\\Resources\\TerrainData\\"), Ogre::String("FileSystem"), Ogre::String("TerrainResources"), false);
	_OgreManager->getRgm()->initialiseResourceGroup(Ogre::String("TerrainResources"));
}

void TerrainManager::createLight()
{
	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
	lightdir.normalise();

	_Light = _OgreManager->getSceneManager()->createLight("GameLight");
	_Light->setType(Ogre::Light::LT_DIRECTIONAL);
	_Light->setDirection(lightdir);
	_Light->setDiffuseColour(Ogre::ColourValue::White);
	_Light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

	_OgreManager->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
}

void TerrainManager::setGlobalOptions()
{
	_TerrainGlobalOptions = OGRE_NEW Ogre::TerrainGlobalOptions();

	_TerrainGlobalOptions->setMaxPixelError(8);
	_TerrainGlobalOptions->setCompositeMapDistance(3000);

	_TerrainGlobalOptions->setLightMapDirection(_Light->getDerivedDirection());
	_TerrainGlobalOptions->setCompositeMapAmbient(_OgreManager->getSceneManager()->getAmbientLight());
	_TerrainGlobalOptions->setCompositeMapDiffuse(_Light->getDiffuseColour());
}

void TerrainManager::setDefaultImportSettings()
{
	Ogre::Terrain::ImportData& defaultimp = _TerrainGroup->getDefaultImportSettings();
	defaultimp.terrainSize = 512;
	defaultimp.worldSize = 12000.0f;
	defaultimp.inputScale = 600;
	defaultimp.minBatchSize = 33;
	defaultimp.maxBatchSize = 65;

	defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 100;
	defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
	defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
	defaultimp.layerList[1].worldSize = 30;
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
	defaultimp.layerList[2].worldSize = 200;
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
}

void TerrainManager::terrainInit(Ogre::String file, OgreManager* o)
{
	_OgreManager = o;

	initialiseResources();

	createLight();

	setGlobalOptions();

	_TerrainGroup = OGRE_NEW Ogre::TerrainGroup(_OgreManager->getSceneManager(), Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
	_TerrainGroup->setFilenameConvention(Ogre::String("GameTerrain"), Ogre::String("dat"));
	_TerrainGroup->setOrigin(Ogre::Vector3::ZERO);

	setDefaultImportSettings();

	bool lTerrainsImported = false;
	 for (long x = 0; x <= 0; ++x)
	 {
        for (long y = 0; y <= 0; ++y)
		{
			//Define terrain function
			 Ogre::String filename = _TerrainGroup->generateFilename(x, y);
			if (Ogre::ResourceGroupManager::getSingleton().resourceExists(_TerrainGroup->getResourceGroup(), filename))
			{
				_TerrainGroup->defineTerrain(x, y);
			}
			else
			{
				Ogre::Image img;
				//Get terrain image
				Ogre::String tempFile = Ogre::StringConverter::toString(x * 10 + y);
				tempFile.append(".bmp");
				img.load("00.bmp", Ogre::String("TerrainResources"));
					if (x % 2 != 0)
						img.flipAroundY();
					if (y % 2 != 0)
						img.flipAroundX();
				//Get terrain image end
				_TerrainGroup->defineTerrain(x, y, &img);
				lTerrainsImported = true;
			}
			//Define terrain function end
		}
	}
	
	_TerrainGroup->loadAllTerrains(true);

	if (lTerrainsImported)
    {
        Ogre::TerrainGroup::TerrainIterator ti = _TerrainGroup->getTerrainIterator();
        while(ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;
            //Init blend maps function start
			Ogre::TerrainLayerBlendMap* blendMap0 = t->getLayerBlendMap(1);
			Ogre::TerrainLayerBlendMap* blendMap1 = t->getLayerBlendMap(2);
			Ogre::Real minHeight0 = -10;
			Ogre::Real fadeDist0 = 0;//40;
			Ogre::Real minHeight1 = -10;
			Ogre::Real fadeDist1 = 0;//15;
			float* pBlend0 = blendMap0->getBlendPointer();
			float* pBlend1 = blendMap1->getBlendPointer();
			for (Ogre::uint16 y = 0; y < t->getLayerBlendMapSize(); ++y)
			{
				for (Ogre::uint16 x = 0; x < t->getLayerBlendMapSize(); ++x)
				{
					Ogre::Real tx, ty;
 
					blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
					Ogre::Real height = t->getHeightAtTerrainPosition(tx, ty);
					Ogre::Real val = (height - minHeight0) / fadeDist0;
					val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
					*pBlend0++ = val;
 
					val = (height - minHeight1) / fadeDist1;
					val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
					*pBlend1++ = val;
				}
			}
			blendMap0->dirty();
			blendMap1->dirty();
			blendMap0->update();
			blendMap1->update();
			//Init blend maps end
        }
    }

	_TerrainGroup->freeTemporaryResources();

	_OgreManager->getSceneManager()->setSkyBox(true, "Examples/EarlyMorningSkyBox", 5000, true, Ogre::Quaternion::IDENTITY, "GameResources");
}

//void TerrainManager::setupPaging()
//{
//	 // Paging setup
//   mPageManager = OGRE_NEW PageManager();
//   // Since we're not loading any pages from .page files, we need a way just 
//   // to say we've loaded them without them actually being loaded
//   mPageManager->setPageProvider(&mDummyPageProvider);
//   mPageManager->addCamera(const_cast<Camera *>(cam));
//   mTerrainPaging = OGRE_NEW TerrainPaging(mPageManager);
//   PagedWorld* world = mPageManager->createWorld();
//   TerrainPagedWorldSection* worldSection = mTerrainPaging->createWorldSection(world, _TerrainGroup, 2000, 3000, TERRAIN_PAGE_MIN_X, TERRAIN_PAGE_MIN_Y, TERRAIN_PAGE_MAX_X, TERRAIN_PAGE_MAX_Y);
//}

void TerrainManager::clearTerrainManager()
{
	_TerrainGroup->removeAllTerrains();
	OgreManager::Instance()->getSceneManager()->destroyLight("GameLight");
	OgreManager::Instance()->getSceneManager()->setSkyBox(false, "");
	OGRE_DELETE _TerrainGroup;
	OGRE_DELETE _TerrainGlobalOptions;

	_OgreManager->removeResourceGroup("TerrainResources");
}

Ogre::ManualObject* TerrainManager::createTerrainDecal(Ogre::String& name, Ogre::String& material, Ogre::String& resourceGroup)
{
	if(!_OgreManager)
		return NULL;

	Ogre::ManualObject* meshDecal = new Ogre::ManualObject(name);

	_OgreManager->getSceneManager()->getRootSceneNode()->attachObject(meshDecal);
	
	int x_size = 4;  // number of polygons
	int z_size = 4;
 
	meshDecal->begin(material, Ogre::RenderOperation::OT_TRIANGLE_LIST, resourceGroup);
	for (int i=0; i<=x_size; i++)
	{
		for (int j=0; j<=z_size; j++)
		{
			meshDecal->position(Ogre::Vector3(i, 0, j));
			meshDecal->textureCoord((float)i / (float)x_size, (float)j / (float)z_size);
		}
	}
 
	for (int i=0; i<x_size; i++)
	{
		for (int j=0; j<z_size; j++)
		{
			meshDecal->quad( i * (x_size+1) + j,
							 i * (x_size+1) + j + 1,
							(i + 1) * (x_size+1) + j + 1,
							(i + 1) * (x_size+1) + j);
		}
	}
	meshDecal->end();

	return meshDecal;
}

void TerrainManager::setTerrainDecal(Ogre::ManualObject* decal, Ogre::Real x, Ogre::Real z, Ogre::Real rad)
{
	Ogre::Real x1 = x - rad;
	Ogre::Real z1 = z - rad;
 
	int x_size = 4;  // number of polygons
	int z_size = 4;
 
	Ogre::Real x_step = rad * 2/ x_size;
	Ogre::Real z_step = rad * 2/ z_size;
 
	decal->beginUpdate(0);
	
	// redefine vertices
	for (int i=0; i<=x_size; i++)
	{
		for (int j=0; j<=z_size; j++)
		{
			decal->position(Ogre::Vector3(x1, getTerrainHeight(x1, z1) + 1, z1));
			decal->textureCoord((float)i / (float)x_size, (float)j / (float)z_size);
			z1 += z_step;
		}
		x1 += x_step;
		z1 = z - rad;
	}
   
	// redefine quads
   
	for (int i=0; i<x_size; i++)
   	{
   		for (int j=0; j<z_size; j++)
   		{
   			decal->quad( i * (x_size+1) + j,
   						 i * (x_size+1) + j + 1,
   						(i + 1) * (x_size+1) + j + 1,
						(i + 1) * (x_size+1) + j);
		}
	}

	decal->end();
}

Ogre::Real TerrainManager::getTerrainHeight(Ogre::Real x, Ogre::Real z)
{
	if(_TerrainGroup)
	{
		Ogre::Ray verticalRay( Ogre::Vector3(x, 5000, z), Ogre::Vector3::NEGATIVE_UNIT_Y );
		
		Ogre::TerrainGroup::RayResult rayResult = _TerrainGroup->rayIntersects(verticalRay);
		
		if (rayResult.hit)
		{
			Ogre::Vector3 intersection = rayResult.position;
			return intersection.y;
		}else
		{
			return 0;
		}  
	}
}

/*
http://www.ogre3d.org/forums/viewtopic.php?f=2&t=60456

http://www.ogre3d.org/docs/api/html/classOgre_1_1PageManager.html

http://www.ogre3d.org/forums/viewtopic.php?f=1&t=73377

http://www.ogre3d.org/forums/viewtopic.php?f=2&t=65670

https://bitbucket.org/jacmoe/ogitor/src/d8e782345e93bb86d4126102e3aab6eb0b8e6195/Ogitor?at=default
*/