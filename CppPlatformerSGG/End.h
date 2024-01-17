#pragma once
#include "graphics.h"
#include "GameObject.h"
#include "box.h"

class End: public GameObject, public Box{
private:
	graphics::Brush m_brush_end;
	float frame_count = 0;
public:
	End(float x, float y, float w, float h) : Box(x, y, w, h) {
		hitbox = new Box(x, y, 0.6, 1);
	}
	bool is_collected = false;
	void update(float dt) override;
	void init() override;
	void draw() override;
};