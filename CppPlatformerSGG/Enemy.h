#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Enemy : public GameObject, public Box {
	graphics::Brush m_brush_player;


public:
	Enemy(std::string name) : GameObject(name) {

	}
	void update(float dt) override;
	void init() override;
	void draw() override;
};