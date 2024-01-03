#pragma once
#include "PowerUp.h"

class Melon : public PowerUp {
	int value = 400;
	std::string m_name = "Melon";
public:
	Melon(float x, float y, float w, float h) : PowerUp(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation() override;
	std::string getName() const override { return m_name; };
};