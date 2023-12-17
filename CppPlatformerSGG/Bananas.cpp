#include "Bananas.h"

void Bananas::update(float dt)
{
	PowerUp::update(dt);
	int current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
	m_brush_power.texture = m_state->getAssetPath(m_name + "\\output_") + std::to_string(current_frame) + ".png";
}

void Bananas::init()
{
	frame_count = 0;
	m_brush_power.fill_opacity = 1.f;
	m_brush_power.outline_opacity = 0.f;
	m_brush_power.texture = m_state->getAssetPath(m_name + "\\output_1.png");
}

void Bananas::draw()
{
	PowerUp::draw();
}

void Bananas::activation()
{
}
