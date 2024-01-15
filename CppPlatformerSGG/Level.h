#pragma once
#define SETCOLOR(c, r, g, b) {c[0]=r; c[1]=g; c[2]=b;}//Van

#include "GameObject.h"
#include "PowerUp.h"
#include "graphics.h"
#include "Enemy.h"//Van
#include <list>

class Level : public GameObject {
	graphics::Brush m_brush_background;

	float m_center_x = 8.0f;
	float m_center_y = 4.0f;

	float offset_x;
	float offset_y;

	float time;


	int enemies_killed = 0;//Van
	


	std::vector<GameObject*> m_static_objects;
	std::vector<PowerUp*> m_power_ups;
	std::list<GameObject*> m_dynamic_objects;
	std::list<Enemy*> m_Enemies;//Van

public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	Level(const std::string& name = "Level0");
	~Level();
};