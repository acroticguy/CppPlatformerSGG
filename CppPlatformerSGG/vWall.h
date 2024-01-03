#pragma once
#include "box.h"
#include "GameObject.h"

class vWall : public GameObject, public Box {
	graphics::Brush m_brush_vWall;


public:
	vWall(std::string name) : GameObject(name) {

	}
	vWall(float x, float y, float w, float h) : Box(x, y, w, h) {

	}
	void update(float dt) override;
	void init() override;
	void draw() override;
};