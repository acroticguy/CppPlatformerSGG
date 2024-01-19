#pragma once
#include "graphics.h"

class Menu {
	graphics::Brush m_brush_menu;

public:
	std::string title;

	Menu();
	virtual void update(float dt) {};
	virtual void init() {};
	virtual void draw() {};
};