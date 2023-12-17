#pragma once
#include "PowerUp.h"

class Apple : public PowerUp {
	int value = 400;
	std::string m_name = "Apple";
public:
	Apple(float x, float y, float w, float h) : PowerUp(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation() override;
};