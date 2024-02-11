#include "Player.h"
#include "graphics.h"
#include "GameState.h"
#include <math.h>

float Player::getHealth()
{
	return health;
}

void Player::setHealth(float h)
{
	health = h;
}

void Player::update(float dt)
{
	float delta_t = dt / 1000.f;

	frame_count += animation_cycle * delta_t;

	if (health <= 0) { 
		is_dead = true;
	}

	curr_cd += delta_t;

	bool cd_exceeded = (curr_cd > m_state->cooldown);

	int current_frame;
	if (is_hit) {
		if (hit_frame == 0.f) { graphics::playSound(m_state->getAssetPath("Players\\Hero_hit.mp3"), 1.f, false); }
		hit_frame += hit_frame_sum * dt / 1000.f;
		current_frame = (static_cast<int>(floor(hit_frame)) % hit_frame_sum) + 1;
		m_brush_player.texture = m_state->getAssetPath("Players\\" + m_name + "\\Hit\\output_") + std::to_string(current_frame) + ".png";
		if (current_frame >= 7) {
			is_hit = false;
			hit_frame = 0.f;
		}
	} else {
		frame_count += animation_cycle * dt / 1000.f; // In 1s we will have circled 1 animation
		current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
		m_brush_player.texture = m_state->getAssetPath("Players\\" + m_name + "\\Idle\\output_") + std::to_string(current_frame) + ".png";
	}

	vertical_v += gravity;
	

	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT)) { m_pos_x -= delta_t * v; direction = -1.f;}
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT)) { m_pos_x += delta_t * v; direction = 1.f;}
	if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP)) { m_pos_y -= delta_t * jump_v;}
	if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN)) { m_pos_y = std::min(m_state->getBackgroundHeight() / 2 - 1 + 0.2f, m_pos_y + v * delta_t); }

	//Debug Toggle
	if (graphics::getKeyState(graphics::SCANCODE_G)) { 
		if (cd_exceeded) { m_state->debug_mode = !m_state->debug_mode; curr_cd = 0; }
	}

	// We wanted to prevent the player from falling under the map. Since there was no collision with the ground, we couldn't eliminate the vertical velocity. That's why we used the ground y and set a hard boundary, to barely have the player stand in the ground.

	m_pos_y = std::min(m_state->getBackgroundHeight()/2 - 1 + 0.2f, m_pos_y + vertical_v * delta_t);

	vertical_v = (vertical_v > terminal_v) ? terminal_v : vertical_v + gravity * delta_t / 20;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.f - m_pos_y;

	hitbox->m_pos_x = m_pos_x;
	hitbox->m_pos_y = m_pos_y;

	GameObject::update(dt);
}

void Player::init()
{
	curr_cd = 0;
	is_dead = false;

	m_pos_x = -29.f;
	m_pos_y = 0.f;
	hitbox->m_pos_x = m_pos_x;
	hitbox->m_pos_y = m_pos_y;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.f - m_pos_y;

	m_brush_player.fill_opacity = 1.f;
	m_brush_player.outline_opacity = 0.f;
	m_brush_player.texture = m_state->getAssetPath("Players\\" + m_name + "\\Idle\\output_1.png");

	m_brush_hbox.fill_opacity = 0.f;
	m_brush_hbox.outline_opacity = 1.f;
}

void Player::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	float x_edge = m_state->m_global_offset_x - w / 2;
	float y_edge = m_state->m_global_offset_y - h / 2;

	if (m_state->isOnEdge()) {// is edge
		if (x_edge > 0) {// left
			if (y_edge > 0) {
				graphics::drawRect(2 * w + m_pos_x, h / 2 + m_pos_y, direction * m_width, m_height, m_brush_player);

				//Debug Frame:
				if (m_state->debug_mode) {
					graphics::drawRect(2 * w + m_pos_x, h / 2 + m_pos_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			} else {
				graphics::drawRect(2 * w + m_pos_x, h / 2, direction * m_width, m_height, m_brush_player);

				//Debug Frame:
				if (m_state->debug_mode) {
					graphics::drawRect(2 * w + m_pos_x, h / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
		} else { // right
			if (y_edge > 0) {
				graphics::drawRect(-w + m_pos_x, h / 2 + m_pos_y, direction * m_width, m_height, m_brush_player);

				//Debug Frame:
				if (m_state->debug_mode) {
					graphics::drawRect(-w + m_pos_x, h / 2 + m_pos_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
			else {
				graphics::drawRect(-w + m_pos_x, h / 2, direction * m_width, m_height, m_brush_player);

				//Debug Frame:
				if (m_state->debug_mode) {
					graphics::drawRect(-w + m_pos_x, h / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
		}
	}
	else {
		if (y_edge > 0) {
			graphics::drawRect(w / 2, h / 2 + m_pos_y, direction * m_width, m_height, m_brush_player);

			//Debug Frame:
			if (m_state->debug_mode) {
				graphics::drawRect(w / 2, h / 2 + m_pos_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
		else {
			graphics::drawRect(w / 2, h / 2, direction * m_width, m_height, m_brush_player);

			//Debug Frame:
			if (m_state->debug_mode) {
				graphics::drawRect(w / 2, h / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
	}
}

void Player::setVerticalV(float new_v)
{
	vertical_v = new_v;
}
