#pragma once
#include "PowerUp.h"

class Kiwi : public PowerUp {
	int value = 400;
	int health_given = 15;
	std::string m_name = "Kiwi";
public:
	Kiwi(float x, float y, float w, float h) : PowerUp(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation() override;
	std::string getName() const override { return m_name; };
};