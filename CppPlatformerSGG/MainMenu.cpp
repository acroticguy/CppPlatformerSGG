#include "MainMenu.h"

MainMenu* MainMenu::instance = nullptr;

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
	title = "MAIN MENU";
}

void MainMenu::draw()
{

}
