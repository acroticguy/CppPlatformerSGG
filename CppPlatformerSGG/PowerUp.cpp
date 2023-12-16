#include "PowerUp.h"

void PowerUp::update(float dt)
{
	frame_count += animation_cycle * dt / 1000.f; // In 1s we will have circled 1 animation
	current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
	m_brush_power.texture = m_state->getAssetPath("Bananas\\output_") + std::to_string(current_frame) + ".png";
	GameObject::update(dt);
}

void PowerUp::init()
{
	frame_count = 0;
	m_brush_power.fill_opacity = 1.f;
	m_brush_power.outline_opacity = 0.f;
	m_brush_power.texture = m_state->getAssetPath("Bananas\\output_1.png");
}

void PowerUp::draw()
{
	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_power);
		}
		else {
			graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_power);
		}
	}
	else {
		graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_power);
	}

	graphics::Brush br;
	graphics::setFont(m_state->getAssetPath("orange juice 2.0.ttf"));
	graphics::drawText(1, 4, 1, std::string("Frame = ") + std::to_string(current_frame), br);
}

void PowerUp::activation() {

}

void PowerUp::setCycle(const int& cycle)
{
	animation_cycle = cycle;
}
