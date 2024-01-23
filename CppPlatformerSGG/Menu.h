#pragma once
#include "graphics.h"
#include <string>

class Menu {

protected:
	graphics::Brush m_brush_menu;
	
	int sel = 0;
	int curr_selected;

	class GameState* m_state;
	std::string title;

	const float cooldown = 0.25f;
	float curr_cd;

public:

	Menu();
	virtual void update(float dt) {};
	virtual void init() {};
	virtual void draw() {};
};