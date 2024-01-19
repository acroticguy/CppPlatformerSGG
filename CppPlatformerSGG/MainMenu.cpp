#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu* MainMenu::getInstance()
{
	if (instance == nullptr) {
		instance = new MainMenu();
	}
	return instance;
}

void MainMenu::update(float dt)
{
}

void MainMenu::init()
{
}

void MainMenu::draw()
{
}
