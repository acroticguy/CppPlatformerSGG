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
	
	float delta_t = dt / 1000.f;

	//Add countdown for player's health
	m_state->getPlayer()->setHealth(std::max(0.f, m_state->getPlayer()->getHealth() - delta_t));

	if (m_state->getPlayer()->is_dead) {
		if (secs_dead == 0.f) {
			m_state->getPlayer()->setActive(false);
			graphics::stopMusic(500);
			graphics::playSound("assets\\game-over.wav", 0.2f, false);
		}
		game_over_pos_offset += delta_t;
		secs_dead += delta_t;

		if (secs_dead > 3.f) {
			m_state->in_game_over = true;
		}
	}

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

		time += delta_t * m_state->difficulty_multiplier;
		int current_sec = static_cast<int>(floor(time));

		if (current_sec % 4 == 3 && !enemy_spawned) {
			//Enemy* opp = new Enemy(m_state->getPlayer()->m_pos_y);
			Enemy* opp = new Enemy(1,m_state->getPlayer()->m_pos_y,1.5,1,"Bat");//Van
			opp->init();
			m_Enemies.push_back(opp);
			enemy_spawned = true;
		}

		if (current_sec % 4 != 3) { enemy_spawned = false; }
		
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
					if (collision_offset < 0.f) {
						m_state->getPlayer()->setVerticalV(0.f);
						m_state->getPlayer()->m_pos_y -= delta_t * m_state->getPlayer()->jump_v * 5;
						p_opp->setKilled(true);//Van
					}
				}

				if (m_state->getPlayer()->hitbox->intersectSideways(*p_opp->hitbox)) {
					m_state->getPlayer()->is_hit = true;

					// Don't try to give negative HP. If HP left is less than 0.5, just go to 0.
					m_state->getPlayer()->setHealth(std::max(0.f, m_state->getPlayer()->getHealth() - 0.5f));
				}
				++it;  // Move to the next element.
			}
			else {
				it = m_Enemies.erase(it);  // Erase returns the iterator to the next element.
				delete p_opp;
			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_SPACE) || graphics::getKeyState(graphics::SCANCODE_RETURN)) {
			//Weapon* wpn = new Weapon(m_state->getPlayer()->m_pos_x, m_state->getPlayer()->m_pos_y, 0.2, 0.2);
			Weapon* wpn = new Weapon();
			wpn->init();
			m_Weapons.push_back(wpn);
			wpn->is_firing = true;

		}

		for (auto it = m_Weapons.begin(); it != m_Weapons.end();) {
			auto p_wpn = *it;  // Get the pointer from the iterator.
			if (p_wpn->isActive()) {
				p_wpn->update(dt);
				for (auto ix = m_Enemies.begin(); ix != m_Enemies.end();) {
					auto p_opp = *ix;

					if (p_wpn->hitbox->intersect(*p_opp->hitbox)) {
						p_opp->setKilled(true);//Van
					}


					if (p_opp->isActive()) {
						if (p_opp->is_killed) {
							++ix;
							continue;
						}
						//    if (p_wpn->hitbox->intersect(*p_opp->hitbox)) {
							//    p_opp->setKilled(true);//Van
						//}
					}
					else {
						ix = m_Enemies.erase(ix);  // Erase returns the iterator to the next element.
						delete p_opp;
					}
					if (ix != m_Enemies.end()) {//Van after search in web
						++ix;
					}
				}
			}

			if (p_wpn->is_firing) {//moved down
				++it;  // Move to the next element.
			}
			else {
				it = m_Weapons.erase(it);  // Erase returns the iterator to the next element.
				delete p_wpn;
			}
		}
		
	}
	
	GameObject::update(dt);
}

