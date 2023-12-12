#include "Level.h"
#include "GameState.h"
#include "Player.h"

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->update(dt);
	}

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
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x + w / 2.f;
	float offset_y = m_state->m_global_offset_y + h / 2.f;

	graphics::drawRect(offset_x, offset_y, 2.f * w, 4.f * h, m_brush_background);
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
