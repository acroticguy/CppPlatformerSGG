#pragma once
#include <string>
#include <graphics.h>
#include <math.h>
class GameState {

private:
	std::string m_asset_path = "assets\\";

	float m_canvas_width = 16.f;
	float m_canvas_height = 8.f;

	float m_background_width = 4.f * m_canvas_width;
	float m_background_height = 2.f * m_canvas_height;

	static GameState* m_unique_instance;

	class Player* m_player = 0;
	class Level* m_level = 0;

	GameState();

public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;

	bool m_global_collision = false;

	bool init();
	void draw();
	void update(float dt);

	bool in_menu = false;


	~GameState();
	static GameState* getInstance();
	std::string getAssetPath(std::string image);
	class Player* getPlayer() { return GameState::m_player; }

	float getCanvasWidth();
	float getCanvasHeight();

	float getBackgroundWidth();
	float getBackgroundHeight();

	bool isOnEdge();
};