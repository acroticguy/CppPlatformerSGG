#pragma once
#include "GameObject.h"
#include "graphics.h"
#include <list>

class Level : public GameObject {
	graphics::Brush m_brush_background;

	float m_center_x = 8.0f;
	float m_center_y = 4.0f;

	float offset_x;
	float offset_y;

	float time;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	Level(const std::string& name = "Level0");
	~Level();
};