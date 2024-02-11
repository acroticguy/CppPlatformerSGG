#pragma once
#include "Event.h"
#include "box.h"
#include "graphics.h"

class Weapon : public Event, public Box {
private:
	
	const int fire_frame_sum = 1;
protected:
	const int animation_cycle = 1;
	const int speed = 12;

	graphics::Brush m_brush_weapon;
	

	float frame_count = 0.f;
	float fire_frame = 0.f;

	float start_point;
	int direction = 1;
	
public:
	Weapon(float x, float y, float w, float h) : Box(x, y, w, h) {
		hitbox = new Box(x, y, 0.2, 0.2);
	}
	Weapon() {}

	bool is_firing = false;
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation(float dt) override;
	//virtual std::string getName() const = 0;
};