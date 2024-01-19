#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Player: public GameObject, public Box {
	const int animation_cycle = 11;

	graphics::Brush m_brush_player;
	const float v = 10.f;
	const float terminal_v = 20.f;
	const int hit_frame_sum = 14;//Van
	
	float direction = 1.f;

	float gravity = 1.f;
	float vertical_v = 0.f;
	
	float hit_frame = 0.f;//Van
	float health = 200;//Van
	int lives = 3;//Van

public:
	Player(std::string name) : GameObject(name) {
		hitbox = new Box(m_pos_x, m_pos_y, 1, 1);
	}

	int enemies_killed = 0;//Van
	int score = 0;
	float initHealth = 200;//Van
	float jump_v = 15.f;
	bool is_hit = false;//Van
	float getHealth();//Van
	void setHealth(float h);//Van
	void updateHealth(float h);//Van
	int getLives();//Van
	void setLives(int l);//Van

	void update(float dt) override;
	void init() override;
	void draw() override;
	void setVerticalV(float new_v);
};