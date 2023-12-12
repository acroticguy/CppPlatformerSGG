#include "Player.h"
#include "graphics.h"
#include "GameState.h"

void Player::update(float dt)
{
	float delta_t = dt / 1000.f;

	const float v = 10.f;
	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT)) { m_pos_x -= delta_t * v;}
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT)) { m_pos_x += delta_t * v;}
	if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP)) { m_pos_y -= delta_t * v;}
	if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN)) { m_pos_y += delta_t * v;}

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.f - m_pos_y;

	GameObject::update(dt);
}

void Player::init()
{
	m_pos_x = 5.f;
	m_pos_y = 5.f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.f - m_pos_y;

	m_brush_player.fill_opacity = 1.f;
	m_brush_player.outline_opacity = 0.f;
	m_brush_player.texture = m_state->getAssetPath("boy2.png");
}

void Player::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, 1.f, 1.f, m_brush_player);
}
