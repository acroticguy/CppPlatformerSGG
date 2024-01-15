#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Enemy : public GameObject, public Box {
	graphics::Brush m_brush_enemy;
	float ve = 2.f;
	float m_pos_y;
	float exit_point;
	int direction = 1;

	float kill_frame = 0.f;//Van
	const int kill_frame_sum = 10;//Van
	
public:
	Enemy(float y) : m_pos_y(y) {
		if (rand() % 2 == 0) {
			direction *= -1;
		}
	}
	Enemy(float x, float y, float w, float h) : Box(x, y, w, h) {
		if (rand() % 2 == 0) {
			direction *= -1;
		}
	}
	bool is_killed = false;//Van

	void setKilled(bool status);
	bool getActive();
	float getM_pos_y();

	void update(float dt) override;
	void init() override;
	void draw() override;

	~Enemy() ;
};