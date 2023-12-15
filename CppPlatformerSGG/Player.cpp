#include "Player.h"
#include "graphics.h"
#include "GameState.h"
#include <math.h>

void Player::update(float dt)
{
	float delta_t = dt / 1000.f;

	vertical_v += gravity;
	float jump_v = 15.f;

	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT)) { m_pos_x -= delta_t * v;}
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT)) { m_pos_x += delta_t * v;}
	if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP)) { m_pos_y -= delta_t * jump_v;}
	if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN)) { m_pos_y += delta_t * v;}

	m_pos_y += vertical_v * delta_t;

	vertical_v = (vertical_v > terminal_v) ? terminal_v : vertical_v + gravity * delta_t / 20;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.f - m_pos_y;

	GameObject::update(dt);
}

void Player::init()
{
	m_pos_x = -25.f;
	m_pos_y = 0.f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.f - m_pos_y;

	m_brush_player.fill_opacity = 1.f;
	m_brush_player.outline_opacity = 0.f;
	m_brush_player.texture = m_state->getAssetPath("boy2.png");
}

void Player::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	float temp = m_state->m_global_offset_x - w / 2;
	if (m_state->isOnEdge()) {// is edge
		if (temp > 0) {// left
			graphics::drawRect(2*w + m_pos_x, h / 2, m_width, m_height, m_brush_player);
		}
		else { // right
			graphics::drawRect(-w + m_pos_x, h / 2, m_width, m_height, m_brush_player);
		}
	}
	else {
		graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, m_width, m_height, m_brush_player);
	}
	//graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, m_width, m_height, m_brush_player);
}

void Player::setVerticalV(float new_v)
{
	vertical_v = new_v;
}