void Level::init()
{
	m_static_objects.clear();
	m_power_ups.clear();
	m_dynamic_objects.clear();
	m_Enemies.clear();
	m_Weapons.clear();
	time = 0;
	m_brush_background.outline_opacity = 0.f;
	m_brush_background.texture = m_state->getAssetPath("bkg_swamp2.png");

	const int min_platform_distance = 2; // Minimum distance between blocks
	const int max_platform_distance = 4; // Maximum distance between blocks

	const int min_y = 0;
	const int max_y = m_state->getBackgroundHeight() / 2 - 1;

	const int max_x = m_state->getBackgroundWidth() / 2 - 5; // We will later manually add the last platform, in order to add the exit.
	int next_platform = -(m_state->getBackgroundWidth() / 2 - 2);
	int y_pos = 3;

	Wall* platform;
	PowerUp* pwrup;
	while (next_platform + 2 < max_x) {
		int num = rand();
		y_pos = num % 2 == 0 ? std::min(max_y, y_pos + 1) : std::max(min_y, y_pos - 1);
		platform = new Wall(next_platform, next_platform + 2, y_pos, y_pos, "Grass");

		// Pick Fruit
		switch (getPowerUp()) {
		case 0:
			//Empty Platform
			break;
		case 1:
			pwrup = new Apple(next_platform + 1, y_pos - 1, 1, 1);
			m_power_ups.push_back(pwrup);
			break;
		case 2:
			pwrup = new Bananas(next_platform + 1, y_pos - 1, 1, 1);
			m_power_ups.push_back(pwrup);
			break;
		case 3:
			pwrup = new Cherries(next_platform + 1, y_pos - 1, 1, 1);
			m_power_ups.push_back(pwrup);
			break;
		case 4:
			pwrup = new Kiwi(next_platform + 1, y_pos - 1, 1, 1);
			m_power_ups.push_back(pwrup);
			break;
		case 5:
			pwrup = new Melon(next_platform + 1, y_pos - 1, 1, 1);
			m_power_ups.push_back(pwrup);
			break;
		case 6:
			pwrup = new Orange(next_platform + 1, y_pos - 1, 1, 1);
			m_power_ups.push_back(pwrup);
			break;
		case 7:
			pwrup = new Pineapple(next_platform + 1, y_pos - 1, 1, 1);
			m_power_ups.push_back(pwrup);
			break;
		case 8:
			pwrup = new Strawberry(next_platform + 1, y_pos - 1, 1, 1);
			m_power_ups.push_back(pwrup);
			break;
		}

		int selection = num % (max_platform_distance - min_platform_distance + 1) + 2;
		next_platform += selection;
		m_static_objects.push_back(platform);
	}

	int num = rand();
	y_pos = num % 2 == 0 ? std::min(max_y, y_pos + 1) : std::max(min_y, y_pos - 1);
	platform = new Wall(max_x, max_x + 2, y_pos, y_pos, "Grass");
	m_static_objects.push_back(platform);
	End* fin = new End(max_x + 2, y_pos - 1, 1, 1);

	Wall* ground = new Wall(-m_state->getBackgroundWidth() / 2, m_state->getBackgroundWidth() / 2, 4, 4, "Grass2");
	Wall* wall_left = new Wall(-(m_state->getBackgroundWidth() / 2 - 0.5f), -(m_state->getBackgroundWidth() / 2 - 0.5f), -4, m_state->getBackgroundHeight() / 2 - 1, "Wall");
	Wall* wall_right = new Wall((m_state->getBackgroundWidth() / 2 - 0.5f), (m_state->getBackgroundWidth() / 2 - 0.5f), -4, m_state->getBackgroundHeight() / 2 - 1, "Wall");
	
	m_static_objects.push_back(ground);
	m_static_objects.push_back(wall_left);
	m_static_objects.push_back(wall_right);
	m_static_objects.push_back(fin);
	
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
			if (offset_y > 0) {
				graphics::drawRect(m_state->getBackgroundWidth() / 2, m_state->getBackgroundHeight() / 2, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
			} else {
				graphics::drawRect(m_state->getBackgroundWidth() / 2, m_state->m_global_offset_y, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
			}
		} else {
			if (offset_y > 0) {
				graphics::drawRect(w - m_state->getBackgroundWidth() / 2, m_state->getBackgroundHeight() / 2, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
			} else {
				graphics::drawRect(w - m_state->getBackgroundWidth() / 2, m_state->m_global_offset_y, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
			}
		}
	} else {
		if (offset_y > 0) {
			graphics::drawRect(m_state->m_global_offset_x, m_state->getBackgroundHeight() / 2, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
		}
		else {
			graphics::drawRect(m_state->m_global_offset_x, m_state->m_global_offset_y, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_background);
		}
		
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
	for (auto p_wpn : m_Weapons) {
		if (p_wpn) {
			if (p_wpn->isActive()) { p_wpn->draw(); }
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
	

	if (m_state->getPlayer()->is_dead) { 
		graphics::Brush br;
		br.texture = m_state->getAssetPath("game_over.png");
		br.fill_opacity = 1.f;
		br.outline_opacity = 0.f;

		graphics::drawRect(m_state->getCanvasWidth() / 2, std::min(m_state->getCanvasHeight() / 4, game_over_pos_offset), m_state->getCanvasWidth() / 2, 1, br);
	}
}

int Level::getPowerUp()
{
	return rand() % 9;
}

Level::Level(const std::string& name) {}

Level::~Level()
{
	for (auto p_gob : m_static_objects) {
		if (p_gob) {
			delete p_gob;
		}
	}
	for (auto p_pwr : m_power_ups) {
		if (p_pwr) {
			delete p_pwr;
		}
	}
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) {
			delete p_gob;
		}
	}
	for (auto p_opp : m_Enemies) {
		if (p_opp) {
			delete p_opp;
		}
	}
	for (auto p_wpn : m_Weapons) {
		if (p_wpn) {
			delete p_wpn;
		}
	}
}
