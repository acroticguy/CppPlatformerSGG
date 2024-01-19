#pragma once
#include "Event.h"
#include "box.h"
#include "graphics.h"

class PowerUp : public Event, public Box {
private:
	std::string m_name = "";
	const int collected_frame_sum = 6;
protected:
	const int animation_cycle = 17;

	graphics::Brush m_brush_power;
	graphics::Brush m_brush_score_p;
	
	float frame_count= 0.f;
	float collected_frame = 0.f;

	float score_pos_offset = 0.f;

	int value;
	int health_given;

public:
	PowerUp(float x, float y, float w, float h) : Box(x, y, w, h) {
		hitbox = new Box(x, y, 0.5, 0.5);
	}
	bool is_collected = false;
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation(float dt) override;
	virtual std::string getName() const = 0;
	virtual int getHeal() const = 0;
	virtual int getScore() const = 0;
};