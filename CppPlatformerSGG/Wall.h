#pragma once
#include "box.h"
#include "GameObject.h"
#include <list>

class Wall : public GameObject, public Box {
	graphics::Brush m_brush_wall;
	float starting_x = 0.f;
	float starting_y = 0.f;
	float ending_x = 0.f;
	float ending_y = 0.f;
	float side_col;

	std::vector<Box*> list;

public:
	Wall(std::string name) : GameObject(name) {

	}
	Wall(float s_x, float e_x, float s_y, float e_y, std::string name) {
		starting_x = s_x;
		ending_x = e_x;
		starting_y = s_y;
		ending_y = e_y;
		m_name = name;
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
};