#pragma once
#include "graphics.h"
#include "GameState.h"
#include "Menu.h"

class CharSelect : public Menu {
private:
	static const int buttons = 4;
	static CharSelect* instance;
	int sel = 0;
	int curr_selected;
	std::string menu_selection[buttons] = { "Mask Dude", "Ninja Frog", "Pink Guy", "Virtual Man" };

	graphics::Brush m_brush_sel[buttons];

	float frame_count = 0.f;
	const int animation_cycle = 11;

public:

	CharSelect();
	static CharSelect* getInstance();
	void update(float dt) override;
	void init() override;
	void draw() override;
	void animate(int p);
};