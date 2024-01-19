#pragma once
#include "graphics.h"
#include "Menu.h"

class MainMenu: public Menu {
	graphics::Brush m_brush_menu;

	static MainMenu* instance;
public:

	MainMenu();
	static MainMenu* getInstance();
	void update(float dt) override;
	void init() override;
	void draw() override;
};