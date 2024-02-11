#pragma once
#include <string>
#include <graphics.h>
#include <math.h>

#include "MainMenu.h"
#include "CharSelect.h"
#include "SetDiff.h"
#include "GameOver.h"
#include "Congratulations.h"
class GameState {

private:
	std::string m_asset_path = "assets\\";

	float m_canvas_width = 16.f;
	float m_canvas_height = 8.f;

	float m_background_width = 4.f * m_canvas_width;
	float m_background_height = 1.f * m_canvas_height;

	static GameState* m_unique_instance;

	class Player* m_player = 0;
	class Level* m_level = 0;
	class MainMenu* m_menu = 0;
	class CharSelect* char_sel = 0;
	class SetDiff* set_diff = 0;
	class GameOver* game_over = 0;
	class Congratulations* congratulations = 0;

	GameState();

public:
	const float cooldown = 0.25f;
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;

	bool init();
	void draw();
	void update(float dt);

	bool in_menu = true;
	bool in_char_sel = false;
	bool in_set_diff = false;
	bool in_game_over = false;
	bool in_congratulations = false;

	bool debug_mode = false;

	float difficulty_multiplier = 1.f;

	std::string p_name = "Mask Dude";


	~GameState();
	static GameState* getInstance();
	std::string getAssetPath(std::string image);
	class Player* getPlayer() { return GameState::m_player; }
	void initCong();

	float getCanvasWidth();
	float getCanvasHeight();

	float getBackgroundWidth();
	float getBackgroundHeight();

	bool isOnEdge();
};