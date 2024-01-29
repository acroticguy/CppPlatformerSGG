#pragma once
#include "graphics.h"
#include "GameState.h"
#include "Menu.h"

class GameOver : public Menu {
private:
	static const int buttons = 2;
	static GameOver* instance;

	std::string menu_selection[buttons] = { "RETRY", "MAIN MENU" };

	graphics::Brush m_brush_sel;
	graphics::Brush m_brush_arrow;

public:

	GameOver();
	static GameOver* getInstance();
	void update(float dt) override;
	void init() override;
	void draw() override;
};