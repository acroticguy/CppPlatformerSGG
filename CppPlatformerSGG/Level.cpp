#include "Level.h"
#include "GameState.h"
#include "Player.h"
#include <math.h>

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->update(dt);
	}

	is_on_edge = fabs(offset_x) >= w;

	GameObject::update(dt);
}

void Level::init()
{
	m_brush_background.outline_opacity = 0.f;
	m_brush_background.texture = m_state->getAssetPath("profilebg.png");

	for (auto p_gob : m_static_objects) {
		if (p_gob) {
			p_gob->init();
		}
	}
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) {
			p_gob->init();
		}
	}
}

void Level::draw()
{
	w = m_state->getCanvasWidth();
	h = m_state->getCanvasHeight();

	offset_x = m_state->m_global_offset_x - w/2;
	offset_y = m_state->m_global_offset_y - h/2;

	if (is_on_edge) {
		if (offset_x > 0) {
			graphics::drawRect(3*w/2, m_state->m_global_offset_y, 4.f * w, 2.f * h, m_brush_background);
		} else {
			graphics::drawRect(-w/2, m_state->m_global_offset_y, 4.f * w, 2.f * h, m_brush_background);
		}
	} else {
		graphics::drawRect(m_state->m_global_offset_x, m_state->m_global_offset_y, 4.f * w, 2.f * h, m_brush_background);
	}
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->draw();
	}

	for (auto p_gob : m_static_objects) {
		if (p_gob) {
			p_gob->draw();
		}
	}
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) {
			p_gob->draw();
		}
	}

	graphics::Brush br;
	graphics::setFont(m_state->getAssetPath("orange juice 2.0.ttf"));
	graphics::drawText(1, 1, 2, std::string("x = ") + std::to_string(offset_x), br);
}

Level::Level(const std::string& name) {}

Level::~Level()
{
	for (auto p_gob : m_static_objects) {
		if (p_gob) {
			delete p_gob;
		}
	}
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) {
			delete p_gob;
		}
	}
}
