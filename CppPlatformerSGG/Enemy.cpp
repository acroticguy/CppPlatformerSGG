#include "Enemy.h"
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

float Enemy::getM_pos_y()
{
	return m_pos_y;
}



void Enemy::update(float dt)
{
	float delta_t = dt / 1000.f;
	
	m_active = fabs(m_pos_x) <= fabs(exit_point);

	m_pos_x += direction * ve * delta_t;


	int current_frame;
	if (is_killed) {
		if (kill_frame == 0.f) { graphics::playSound(m_state->getAssetPath("Enemy_hit.mp3"), 1.f, false); }
		kill_frame += 3.5 * kill_frame_sum * dt / 1000.f;
		current_frame = (static_cast<int>(floor(kill_frame)) % kill_frame_sum) + 1;
		m_brush_enemy.texture = m_state->getAssetPath("Hit\\Enemy\\output_") + std::to_string(current_frame) + ".png";
		direction *= -1;//Van
		exit_point = m_pos_x+0.01 ;//Van
		
		

		if (current_frame >= 6) {			
			is_killed = false;
			kill_frame = 0.f;
		}
	}
	else {
		//frame_count += animation_cycle * dt / 1000.f; // In 1s we will have circled 1 animation
		//current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
		//m_brush_enemy.texture = m_state->getAssetPath(m_name + "\\output_") + std::to_string(current_frame) + ".png";
		m_brush_enemy.texture = m_state->getAssetPath("enemy.png");
	}



	GameObject::update(dt);
}

void Enemy::init()
{
	m_pos_x = direction * -(m_state->getBackgroundWidth() / 2 + 1);
	exit_point = -m_pos_x;
	m_brush_enemy.fill_opacity = 1.f;
	m_brush_enemy.outline_opacity = 0.f;
	m_brush_enemy.texture = m_state->getAssetPath("enemy.png");
}

void Enemy::draw() {

	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, Box::m_pos_y + m_state->m_global_offset_y, direction * m_width, m_height, m_brush_enemy);
		}
		else {
			graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, Box::m_pos_y + m_state->m_global_offset_y, direction * m_width, m_height, m_brush_enemy);
		}
	}
	else {
		graphics::drawRect(m_pos_x + m_state->m_global_offset_x, Box::m_pos_y + m_state->m_global_offset_y, direction * m_width, m_height, m_brush_enemy);
	}
}



Enemy::~Enemy(){
}