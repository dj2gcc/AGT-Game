#pragma once

#include <CEGUI.h>
#include <CEGUISystem.h>

#include "Interface.h"
#include "Character.h"

class GUIRenderer
{
private:

	Character* _Player;

	CEGUI::Window* _Sheet;

	CEGUI::Window* _NameBar;
	CEGUI::ProgressBar* _HpBar;
	CEGUI::ProgressBar* _MpBar;

	CEGUI::Window* _TargetNameBar;
	CEGUI::ProgressBar* _TargetHpBar;
	CEGUI::ProgressBar* _TargetMpBar;

	CEGUI::Window* _SkillSlot1;
	CEGUI::Window* _SkillSlot2;
	CEGUI::Window* _SkillSlot3;

	CEGUI::ProgressBar* _CastBar;

	Interface* _Listener;
	
	std::vector<CEGUI::Window*> _Windows;
	std::vector<CEGUI::Window*>::iterator _wi;

	GUIRenderer();
	~GUIRenderer();

public:
	
	static GUIRenderer* Instance();

	void initialise(CEGUI::Window* sheet, Character* player);

	bool SkillSlot1(const CEGUI::EventArgs& arg);
	bool SkillSlot2(const CEGUI::EventArgs& arg);
	bool SkillSlot3(const CEGUI::EventArgs& arg);

	float toPercentage(float value, float max);

	bool addSkill(int slot);
	bool removeSkill(int slot);

	void showTarget(bool show);

	void displayWindow(CEGUI::Window* window);
	bool isWindowDisplayed(CEGUI::String name);

	void update(float tslf);
};

#define GUI GUIRenderer::Instance()