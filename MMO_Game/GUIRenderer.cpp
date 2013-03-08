#include "GUIRenderer.h"

GUIRenderer::GUIRenderer()
{
	_Player = NULL;
}

GUIRenderer::~GUIRenderer()
{
}

GUIRenderer* GUIRenderer::Instance()
{
  static GUIRenderer instance;

  return &instance;
}

void GUIRenderer::initialise(CEGUI::Window* sheet, Character* player)
{
	if(_Player != NULL && _Sheet != NULL)
		return;

	_Player = player;

	_Sheet = sheet;

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

	_NameBar = wmgr.createWindow("TaharezLook/Titlebar", "OgreGame/MainSheet/PlayerName");
	_NameBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.05f, 0.0f)));
	_NameBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.02f, 0.0f) ,CEGUI::UDim(0.02f, 0.0f)));
	_NameBar->setText(_Player->getName());
	sheet->addChildWindow(_NameBar);
	
	_HpBar = (CEGUI::ProgressBar*)wmgr.createWindow("TaharezLook/ProgressBar", "OgreGame/MainSheet/Hp");
	_HpBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.025f, 0.0f)));
	_HpBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.02f, 0.0f) ,CEGUI::UDim(0.07f, 0.0f)));
	_HpBar->setText("Health");
	_HpBar->setProgress(toPercentage(_Player->getCombat()->_Attributes.hp, _Player->getCombat()->_Attributes.maxHp));
	sheet->addChildWindow(_HpBar);

	_MpBar = (CEGUI::ProgressBar*)wmgr.createWindow("TaharezLook/ProgressBar", "OgreGame/MainSheet/Mp");
	_MpBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.025f, 0.0f)));
	_MpBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.02f, 0.0f) ,CEGUI::UDim(0.095f, 0.0f)));
	_MpBar->setText("Magic");
	_MpBar->setProgress(toPercentage(_Player->getCombat()->_Attributes.mp, _Player->getCombat()->_Attributes.maxMp));
	sheet->addChildWindow(_MpBar);

	_TargetNameBar = wmgr.createWindow("TaharezLook/Titlebar", "OgreGame/MainSheet/TargetName");
	_TargetNameBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.05f, 0.0f)));
	_TargetNameBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.79f, 0.0f) ,CEGUI::UDim(0.02f, 0.0f)));
	sheet->addChildWindow(_TargetNameBar);
	_TargetNameBar->setVisible(false);

	_TargetHpBar = (CEGUI::ProgressBar*)wmgr.createWindow("TaharezLook/ProgressBar", "OgreGame/MainSheet/TargetHp");
	_TargetHpBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.025f, 0.0f)));
	_TargetHpBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.79f, 0.0f) ,CEGUI::UDim(0.07f, 0.0f)));
	_TargetHpBar->setText("Health");
	sheet->addChildWindow(_TargetHpBar);
	_TargetHpBar->setVisible(false);

	_TargetMpBar = (CEGUI::ProgressBar*)wmgr.createWindow("TaharezLook/ProgressBar", "OgreGame/MainSheet/TargetMp");
	_TargetMpBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.025f, 0.0f)));
	_TargetMpBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.79f, 0.0f) ,CEGUI::UDim(0.095f, 0.0f)));
	_TargetMpBar->setText("Magic");
	sheet->addChildWindow(_TargetMpBar);
	_TargetMpBar->setVisible(false);

	_SkillSlot1 = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/SkillSlot1");
	_SkillSlot1->setSize(CEGUI::UVector2(CEGUI::UDim(0.1f, 0.0f), CEGUI::UDim(0.05f, 0.0f)));
	_SkillSlot1->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f, 0.0f) ,CEGUI::UDim(0.9f, 0.0f)));
	_SkillSlot1->setText("Attack");
	_SkillSlot1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIRenderer::SkillSlot1, this));
	sheet->addChildWindow(_SkillSlot1);

	_SkillSlot2 = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/SkillSlot2");
	_SkillSlot2->setSize(CEGUI::UVector2(CEGUI::UDim(0.1f, 0.0f), CEGUI::UDim(0.05f, 0.0f)));
	_SkillSlot2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45f, 0.0f) ,CEGUI::UDim(0.9f, 0.0f)));
	_SkillSlot2->setText("Pain");
	_SkillSlot2->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIRenderer::SkillSlot2, this));
	sheet->addChildWindow(_SkillSlot2);

	_SkillSlot3 = wmgr.createWindow("TaharezLook/Button", "OgreGame/MainSheet/SkillSlot3");
	_SkillSlot3->setSize(CEGUI::UVector2(CEGUI::UDim(0.1f, 0.0f), CEGUI::UDim(0.05f, 0.0f)));
	_SkillSlot3->setPosition(CEGUI::UVector2(CEGUI::UDim(0.55f, 0.0f) ,CEGUI::UDim(0.9f, 0.0f)));
	_SkillSlot3->setText("Heal");
	_SkillSlot3->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIRenderer::SkillSlot3, this));
	sheet->addChildWindow(_SkillSlot3);

	_CastBar = (CEGUI::ProgressBar*)wmgr.createWindow("TaharezLook/ProgressBar", "OgreGame/MainSheet/CastBar");
	_CastBar->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.025f, 0.0f)));
	_CastBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.4f, 0.0f) ,CEGUI::UDim(0.85f, 0.0f)));
	_CastBar->setText("Casting");
	_CastBar->setProgress(0.0f);
	sheet->addChildWindow(_CastBar);
	_CastBar->setVisible(false);

	/*BackPack = (CEGUI::FrameWindow*)wmgr.createWindow("TaharezLook/FrameWindow", "OgreGame/MainSheet/BackPack");
	BackPack->setSize(CEGUI::UVector2(CEGUI::UDim(0.3f, 0.0f), CEGUI::UDim(0.3f, 0.0f)));
	BackPack->setPosition(CEGUI::UVector2(CEGUI::UDim(0.7f, 0.0f) ,CEGUI::UDim(0.7f, 0.0f)));
	BackPack->setText("BackPack");
	BackPack->setRollupEnabled(false);
	sheet->addChildWindow(BackPack);*/

	//StaticImage = static_cast<CEGUI::Window*>(wmgr.createWindow("TaharezLook/StaticImage", "ChackPack/StaticImage"));
	//StaticImage->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.5f, 0)));
	//StaticImage->setSize(CEGUI::UVector2(CEGUI::UDim(0.1f, 0), CEGUI::UDim(0.1f, 0)));
	//StaticImage->setProperty("Image", "set:SkillsImageset image:Slot");
	//StaticImage->setProperty("FrameEnabled", "False");
	//StaticImage->setProperty("BackgroundEnabled", "False");
	//BackPack->addChildWindow(StaticImage);

	
	//BackPack->moveToFront();
}

