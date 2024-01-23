#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include "MainMenu.h"
#include "graphics.h"

GameState* GameState::m_unique_instance = nullptr;

bool GameState::init()
{
	graphics::setFont(this->getAssetPath("orange juice 2.0.ttf"));

	if (in_menu) {
		m_menu = MainMenu::getInstance();
		m_menu->init();
	}
	else if (in_char_sel) {
		char_sel->init();
	}
	else {
		m_level = new Level("Level0");
		m_level->init();

		m_player = new Player(p_name);
		m_player->init();
	}

	graphics::preloadBitmaps(m_asset_path); //Load all PNGs in the memory
	return true;
}

void GameState::draw()
{
	if (in_menu) {
		if (!m_menu) { 
			m_menu = MainMenu::getInstance();
			m_menu->init();
		}
		m_menu->draw();
	}
	else if (in_char_sel) {
		if (!char_sel) {
			char_sel = CharSelect::getInstance();
			char_sel->init();
		}
		char_sel->draw();
	}
	else { 
		if (!m_level) { 
			m_level = new Level("Level0");
			m_level->init();

			m_player = new Player(p_name);
			m_player->init();
		}
		m_level->draw();
	}
}

void GameState::update(float dt)
{
	if (dt > 500) {
		return;
	}
	if (in_menu) {
		if (!m_menu) {
			m_menu = MainMenu::getInstance();
			m_menu->init();
		}
		m_menu->update(dt);
	}
	else if (in_char_sel) {
		if (!char_sel) {
			char_sel = CharSelect::getInstance();
			char_sel->init();
		}
		char_sel->update(dt);
	}
	else {
		if (!m_level) {
			m_level = new Level("Level0");
			m_level->init();

			m_player = new Player(p_name);
			m_player->init();
		}
		m_level->update(dt);
	}
}

GameState * GameState::getInstance()
{
	if (m_unique_instance == nullptr) {
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

std::string GameState::getAssetPath(std::string str)
{
	return m_asset_path + str;
}

float GameState::getCanvasWidth()
{
	return m_canvas_width;
}

float GameState::getCanvasHeight()
{
	return m_canvas_height;
}

float GameState::getBackgroundWidth()
{
	return m_background_width;
}

float GameState::getBackgroundHeight()
{
	return m_background_height;
}

bool GameState::isOnEdge()
{
	return fabs(m_global_offset_x - m_canvas_width/2) >= m_background_width/2 - m_canvas_width/2;
}

GameState::GameState() {

}

GameState::~GameState()
{
	if (m_player) {
		delete m_player;
	}
	if (m_level) {
		delete m_level;
	}
}