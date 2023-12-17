#pragma once
#include "PowerUp.h"

class Cherries : public PowerUp {
	int value = 600;
	std::string m_name = "Cherries";
public:
	Cherries(float x, float y, float w, float h) : PowerUp(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation() override;
};