#include "PowerUp.h"
#include "Player.h"
#include <math.h>

void PowerUp::update(float dt)
{
	activation(dt);
	
	GameObject::update(dt);
}

void PowerUp::init()
{
	frame_count = 0;
	m_brush_power.fill_opacity = 1.f;
	m_brush_power.outline_opacity = 0.f;
	m_brush_power.texture = m_state->getAssetPath("Fruits\\" + this->getName() + "\\output_1.png"); //We call getName() due to the way polymorphic calls are made. If we simply used m_name, we would get the default PowerUp m_name. Since we want the child's m_name, we call the method.

	//Score Popup
	m_brush_score_p.fill_opacity = 0.f;

	//HITBOX
	m_brush_hbox.fill_opacity = 0.f;
	m_brush_hbox.outline_opacity = 1.f;
}

void PowerUp::draw()
{
	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			if (m_state->m_global_offset_y - h / 2 > 0) {
				graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight()/2, m_width, m_height, m_brush_power);

				//Score Popup
				graphics::drawText(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y - score_pos_offset + m_state->getBackgroundHeight() / 2, 0.4, std::to_string(this->getScore()), m_brush_score_p);

				//HITBOX
				if (m_state->debug_mode) {
					graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight() / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			} else {
				graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_power);

				//Score Popup
				graphics::drawText(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y - score_pos_offset + m_state->m_global_offset_y, 0.4, std::to_string(this->getScore()), m_brush_score_p);

				//HITBOX
				if (m_state->debug_mode) {
					graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
			
		} else {
			if (m_state->m_global_offset_y - h / 2 > 0) {
				graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight() / 2, m_width, m_height, m_brush_power);

				//Score Popup
				graphics::drawText(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight() / 2 - score_pos_offset, 0.4, std::to_string(this->getScore()), m_brush_score_p);

				//HITBOX
				if (m_state->debug_mode) {
					graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight() / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
			else {
				graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_power);

				//Score Popup
				graphics::drawText(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y - score_pos_offset + m_state->m_global_offset_y, 0.4, std::to_string(this->getScore()), m_brush_score_p);

				//HITBOX
				if (m_state->debug_mode) {
					graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
			
		}
	} else {
		if (m_state->m_global_offset_y - h / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->getBackgroundHeight() / 2, m_width, m_height, m_brush_power);

			//Score Popup
			graphics::drawText(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->getBackgroundHeight() / 2 - score_pos_offset, 0.4, std::to_string(this->getScore()), m_brush_score_p);

			//HITBOX
			if (m_state->debug_mode) {
				graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->getBackgroundHeight() / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
		else {
			graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_power);

			//Score Popup
			graphics::drawText(m_pos_x + m_state->m_global_offset_x, m_pos_y - score_pos_offset + m_state->m_global_offset_y, 0.4, std::to_string(this->getScore()), m_brush_score_p);

			//HITBOX
			if (m_state->debug_mode) {
				graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
		
	}

}

void PowerUp::activation(float dt) {
	int current_frame;

	float delta_t = dt / 1000.f;
	if (is_collected) {
		if (collected_frame == 0.f) {
			graphics::playSound(m_state->getAssetPath("Fruits\\pop.mp3"), 1.f, false);
			float new_health = std::min(200.f, m_state->getPlayer()->getHealth() + this->getHeal());
			m_state->getPlayer()->setHealth(new_health);

			m_brush_score_p.fill_opacity = 0.2f;
			m_state->getPlayer()->score += this->getScore();
		}

		m_brush_score_p.fill_opacity = std::min(1.f, m_brush_score_p.fill_opacity + delta_t * 4);

		score_pos_offset += delta_t/2;

		

		collected_frame += 1.5 * collected_frame_sum * delta_t;
		current_frame = (static_cast<int>(floor(collected_frame)) % collected_frame_sum) + 1;
		m_brush_power.texture = m_state->getAssetPath("Fruits\\Collected\\output_") + std::to_string(current_frame) + ".png";

		if (current_frame >= collected_frame_sum) {
			is_collected = false;
			collected_frame = 0.f;
			m_active = false;

			m_brush_score_p.fill_opacity = 0.f;
		}
	}
	else {
		frame_count += animation_cycle * delta_t; // In 1s we will have circled 1 animation
		current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
		m_brush_power.texture = m_state->getAssetPath("Fruits\\" + this->getName() + "\\output_") + std::to_string(current_frame) + ".png"; //We call getName() due to the way polymorphic calls are made. If we simply used m_name, we would get the default PowerUp m_name. Since we want the child's m_name, we call the method.
	}
}