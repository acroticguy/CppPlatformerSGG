#pragma once
#include "GameObject.h"
#include "graphics.h"

class Event : public GameObject {
	graphics::Brush m_brush_event;

public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	virtual void activation(float dt) {}
	Event(std::string & name) : GameObject(name){}
	Event() {}
	~Event();
};