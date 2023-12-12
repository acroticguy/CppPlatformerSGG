#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Player: public GameObject, public Box {
	graphics::Brush m_brush_player;


public:
	Player(std::string name) : GameObject(name) {

	}
	void update(float dt) override;
	void init() override;
	void draw() override;
};