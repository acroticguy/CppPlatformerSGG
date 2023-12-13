#pragma once
#include <string>
#include <graphics.h>
class GameState {

private:
	std::string m_asset_path = "assets\\";

	float m_canvas_width = 16.f;
	float m_canvas_height = 8.f;

	static GameState* m_unique_instance;

	class Player* m_player = 0;
	class Level* m_level = 0;

	GameState();

public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;

	bool init();
	void draw();
	void update(float dt);


	~GameState();
	static GameState* getInstance();
	std::string getAssetPath(std::string image);
	class Player* getPlayer() { return GameState::m_player; }

	float getCanvasWidth();
	float getCanvasHeight();
};