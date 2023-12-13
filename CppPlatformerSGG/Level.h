#pragma once
#include "GameObject.h"
#include "graphics.h"
#include <list>

class Level : public GameObject {
	graphics::Brush m_brush_background;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	float w;
	float h;

	float offset_x;
	float offset_y;

	bool is_on_edge = false;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	Level(const std::string& name = "Level0");
	~Level();
};