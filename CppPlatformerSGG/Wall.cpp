#include "Wall.h"

void Wall::update(float dt)
{
	GameObject::update(dt);
}

void Wall::init()
{
	m_brush_wall.fill_opacity = 1.f;
	m_brush_wall.outline_opacity = 0.f;
	m_brush_wall.texture = m_state->getAssetPath("Grass_large.png");
}

void Wall::draw()
{
	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y+  m_state->m_global_offset_y, m_width, m_height, m_brush_wall);
		}
		else {
			graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_wall);
		}
	}
	else {
		graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_wall);
	}
	
}
