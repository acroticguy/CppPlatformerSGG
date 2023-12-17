#include "Strawberry.h"

void Strawberry::update(float dt)
{
	PowerUp::update(dt);
	int current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
	m_brush_power.texture = m_state->getAssetPath(m_name + "\\output_") + std::to_string(current_frame) + ".png";
}

void Strawberry::init()
{
	frame_count = 0;
	m_brush_power.fill_opacity = 1.f;
	m_brush_power.outline_opacity = 0.f;
	m_brush_power.texture = m_state->getAssetPath(m_name + "\\output_1.png");
}

void Strawberry::draw()
{
	PowerUp::draw();
}

void Strawberry::activation()
{
}
