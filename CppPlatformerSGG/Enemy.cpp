#include "Enemy.h"
#include "graphics.h"
#include "GameState.h"

void Enemy::update(float dt)
{
	float delta_t = dt / 1000.f;

	const float v = 5.f;
}

void Enemy::init()
{
	m_pos_x = 0.f;
	m_pos_y = 0.f;
}

void Enemy::draw()
{
}
