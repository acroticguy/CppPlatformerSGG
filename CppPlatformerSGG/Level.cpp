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
#include "End.h"
#include <math.h>

void Level::update(float dt)
{
	
	float delta_t = dt / 10.f;

	/*Vangelis - Add countdown for player's health*/
	m_state->getPlayer()->getHealth() <= 0 ? m_state->getPlayer()->updateHealth(0) : m_state->getPlayer()->updateHealth(-delta_t / 100);//Van
	/*Vangelis*/

	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->update(dt);
		for (auto& p_gob : m_static_objects) {
			p_gob->update(dt);
		}

		for (auto& p_pwr : m_power_ups) {
			if (p_pwr->isActive()) { p_pwr->update(dt); }
			if (m_state->getPlayer()->hitbox->intersect(*p_pwr->hitbox) && !p_pwr->is_collected) {
				p_pwr->is_collected = true;	
			}
		}

		time += delta_t;
		int current_sec = static_cast<int>(floor(time));
		if (current_sec % 500 == 499) {
			//Enemy* opp = new Enemy(m_state->getPlayer()->m_pos_y);
			Enemy* opp = new Enemy(1,m_state->getPlayer()->m_pos_y,1.5,1,"Bat");//Van
			opp->init();
			m_Enemies.push_back(opp);
		}
		
		for (auto it = m_Enemies.begin(); it != m_Enemies.end();) {
			auto p_opp = *it;  // Get the pointer from the iterator.			
			if (p_opp->isActive()) {
				p_opp->update(dt);
				if (p_opp->is_killed) { 
					++it;
					continue; 
				}
				if (m_state->getPlayer()->hitbox->intersectDown(*p_opp->hitbox)) {
					float collision_offset = m_state->getPlayer()->hitbox->intersectDown(*p_opp->hitbox);
					if (collision_offset < 0.f /*&& collision_offset >= -0.05*/) {
						m_state->getPlayer()->setVerticalV(0.f);
						m_state->getPlayer()->m_pos_y -= (delta_t / 100.f) * m_state->getPlayer()->jump_v * 5;
						p_opp->setKilled(true);//Van
					}
				}

				if (m_state->getPlayer()->hitbox->intersectSideways(*p_opp->hitbox)) {
					m_state->getPlayer()->is_hit = true;

					if (m_state->getPlayer()->getHealth() >= 0.5) {//Van
						m_state->getPlayer()->updateHealth(-0.5);//Van
					}
					else {//Van
						m_state->getPlayer()->setHealth(0);//Van
					}
				}
				++it;  // Move to the next element.
			}
			else {
				it = m_Enemies.erase(it);  // Erase returns the iterator to the next element.
				delete p_opp;
			}
		}
		
	}
	
	GameObject::update(dt);
}

