#pragma once
#include "box.h"
#include "GameObject.h"

class Wall : public GameObject, public Box {
	graphics::Brush m_brush_wall;


public:
	Wall(std::string name) : GameObject(name) {

	}
	Wall(float x, float y, float w, float h) : Box(x, y, w, h) {

	}
	void update(float dt) override;
	void init() override;
	void draw() override;
};