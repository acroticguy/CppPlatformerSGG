#include "Wall.h"
#include "Player.h"

void Wall::update(float dt)
{
	for (Box* box : list) {

		float collision_offset = m_state->getPlayer()->intersectDown(*box);
		if (collision_offset < 0.f) {
			m_state->getPlayer()->setVerticalV(0.f);
			m_state->getPlayer()->m_pos_y += collision_offset;
		}

		collision_offset = m_state->getPlayer()->intersectSideways(*box);

		if (collision_offset != 0.f) {
			side_col = collision_offset;
			m_state->getPlayer()->m_pos_x += collision_offset;
		}
	}
	GameObject::update(dt);
}

void Wall::init()
{
	m_brush_wall.fill_opacity = 1.f;
	m_brush_wall.outline_opacity = 0.f;
	m_brush_wall.texture = m_state->getAssetPath(m_name + ".png");
	for (float i = starting_y; i < ending_y + 1; i++) {
		for (float j = starting_x; j < ending_x + 1; j++) {
			list.push_back(new Box(j, i, 1, 1));
		}
	}
}

void Wall::draw()
{
	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			if (m_state->m_global_offset_y - h / 2 > 0) {
				for (Box* box : list) {
					graphics::drawRect(box->m_pos_x + m_state->getBackgroundWidth() / 2, box->m_pos_y + m_state->getBackgroundHeight() / 2, box->m_width, box->m_height, m_brush_wall);
				}
			}
			else {
				for (Box* box : list) {
					graphics::drawRect(box->m_pos_x + m_state->getBackgroundWidth() / 2, box->m_pos_y + m_state->m_global_offset_y, box->m_width, box->m_height, m_brush_wall);
				}
			}
		}
		else {
			if (m_state->m_global_offset_y - h / 2 > 0) {
				for (Box* box : list) {
					graphics::drawRect(box->m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, box->m_pos_y + m_state->getBackgroundHeight() / 2, box->m_width, box->m_height, m_brush_wall);
				}
			} else {
				for (Box* box : list) {
					graphics::drawRect(box->m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, box->m_pos_y + m_state->m_global_offset_y, box->m_width, box->m_height, m_brush_wall);
				}
			}
		}
	}
	else {
		if (m_state->m_global_offset_y - h / 2 > 0) {
			for (Box* box : list) {
				graphics::drawRect(box->m_pos_x + m_state->m_global_offset_x, box->m_pos_y + m_state->getBackgroundHeight() / 2, box->m_width, box->m_height, m_brush_wall);
			}
		} else {
			for (Box* box : list) {
				graphics::drawRect(box->m_pos_x + m_state->m_global_offset_x, box->m_pos_y + m_state->m_global_offset_y, box->m_width, box->m_height, m_brush_wall);
			}
		}
	}
}
