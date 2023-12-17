#pragma once
#include "PowerUp.h"

class Bananas : public PowerUp {
	int value = 200;
	std::string m_name = "Bananas";
public:
	Bananas(float x, float y, float w, float h) : PowerUp(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation() override;
};