void GUIRenderer::showTarget(bool show)
{
	if(show && _Player->_Target)
	{
		_TargetNameBar->setText(_Player->_Target->getName());
		_TargetHpBar->setProgress(toPercentage(_Player->_Target->getCombat()->_Attributes.hp, _Player->_Target->getCombat()->_Attributes.maxHp));
		_TargetMpBar->setProgress(toPercentage(_Player->_Target->getCombat()->_Attributes.mp, _Player->_Target->getCombat()->_Attributes.maxMp));
	
		_TargetNameBar->setVisible(true);
		_TargetHpBar->setVisible(true);
		_TargetMpBar->setVisible(true);
	}else
	{
		_TargetNameBar->setVisible(false);
		_TargetHpBar->setVisible(false);
		_TargetMpBar->setVisible(false);
	}
}

bool GUIRenderer::SkillSlot1(const CEGUI::EventArgs& arg)
{
	_Player->getCombat()->castEffect("Attack");
	return true;
}

bool GUIRenderer::SkillSlot2(const CEGUI::EventArgs& arg)
{
	_Player->getCombat()->castEffect("Pain");
	return true;
}

bool GUIRenderer::SkillSlot3(const CEGUI::EventArgs& arg)
{
	_Player->getCombat()->castEffect("Heal");
	return true;
}

float GUIRenderer::toPercentage(float value, float max)
{
	return ((value * 1) / max);
}

bool GUIRenderer::addSkill(int slot)
{
	return true;
}

bool GUIRenderer::removeSkill(int slot)
{
	return true;
}

void GUIRenderer::displayWindow(CEGUI::Window* window)
{
	_Sheet->addChildWindow(window);
	_Windows.push_back(window);
}

bool GUIRenderer::isWindowDisplayed(CEGUI::String name)
{
	for(_wi = _Windows.begin(); _wi != _Windows.end(); _wi++)
	{
		if((*_wi)->getName() == name)
		{
			return true;
		}
	}
	return false;
}

void GUIRenderer::update(float tslf)
{
	_HpBar->setProgress(toPercentage(_Player->getCombat()->_Attributes.hp, _Player->getCombat()->_Attributes.maxHp));
	_MpBar->setProgress(toPercentage(_Player->getCombat()->_Attributes.mp, _Player->getCombat()->_Attributes.maxMp));

	if(_TargetHpBar->isVisible())
	{
		_TargetHpBar->setProgress(toPercentage(_Player->_Target->getCombat()->_Attributes.hp, _Player->_Target->getCombat()->_Attributes.maxHp));
		_TargetMpBar->setProgress(toPercentage(_Player->_Target->getCombat()->_Attributes.mp, _Player->_Target->getCombat()->_Attributes.maxMp));
	}

	if(_Player->getCombat()->getCast())
	{
		_CastBar->setVisible(true);
		_CastBar->setProgress(toPercentage(_Player->getCombat()->getCastProgress(), _Player->getCombat()->getCast()->getSkill()->getCast()));
	}else
	{
		_CastBar->setVisible(false);
	}
}
