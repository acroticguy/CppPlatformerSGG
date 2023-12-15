#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Player: public GameObject, public Box {
	graphics::Brush m_brush_player;
	const float v = 10.f;
	const float terminal_v = 20.f;

	float gravity = 1.f;
	float vertical_v = 0.f;
	

public:
	Player(std::string name) : GameObject(name) {

	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void setVerticalV(float new_v);
};