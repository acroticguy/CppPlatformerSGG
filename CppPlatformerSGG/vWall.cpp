#include "vWall.h"

void vWall::update(float dt)
{
	GameObject::update(dt);
}

void vWall::init()
{
	m_brush_vWall.fill_opacity = 1.f;
	m_brush_vWall.outline_opacity = 0.f;
	m_brush_vWall.texture = m_state->getAssetPath("vWallSmall2.png");
}

void vWall::draw()
{
	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_vWall);
		}
		else {
			graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_vWall);
		}
	}
	else {
		graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_vWall);
	}


}