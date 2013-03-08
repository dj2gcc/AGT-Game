#include "Inventory.h"
#include "GUIRenderer.h"
#include "Ogre.h"
#include <CEGUI.h>

Inventory::Inventory(int x, int y, std::string name)
{
	_ID = IDManager->newInventoryID();

	_Name = name;

	_Contents = new Equipment*[x * y];

	for(int i = 0; i < (x*y); i++)
	{
		_Contents[i] = NULL;
	}

	_Width = x;
	_Height = y;
}

Inventory::~Inventory()
{
	for(int i = 0; i < (_Width * _Height); i++)
	{
		delete _Contents[i];
	}

	delete[] _Contents;
}

bool Inventory::checkSpace(Equipment* item, int x, int y)
{
	if(x > _Width || x < 0 || y > _Height || y < 0)
	{
		return false;
	}

	for(int i = x; i < x + item->getWidth(); i++)
	{
		for(int j = y; j < y + item->getHeight(); j++)
		{
			if(i >= _Width || j >= _Height || _Contents[((j-1) * _Width) + i] != NULL)
			{
				return false;
			}
		}
	}

	return true;
}

bool Inventory::addItemAtSquare(Equipment* item, int x, int y)
{
	for(int i = x; i < x + item->getWidth(); i++)
	{
		for(int j = y; j < y + item->getHeight(); j++)
		{
			_Contents[((j-1) * _Width) + i] = item;
		}
	}

	return true;
}

void Inventory::showContent()
{
	CEGUI::String name = CEGUI::String(Ogre::StringConverter::toString(_ID) + "Inventory");

	if(GUI->isWindowDisplayed(name))
		return;

	CEGUI::FrameWindow* window;

	window = (CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow", name);
	window->setSize(CEGUI::UVector2(CEGUI::UDim(_Width * 0.05, 0), CEGUI::UDim(_Height * 0.05 + 0.05, 0)));
	window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0.0f) ,CEGUI::UDim(0.3f, 0.0f)));
	window->setText(_Name);
	window->setRollupEnabled(false);

	CEGUI::Window* slot;

	float slotSize = 0.95 / (float)_Width;

	float gap = (0.95 / (float)_Width) / 10;

	for(int i = 0; i < _Width; i++)
	{
		for(int j = 0; j < _Height; j++)
		{
			slot = static_cast<CEGUI::Window*>(CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", name + Ogre::StringConverter::toString(i) + Ogre::StringConverter::toString(j) + "Slot"));
			slot->setPosition(CEGUI::UVector2(CEGUI::UDim(i * slotSize + gap, 0), CEGUI::UDim(j * slotSize + gap, 0)));
			slot->setSize(CEGUI::UVector2(CEGUI::UDim(slotSize, 0), CEGUI::UDim(slotSize, 0.)));
			slot->setProperty("Image", "set:SkillsImageset image:Slot");
			slot->setProperty("FrameEnabled", "False");
			slot->setProperty("BackgroundEnabled", "False");
			window->addChildWindow(slot);
		}
	}

	GUI->displayWindow(window);
}