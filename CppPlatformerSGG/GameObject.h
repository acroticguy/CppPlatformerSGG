#pragma once
#include "GameState.h"
#include <string>
#include <math.h>
class GameObject
{
	static int m_next_id;
protected:
	class GameState* m_state;
	std::string m_name;
	int m_id = 0;
	float frame_count;
	int animation_cycle;
	bool m_active = true;

	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

public:
	GameObject(const std::string& name = "");
	virtual void update(float dt) {}
	virtual void init() {}
	virtual void draw() {}
	virtual ~GameObject() {}
	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
};