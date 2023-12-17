#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Enemy : public GameObject, public Box {
	graphics::Brush m_brush_enemy;
	float ve = 2.f;
	float m_pos_y;
	int direction = 1;
	
public:
	Enemy(float y) : m_pos_y(y) {
		if (rand() % 2 == 0) {
			direction *= -1;
		}
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
};