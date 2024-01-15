#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"

class Player: public GameObject, public Box {
	graphics::Brush m_brush_player;
	const float v = 10.f;
	const float terminal_v = 20.f;
	const int hit_frame_sum = 14;//Van

	int animation_cycle = 11;
	float direction = 1.f;

	float gravity = 1.f;
	float vertical_v = 0.f;
	
	float hit_frame = 0.f;//Van
	float health = 200;//Van
	int lives = 3;//Van

public:
	Player(std::string name) : GameObject(name) {

	}

	float initHealth = 200;//Van
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