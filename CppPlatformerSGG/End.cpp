#include "End.h"
#include "Player.h"
#include "graphics.h"
#include "GameState.h"

void End::update(float dt)
{
	if (m_state->getPlayer()->intersect(*this) && m_state->getPlayer()->score >= score_required) { is_active = true; }

	float delta_t = dt / 1000.f;

	frame_count += animation_cycle * delta_t;

	int current_frame;
	if (is_active && !animation_over) {
		//We just got to the flag
		if (active_count == 0.f) { 
			graphics::stopMusic(1500);
			graphics::playSound(m_state->getAssetPath("win_2.wav"), 1.f, false);
		}
		active_count += transition_cycle * delta_t;
		current_frame = (static_cast<int>(floor(active_count)) % transition_cycle) + 1;
		m_brush_end.texture = m_state->getAssetPath("End\\Checkpoint\\output_") + std::to_string(current_frame) + ".png";
		if (current_frame >= 26) {
			//Checkpoint_Active
			animation_over = true;
			active_count = 0;
		}
	}

	//Flag wave after being raised
	if (animation_over) {
		active_count += wave_cycle * delta_t;
		current_frame = (static_cast<int>(floor(active_count)) % wave_cycle) + 1;
		m_brush_end.texture = m_state->getAssetPath("End\\Checkpoint_After\\output_") + std::to_string(current_frame) + ".png";
		// 2 Seconds after flag waves, bring in congratulations
		if (active_count / wave_cycle > 2) {
			//Congratulations needs to be initialized on every run for the sound to play.
			m_state->initCong();
			m_state->in_congratulations = true;
		}
	}
}

void End::init()
{
	frame_count = 0.f;
	active_count = 0.f;
	m_brush_end.fill_opacity = 1.f;
	m_brush_end.outline_opacity = 0.f;
	m_brush_end.texture = m_state->getAssetPath("End\\Idle.png");

	m_brush_hbox.fill_opacity = 0.f;
	m_brush_hbox.outline_opacity = 1.f;
}

void End::draw()
{
	//YOU DON'T HAVE ENOUGH POINTS MESSAGE
	if (m_state->getPlayer()->intersect(*this) && m_state->getPlayer()->score < score_required) {
		graphics::drawText(2.5, 1.5f, 0.5f,std::string("You don't have enough points to go through!"), m_brush_end);
		graphics::drawText(2.5, 2.0f, 0.5f, std::string("Score required: ") + std::to_string(score_required - m_state->getPlayer()->score), m_brush_end);
	}

	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_end);

			//Debug Frame:
			if (m_state->debug_mode) {
				graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
		else {
			graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_end);

			//Debug Frame:
			if (m_state->debug_mode) {
				graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
	}
	else {
		graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_end);

		//Debug Frame:
		if (m_state->debug_mode) {
			graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
		}
	}
}
