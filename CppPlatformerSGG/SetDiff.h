#pragma once
#include "graphics.h"
#include "GameState.h"
#include "Menu.h"

class SetDiff : public Menu {
private:
	static const int buttons = 4;
	static SetDiff* instance;

	std::string menu_selection[buttons] = { "EASY", "MEDIUM", "HARD", "IMPOSSIBLE" };

	graphics::Brush m_brush_sel;
	graphics::Brush m_brush_arrow;

public:

	SetDiff();
	static SetDiff* getInstance();
	void update(float dt) override;
	void init() override;
	void draw() override;
};