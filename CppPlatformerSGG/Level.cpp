#include "Level.h"
#include "GameState.h"
#include "Player.h"
#include "Wall.h"
#include "PowerUp.h"
#include "Apple.h"
#include "Bananas.h"
#include "Cherries.h"
#include "Kiwi.h"
#include "Melon.h"
#include "Orange.h"
#include "Pineapple.h"
#include "Strawberry.h"
#include "Enemy.h"
#include <math.h>

void Level::update(float dt)
{
	float delta_t = dt / 10.f;
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->update(dt);
		for (auto& p_gob : m_static_objects) {
			p_gob->update(dt);
		}

		for (auto& p_pwr : m_power_ups) {
			p_pwr->update(dt);
			if (m_state->getPlayer()->intersect(*p_pwr) && !p_pwr->is_collected) {
				p_pwr->is_collected = true;
			}
		}
		time += delta_t;
		int current_sec = static_cast<int>(floor(time));
		if (current_sec % 500 == 499) {
			Enemy* opp = new Enemy(m_state->getPlayer()->m_pos_y);
			opp->init();
			m_dynamic_objects.push_back(opp);
		}

		for (auto it = m_dynamic_objects.begin(); it != m_dynamic_objects.end();) {
			auto p_gob = *it;  // Get the pointer from the iterator.

			if (p_gob->isActive()) {
				p_gob->update(dt);
				++it;  // Move to the next element.
			}
			else {
				it = m_dynamic_objects.erase(it);  // Erase returns the iterator to the next element.
				delete p_gob;
			}
		}
	}

	GameObject::update(dt);
}

void Level::init()
{
	time = 0;
	m_brush_background.outline_opacity = 0.f;
	m_brush_background.texture = m_state->getAssetPath("profilebg.png");

	Wall* ground = new Wall(-32, 32, 8, 8, "Grass");
	Wall* random_block = new Wall(1, 3, 7, 7, "Grass");
	Wall* wall_left = new Wall(-31.5f, -31.5f, 0, 7, "Wall");
	Wall* wall_right = new Wall(31.5f, 31.5f, 0, 7, "Wall");
	/*Wall* random_block2 = new Wall(6, 8, 5, 6, "Grass");*/

	PowerUp* apple = new Apple(-1, 7, 1, 1);
	PowerUp* banana = new Bananas(-5, 7, 1, 1);
	PowerUp* cherry = new Cherries(4, 5, 1, 1);
	PowerUp* kiwi = new Kiwi(7, 7, 1, 1);
	PowerUp* melon = new Melon(-10, 7, 1, 1);
	PowerUp* orange = new Orange(10, 7, 1, 1);
	PowerUp* ananas = new Pineapple(6, 5, 1, 1);
	PowerUp* strawberry = new Strawberry(-14, 7, 1, 1);

	m_static_objects.push_back(ground);
	m_static_objects.push_back(random_block);
	m_static_objects.push_back(wall_left);
	m_static_objects.push_back(wall_right);
	/*m_static_objects.push_back(random_block2);*/
	m_power_ups.push_back(apple);
	m_power_ups.push_back(banana);
	m_power_ups.push_back(cherry);
	m_power_ups.push_back(kiwi);
	m_power_ups.push_back(melon);
	m_power_ups.push_back(orange);
	m_power_ups.push_back(ananas);
	m_power_ups.push_back(strawberry);

	/*for (int i = 0; i < 8; i++) {
		vWall* leftWall_i = new vWall(-31.5, i, 1, 1);
		vWall* rightWall_i = new vWall(31.5, i, 1, 1);
		m_static_objects.push_back(leftWall_i);
		m_static_objects.push_back(rightWall_i);
	}*/

	for (auto& p_gob : m_static_objects) {
		if (p_gob) {
			p_gob->init();
		}
	}
	for (auto& p_pwr : m_power_ups) {
		if (p_pwr) {
			p_pwr->init();
		}
	}
	for (auto& p_gob : m_dynamic_objects) {
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
	for (auto p_pwr : m_power_ups) {
		if (p_pwr) {
			p_pwr->draw();
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
	graphics::drawText(1, 3, 1, std::string("Enemies = ") + std::to_string(m_dynamic_objects.size()), br);
	//graphics::drawText(1, 4, 1, std::string("Side Col = ") + std::to_string(side_col), br);
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
