#pragma once
#include "Event.h"
#include "box.h"
#include "graphics.h"
class PowerUp : public Event, public Box {
protected:
	graphics::Brush m_brush_power;

	int animation_cycle = 17;
	float frame_count= 0.f;
	int value;
	std::string m_name;

public:
	PowerUp(float x, float y, float w, float h) : Box(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation() override;
};