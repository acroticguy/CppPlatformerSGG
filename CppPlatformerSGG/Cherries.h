#pragma once
#include "PowerUp.h"

class Cherries : public PowerUp {
	int value = 600;
	int health_given = 25;
	std::string m_name = "Cherries";
public:
	Cherries(float x, float y, float w, float h) : PowerUp(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation() override;
	std::string getName() const override { return m_name; };
};