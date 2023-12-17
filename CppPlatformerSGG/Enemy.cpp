#include "Enemy.h"
#include "graphics.h"
#include "GameState.h"

void Enemy::update(float dt)
{
	float delta_t = dt / 1000.f;
	

	m_pos_x += direction * ve * delta_t;

	GameObject::update(dt);
}

void Enemy::init()
{
	m_pos_x = direction * -(m_state->getBackgroundWidth() / 2 + 1);
	m_brush_enemy.fill_opacity = 1.f;
	m_brush_enemy.outline_opacity = 0.f;
	m_brush_enemy.texture = m_state->getAssetPath("enemy.png");
}

void Enemy::draw() {

	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, direction * m_width, m_height, m_brush_enemy);
		}
		else {
			graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, direction * m_width, m_height, m_brush_enemy);
		}
	}
	else {
		graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, direction * m_width, m_height, m_brush_enemy);
	}
}