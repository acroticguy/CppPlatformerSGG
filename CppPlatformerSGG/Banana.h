#pragma once
#include "PowerUp.h"

class Banana : public PowerUp {
	int value = 200;
	std::string m_name = "Banana";
public:
	Banana(float x, float y, float w, float h) : PowerUp(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation() override;
};