#pragma once
#include "graphics.h"
#include "GameState.h"
#include "Menu.h"


class Congratulations : public Menu {
private:
	static const int buttons = 2;
	static Congratulations* instance;

	std::string menu_selection[buttons] = { "PLAY AGAIN", "MAIN MENU" };

	graphics::Brush m_brush_sel;
	graphics::Brush m_brush_arrow;

public:

	Congratulations();
	static Congratulations* getInstance();
	void update(float dt) override;
	void init() override;
	void draw() override;
};