#pragma once
#include "PowerUp.h"

class Orange : public PowerUp {
	int value = 400;
	int health_given = 15;
	std::string m_name = "Orange";
public:
	Orange(float x, float y, float w, float h) : PowerUp(x, y, w, h) {
	}
	void update(float dt) override;
	void init() override;
	void draw() override;
	void activation(float dt) override;
	int getHeal() const override { return health_given; };
	int getScore() const override { return value; };
	std::string getName() const override { return m_name; };
};