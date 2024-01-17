#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include "graphics.h"

GameState* GameState::m_unique_instance = nullptr;

bool GameState::init()
{
	m_level = new Level("Level0");
	m_level->init();

	m_player = new Player("Mask Dude");
	m_player->init();

	graphics::preloadBitmaps(m_asset_path); //Load all PNGs in the memory
	return true;
}

void GameState::draw()
{
	if (!m_level) {
		return;
	}
	if (!in_menu) { m_level->draw(); }
}

void GameState::update(float dt)
{
	if (!m_level || dt > 500) {
		return;
	}
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);
	if (mouse.button_left_released)
	{
		graphics::playSound("assets\\hit1.wav", 1.0f, false);
	}
	if (in_menu) {

	} else { m_level->update(dt); }
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