#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Enemy : public GameObject, public Box {
	graphics::Brush m_brush_enemy;
	graphics::Brush m_brush_score_p;
	float ve = 2.f;
	float exit_point;
	int direction = 1;
	const int value = 100;

	float score_pos_offset = 0.f;

	int animation_cycle = 7;

	float kill_frame = 0.f;//Van
	const int kill_frame_sum = 10;//Van
	
public:
	Enemy(float x, float y, float w, float h, std::string name) : Box(x, y, w, h), GameObject(name) {
		hitbox = new Box(x, y, w, h);
		if (rand() % 2 == 0) {
			direction *= -1;
		}
	}
	bool is_killed = false;//Van

	void setKilled(bool status);
	bool getActive();

	void update(float dt) override;
	void init() override;
	void draw() override;

	~Enemy() ;
};