void Level::init()
{
	//m_state->getPlayer()->updateHealth(m_state->getPlayer()->initHealth);//Van
	time = 0;
	m_brush_background.outline_opacity = 0.f;
	m_brush_background.texture = m_state->getAssetPath("profilebg.png");

	Wall* ground = new Wall(-m_state->getBackgroundWidth() / 2, m_state->getBackgroundWidth() / 2, 8, 8, "Grass");
	Wall* random_block = new Wall(1, 3, 7, 7, "Grass");
	Wall* wall_left = new Wall(-(m_state->getBackgroundWidth() / 2 - 0.5f), -(m_state->getBackgroundWidth() / 2 - 0.5f), 0, m_state->getBackgroundHeight() / 2 - 1, "Wall");
	Wall* wall_right = new Wall((m_state->getBackgroundWidth() / 2 - 0.5f), (m_state->getBackgroundWidth() / 2 - 0.5f), 0, m_state->getBackgroundHeight() / 2 - 1, "Wall");
	PowerUp* apple = new Apple(-1, 7, 1, 1);
	PowerUp* banana = new Bananas(-5, 7, 1, 1);
	PowerUp* cherry = new Cherries(4, 5, 1, 1);
	PowerUp* kiwi = new Kiwi(7, 7, 1, 1);
	PowerUp* melon = new Melon(-10, 7, 1, 1);
	PowerUp* orange = new Orange(10, 7, 1, 1);
	PowerUp* ananas = new Pineapple(6, 5, 1, 1);
	PowerUp* strawberry = new Strawberry(-14, 7, 1, 1);

	End* fin = new End(30, 7, 1, 1);
	
	m_static_objects.push_back(ground);
	m_static_objects.push_back(random_block);
	m_static_objects.push_back(wall_left);
	m_static_objects.push_back(wall_right);
	m_static_objects.push_back(fin);
	m_power_ups.push_back(apple);
	m_power_ups.push_back(banana);
	m_power_ups.push_back(cherry);
	m_power_ups.push_back(kiwi);
	m_power_ups.push_back(melon);
	m_power_ups.push_back(orange);
	m_power_ups.push_back(ananas);
	m_power_ups.push_back(strawberry);
	
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

	for (auto& p_opp : m_Enemies) {
		if (p_opp) {
			p_opp->init();
		}
	}

	graphics::playMusic(m_state->getAssetPath("Soundtracks\\" + soundtrack), 0.2f, true, 1500);
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
			if (p_gob->isActive()) { p_gob->draw(); }
		}
	}
	for (auto p_pwr : m_power_ups) {
		if (p_pwr) {
			if (p_pwr->isActive()) { p_pwr->draw(); }
		}
	}
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) {
			if (p_gob->isActive()) { p_gob->draw(); }
		}
	}
	for (auto p_opp : m_Enemies) {
		if (p_opp) {
			if (p_opp->isActive()) { p_opp->draw(); }
		}
	}

	// Debug outputs
	graphics::Brush br;
	graphics::drawText(0.5, 1.0f, 0.5f, std::string("Enemies killed = ") + std::to_string(m_state->getPlayer()->enemies_killed), br);
	if (m_state->debug_mode) {
		graphics::drawText(1, 1.5f, 0.5f, std::string("x = ") + std::to_string(offset_x), br);
		graphics::drawText(1, 2.0f, 0.5f, std::string("y = ") + std::to_string(offset_y), br);
		graphics::drawText(1, 2.5f, 0.5f, std::string("Enemies = ") + std::to_string(m_Enemies.size()), br);
		graphics::drawText(1, 3.0f, 0.5f, std::string("Hero is hit = ") + std::to_string(m_state->getPlayer()->is_hit), br);
	}
	
	graphics::Brush br_lives;
	br_lives.outline_opacity = 0.f;
	//m_state->getPlayer()->getHealth() 
	SETCOLOR(br_lives.fill_color, 1.f, 0.f, 0.f);
	SETCOLOR(br_lives.fill_secondary_color, 1.f, 1.f, 1.f);
	br_lives.fill_opacity = 1.0f;
	br_lives.fill_secondary_opacity = 0.5f;
	br_lives.gradient = true;
	br_lives.gradient_dir_u = 0.7f;
	br_lives.gradient_dir_v = 0.3f;


	/*Vangelis - Health Bar*/

	graphics::drawText(8.4, 0.7, 0.5, std::string("Life"), br);
	graphics::Brush br_out_health_box;
	br_out_health_box.fill_opacity = 0.1f;
	SETCOLOR(br_out_health_box.fill_color, 0.f, 0.f, 0.f);
	br_out_health_box.outline_opacity = 1.f;
	SETCOLOR(br_out_health_box.outline_color, 1.f, 1.f, 1.f);
	graphics::drawRect(12.5, 0.5, 6, 0.5, br_out_health_box);

	graphics::Brush br_in_health_box;
	br_in_health_box.fill_opacity = 1.f;
	br_in_health_box.outline_opacity = 0.f;
	if ((m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth) > 0.5) {
		SETCOLOR(br_in_health_box.fill_color, 0.5f, 1.f, 0.f);
	}
	else if ((m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth) > 0.2) {
		SETCOLOR(br_in_health_box.fill_color, 1.f, 1.f, 0.f);
	}
	else if ((m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth) > 0.1) {
		SETCOLOR(br_in_health_box.fill_color, 1.f, 0.5f, 0.f);
	}
	else  {		
		SETCOLOR(br_in_health_box.fill_color, 1.f, 0.f, 0.f);
	}

	float box_offset = (6 - 6*(m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth > 1 ? 1 : m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth < 0 ? 0 : (m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth)))/2;
	graphics::drawRect(12.5-box_offset, 0.5, 6*(m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth > 1 ? 1 : m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth < 0 ? 0:(m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth)), 0.5, br_in_health_box);
	graphics::drawText(14, 0.7, 0.5, std::to_string(static_cast<int>((m_state->getPlayer()->getHealth() / m_state->getPlayer()->initHealth)*100)) + std::string(" %"), br);

	/*Vangelis - Add Game Over*/
	if (m_state->getPlayer()->getHealth() <= 0) {
		graphics::Brush br;
		graphics::stopMusic(500);
		br.texture = m_state->getAssetPath("game_over.png");
		br.fill_opacity = 1.f;
		br.outline_opacity = 0.f;
		graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, m_state->getCanvasWidth() / 2, 1, br);

		graphics::playSound("assets\\game-over.wav", 0.2f, false);
		m_state->getPlayer()->setActive(false);
		m_state->in_menu = true;
	}

	/*Vangelis - Add Game Over*/
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
