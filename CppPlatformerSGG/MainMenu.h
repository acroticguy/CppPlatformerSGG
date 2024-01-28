#pragma once
#include "graphics.h"
#include "GameState.h"
#include "Menu.h"

class MainMenu: public Menu {
private:
	static const int buttons = 4;
	static MainMenu* instance;
	
	std::string menu_selection[buttons] = { "PLAY", "SELECT CHARACTER", "DIFFICULTY", "QUIT"};

	graphics::Brush m_brush_sel;
	graphics::Brush m_brush_arrow;

public:

	MainMenu();
	static MainMenu* getInstance();
	void update(float dt) override;
	void init() override;
	void draw() override;
};