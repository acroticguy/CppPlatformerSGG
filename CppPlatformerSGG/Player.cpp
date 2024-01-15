#include "Player.h"
#include "graphics.h"
#include "GameState.h"
#include <math.h>


/*Vangelis*/
float Player::getHealth()
{
	return health;
}

void Player::setHealth(float h)
{
	health = h;
}

void Player::updateHealth(float h)
{
	health += h;
}

int Player::getLives()
{
	return lives;
}

void Player::setLives(int l)
{
	lives += l;
}
/*Vangelis*/

void Player::update(float dt)
{
	float delta_t = dt / 1000.f;

	frame_count += animation_cycle * delta_t;
	//int current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
	//m_brush_player.texture = m_state->getAssetPath(m_name + "\\output_") + std::to_string(current_frame) + ".png";

	int current_frame;
	if (is_hit) {
		if (hit_frame == 0.f) { graphics::playSound(m_state->getAssetPath("Hero_hit.mp3"), 1.f, false); }
		hit_frame += 1.5 * hit_frame_sum * dt / 1000.f;
		current_frame = (static_cast<int>(floor(hit_frame)) % hit_frame_sum) + 1;
		m_brush_player.texture = m_state->getAssetPath("Hit\\Hero\\output_") + std::to_string(current_frame) + ".png";
		if (current_frame >= 6) {
			is_hit = false;
			hit_frame = 0.f;
		}
	}
	else {
		frame_count += animation_cycle * dt / 1000.f; // In 1s we will have circled 1 animation
		current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
		m_brush_player.texture = m_state->getAssetPath(m_name + "\\output_") + std::to_string(current_frame) + ".png";
	}


	vertical_v += gravity;
	float jump_v = 15.f;

	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT)) { m_pos_x -= delta_t * v; direction = -1.f;}
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT)) { m_pos_x += delta_t * v; direction = 1.f;}
	if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP)) { m_pos_y -= delta_t * jump_v;}
	if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN)) { m_pos_y = std::min(7.2f, m_pos_y + v * delta_t);
	}

	// We wanted to prevent the player from falling under the map, so we originally set a min height of 7. Then, since there was no collision with the ground, we couldn't eliminate the vertical velocity. That's why we used 7.01, to barely have the player stand in the ground.

	m_pos_y = std::min(7.2f, m_pos_y + vertical_v * delta_t);

	vertical_v = (vertical_v > terminal_v) ? terminal_v : vertical_v + gravity * delta_t / 20;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.f - m_pos_y;

	GameObject::update(dt);
}

void Player::init()
{
	m_pos_x = -25.f;
	m_pos_y = 0.f;
	/*m_width = 0.8f;
	m_height = 0.8f;*/

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.f - m_pos_y;

	m_brush_player.fill_opacity = 1.f;
	m_brush_player.outline_opacity = 1.f;
	m_brush_player.texture = m_state->getAssetPath(m_name + "\\output_1.png");
}

void Player::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	float temp = m_state->m_global_offset_x - w / 2;
	if (m_state->isOnEdge()) {// is edge
		if (temp > 0) {// left
			graphics::drawRect(2*w + m_pos_x, h / 2, direction * m_width, m_height, m_brush_player);
		}
		else { // right
			graphics::drawRect(-w + m_pos_x, h / 2, direction * m_width, m_height, m_brush_player);
		}
	}
	else {
		graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, direction * m_width /** 1.25f*/, m_height /** 1.25f*/, m_brush_player);
	}
}

void Player::setVerticalV(float new_v)
{
	vertical_v = new_v;
}
