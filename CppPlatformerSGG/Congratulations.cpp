#include "Congratulations.h"
#include "Player.h" // We print player's score on the game over page.

Congratulations* Congratulations::instance = nullptr;

Congratulations::Congratulations() : Menu()
{
}

Congratulations* Congratulations::getInstance()
{
	if (instance == nullptr) {
		instance = new Congratulations();
	}
	return instance;
}

void Congratulations::update(float dt)
{
	float delta_t = dt / 1000.f;

	curr_cd += delta_t;

	bool cd_exceeded = (curr_cd > cooldown);

	if (graphics::getKeyState(graphics::SCANCODE_UP)) {
		if (cd_exceeded) {
			sel--;
			graphics::playSound("assets\\Menu\\gta hover.mp3", 0.2f, false);
			curr_selected = ((sel % buttons) + buttons) % buttons;
			curr_cd = 0;
		}
	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		if (cd_exceeded) {
			sel++;
			graphics::playSound("assets\\Menu\\gta hover.mp3", 0.2f, false);
			curr_selected = ((sel % buttons) + buttons) % buttons;
			curr_cd = 0;
		}
	}
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		if (cd_exceeded) {
			graphics::playSound("assets\\Menu\\clink.wav", 0.2f, false);

			//NAVIGATE TO NEXT PAGE
			curr_cd = 0;
			switch (curr_selected) {
			case 0:
				//PLAY AGAIN
				m_state->in_congratulations = false;
				m_state->init();
				break;
			case 1:
				//MAIN MENU
				m_state->in_menu = true;
				m_state->in_congratulations = false;
				break;
			}
		}
	}
}

void Congratulations::init()
{
	curr_cd = 0;
	curr_selected = ((sel % buttons) + buttons) % buttons;
	title = "YOU MADE IT!";

	graphics::playSound(m_state->getAssetPath("Menu\\applause_2.wav"), 1.f, false);

	m_brush_menu.outline_opacity = 0.f;
	m_brush_menu.texture = m_state->getAssetPath("Menu\\menu_bg.png");

	m_brush_arrow.outline_opacity = 0.f;
	m_brush_arrow.texture = m_state->getAssetPath("Menu\\arrow.png");

}

void Congratulations::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_menu); // Background
	graphics::drawText(1, 1, 1, title, m_brush_menu); // Title

	graphics::drawText(8, 3, 1, std::string("SCORE: " + std::to_string(m_state->getPlayer()->score)), m_brush_menu);

	for (int i = 0; i < buttons; i++) {
		graphics::drawText(1, i + 2.5, 0.5, menu_selection[i], m_brush_sel); // Draw all the buttons, with their respective brush
	}

	graphics::drawRect(0.6f, curr_selected + 2.3, -0.5, 0.25, m_brush_arrow);
}
