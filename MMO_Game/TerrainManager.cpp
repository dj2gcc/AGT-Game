#include "TerrainManager.h"

TerrainManager* TerrainManager::_Instance = NULL;

TerrainManager::TerrainManager()
{
}

TerrainManager::~TerrainManager()
{
}

TerrainManager* TerrainManager::Instance()
{
}

void TerrainManager::terrainInit(Ogre::String file, OgreManager* o)
{
	_OgreManager = o;
	_TerrainGlobalOptions = new Ogre::TerrainGlobalOptions();

	_TerrainGroup = new Ogre::TerrainGroup(_OgreManager->getSceneManager(), Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
	_TerrainGroup->setFilenameConvention(Ogre::String("GameTerrain"), Ogre::String("dat"));
	_TerrainGroup->setOrigin(Ogre::Vector3::ZERO);

	//Config Terrain start
	_TerrainGlobalOptions->setMaxPixelError(8);
	_TerrainGlobalOptions->setCompositeMapDistance(3000);
	//lTerrainGlobalOptions->setLightMapDirection(light->getDerivedDirection());
//	lTerrainGlobalOptions->setCompositeMapAmbient(lScene->getAmbientLight());
	//lTerrainGlobalOptions->setCompositeMapDiffuse(light->getDiffuseColour());

	Ogre::Terrain::ImportData& defaultimp = _TerrainGroup->getDefaultImportSettings();
	defaultimp.terrainSize = 513;
	defaultimp.worldSize = 12000.0f;
	defaultimp.inputScale = 600;
	//defaultimp.inputBias = 100;
	defaultimp.minBatchSize = 33;
	defaultimp.maxBatchSize = 65;

	defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 100;
	defaultimp.layerList[0].textureNames.push_back("dirt_gravyrocky_diffusespecular.dds");
	defaultimp.layerList[0].textureNames.push_back("dirt_gravyrocky_normalheight.dds");
	defaultimp.layerList[1].worldSize = 30;
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
	defaultimp.layerList[2].worldSize = 200;
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
	//Config Terrain end

	bool lTerrainsImported = false;
	 for (long x = 0; x <= 0; ++x)
	 {
        for (long y = 0; y <= 0; ++y)
		{
			//Define terrain function
			 Ogre::String filename = _TerrainGroup->generateFilename(x, y);
			if (Ogre::ResourceGroupManager::getSingleton().resourceExists(lTerrainGroup->getResourceGroup(), filename))
			{
				lTerrainGroup->defineTerrain(x, y);
			}
			else
			{
				Ogre::Image img;
				//Get terrain image
				img.load(file, Ogre::String("GameResources"));
					if (x % 2 != 0)
						img.flipAroundY();
					if (y % 2 != 0)
						img.flipAroundX();
				//Get terrain image end
				lTerrainGroup->defineTerrain(x, y, &img);
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
}

Ogre::ManualObject* TerrainManager::createTerrainDecal(Ogre::String& name, Ogre::String& material, Ogre::String& resourceGroup = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME)
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