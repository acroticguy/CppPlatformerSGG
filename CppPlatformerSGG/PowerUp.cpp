#include "PowerUp.h"
#include "Player.h"
#include <math.h>

void PowerUp::update(float dt)
{
	int current_frame;
	if (is_collected) {				
		if (collected_frame == 0.f) { 
			graphics::playSound(m_state->getAssetPath("pop.mp3"), 1.f, false);
			float new_health = std::min(200.f, m_state->getPlayer()->getHealth() + 10);
			m_state->getPlayer()->setHealth(new_health);
		}
		collected_frame += 1.5*collected_frame_sum * dt / 1000.f;
		current_frame = (static_cast<int>(floor(collected_frame)) % collected_frame_sum) + 1;
		m_brush_power.texture = m_state->getAssetPath("Collected\\output_") + std::to_string(current_frame) + ".png";
		
		if (current_frame >= collected_frame_sum) {
			is_collected = false;
			collected_frame = 0.f;
			m_active = false;
		}
	} else {
		frame_count += animation_cycle * dt / 1000.f; // In 1s we will have circled 1 animation
		current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
		m_brush_power.texture = m_state->getAssetPath(this->getName() + "\\output_") + std::to_string(current_frame) + ".png";
	}
	GameObject::update(dt);
}

void PowerUp::init()
{
	frame_count = 0;
	m_brush_power.fill_opacity = 1.f;
	m_brush_power.outline_opacity = 0.f;
	m_brush_power.texture = m_state->getAssetPath(this->getName() + "\\output_1.png"); //We call getName() due to the way polymorphic calls are made. If we simply used m_name, we would get the default PowerUp m_name. Since we want the child's m_name, we call the method.
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
}

void PowerUp::activation() {
}