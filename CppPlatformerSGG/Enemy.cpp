#include "Enemy.h"
#include "Player.h"
#include "graphics.h"
#include "GameState.h"

void Enemy::setKilled(bool status)//Van
{
	is_killed = status;
}

bool Enemy::getActive()
{
	return m_active;
}

void Enemy::update(float dt)
{
	float delta_t = dt / 1000.f;
	
	m_active = fabs(m_pos_x) <= fabs(exit_point);

	m_pos_x += direction * ve * delta_t;

	int current_frame;
	if (is_killed) {
		if (kill_frame == 0.f) { 
			graphics::playSound(m_state->getAssetPath("Enemy\\Enemy_hit.mp3"), 1.f, false); 
			m_brush_score_p.fill_opacity = 0.2f;
			m_state->getPlayer()->score += value;
		}

		m_brush_score_p.fill_opacity = std::min(1.f, m_brush_score_p.fill_opacity + delta_t * 4);
		score_pos_offset += delta_t / 2;

		kill_frame += kill_frame_sum * dt / 1000.f;
		current_frame = (static_cast<int>(floor(kill_frame)) % kill_frame_sum) + 1;
		m_brush_enemy.texture = m_state->getAssetPath("Enemy\\Hit\\output_") + std::to_string(current_frame) + ".png";

		if (current_frame >= 7) {
			m_state->getPlayer()->enemies_killed += 1;//Van
			m_active = false;
			kill_frame = 0.f;
		}

	}
	else {
		frame_count += animation_cycle * dt / 1000.f;
		current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
		m_brush_enemy.texture = m_state->getAssetPath("Enemy\\" + m_name + "\\Flying\\output_" + std::to_string(current_frame) + ".png");
	}

	hitbox->m_pos_x = m_pos_x;

	GameObject::update(dt);
}

void Enemy::init()
{
	m_pos_x = direction * -(m_state->getBackgroundWidth() / 2 + 1);
	hitbox->m_pos_x = m_pos_x;

	exit_point = -m_pos_x;
	m_brush_enemy.fill_opacity = 1.f;
	m_brush_enemy.outline_opacity = 0.f;
	m_brush_enemy.texture = m_state->getAssetPath("Enemy\\" + m_name + "\\Flying\\output_1.png");

	//Score Popup
	m_brush_score_p.fill_opacity = 0.f;

	//Hitbox
	m_brush_hbox.fill_opacity = 0.f;
	m_brush_hbox.outline_opacity = 1.f;
}

void Enemy::draw() {

	
	// -direction (Bat looks left)
	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, -direction * m_width, m_height, m_brush_enemy);

			//Score Popup
			graphics::drawText(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y - score_pos_offset + m_state->m_global_offset_y, 0.4, std::to_string(value), m_brush_score_p);

			//Debug Frame:
			if (m_state->debug_mode) {
				graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
		else {
			graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, -direction * m_width, m_height, m_brush_enemy);
			
			//Score Popup
			graphics::drawText(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y - score_pos_offset + m_state->m_global_offset_y, 0.4, std::to_string(value), m_brush_score_p);

			//Debug Frame:
			if (m_state->debug_mode) {
				graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
	}
	else {
		graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, -direction * m_width, m_height, m_brush_enemy);

		//Score Popup
		graphics::drawText(m_pos_x + m_state->m_global_offset_x, m_pos_y - score_pos_offset + m_state->m_global_offset_y, 0.4, std::to_string(value), m_brush_score_p);

		//Debug Frame:
		if (m_state->debug_mode) {
			graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
		}
	}
}



Enemy::~Enemy(){}