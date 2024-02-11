#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Player: public GameObject, public Box {
	const int animation_cycle = 11;

	graphics::Brush m_brush_player;
	const float v = 10.f;
	const float terminal_v = 20.f;
	const int hit_frame_sum = 14;
	
	float direction = 1.f;

	float gravity = 1.f;
	float vertical_v = 0.f;
	
	float hit_frame = 0.f;
	float health = 200;
	int lives = 3;

	float curr_cd;

public:
	Player(std::string name) : GameObject(name) {
		hitbox = new Box(m_pos_x, m_pos_y, 1, 1);
	}

	int enemies_killed = 0;
	int score = 0;
	float initHealth = 200;
	float jump_v = 15.f;
	bool is_hit = false;
	bool is_dead = false;
	float getHealth();
	void setHealth(float h);

	void update(float dt) override;
	void init() override;
	void draw() override;
	void setVerticalV(float new_v);
	float getDirection() { return direction; };
};