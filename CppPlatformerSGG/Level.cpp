#include "Level.h"
#include "GameState.h"
#include "Player.h"
#include "Wall.h"
#include "PowerUp.h"
#include <math.h>

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->update(dt);
		for (auto p_gob : m_static_objects) {
			p_gob->update(dt);
			Wall* p_wall = dynamic_cast<Wall*>(p_gob); // Cast Wall* in order to be able to be treated as Box when we use intersect() methods later
			if (p_wall != nullptr) {
				float collision_offset = m_state->getPlayer()->intersectDown(*p_wall);
				if (collision_offset < 0.f) {
					m_state->getPlayer()->setVerticalV(0.f);
					m_state->getPlayer()->m_pos_y += collision_offset;
					m_state->getInstance()->m_global_collision = true;
				}
				else {
					m_state->getInstance()->m_global_collision = false;
				}
			}
		}
	}

	GameObject::update(dt);
}

void Level::init()
{
	m_brush_background.outline_opacity = 0.f;
	m_brush_background.texture = m_state->getAssetPath("profilebg.png");

	Wall* ground = new Wall(0, 8, 72, 1);
	Wall* random_block = new Wall(3, 7, 3, 1);
	Wall* random_block2 = new Wall(7, 6, 3, 1);
	PowerUp* apple = new PowerUp(-1, 7, 1, 1);
	apple->setCycle(17);

	m_static_objects.push_back(ground);
	m_static_objects.push_back(random_block);
	m_static_objects.push_back(random_block2);
	m_static_objects.push_back(apple);

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

	offset_x = m_state->m_global_offset_x - w/2;
	offset_y = m_state->m_global_offset_y - h/2;

	if (m_state->isOnEdge()) {
		if (offset_x > 0) {
			graphics::drawRect(m_state->getBackgroundWidth()/2, m_state->m_global_offset_y, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
		} else {
			graphics::drawRect(w - m_state->getBackgroundWidth()/2, m_state->m_global_offset_y, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
		}
	} else {
		graphics::drawRect(m_state->m_global_offset_x, m_state->m_global_offset_y, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
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
	graphics::drawText(1, 1, 1, std::string("x = ") + std::to_string(offset_x), br);
	graphics::drawText(1, 2, 1, std::string("y = ") + std::to_string(offset_y), br);
	graphics::drawText(1, 3, 1, std::string("We Collided: ") + std::to_string(m_state->getInstance()->m_global_collision), br);
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
