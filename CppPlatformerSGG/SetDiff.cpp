#include "SetDiff.h"

SetDiff* SetDiff::instance = nullptr;

SetDiff::SetDiff() : Menu()
{
}

SetDiff* SetDiff::getInstance()
{
	if (instance == nullptr) {
		instance = new SetDiff();
	}
	return instance;
}

void SetDiff::update(float dt)
{
	float delta_t = dt / 1000.f;

	curr_cd += delta_t;

	bool cd_exceeded = (curr_cd > m_state->cooldown);

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
				//PLAY
				m_state->difficulty_multiplier = 1.f;
				break;
			case 1:
				//CHAR SELECT
				m_state->difficulty_multiplier = 2.f;
				break;
			case 2:
				//HARD
				m_state->difficulty_multiplier = 3.f;
				break;
			case 3:
				//IMPOSSIBLE
				m_state->difficulty_multiplier = 5.f;
				break;
			}
			m_state->in_menu = true;
			m_state->in_set_diff = false;
		}
	}
}

void SetDiff::init()
{
	curr_cd = 0;
	curr_selected = ((sel % buttons) + buttons) % buttons;
	title = "SELECT DIFFICULTY";

	m_brush_menu.outline_opacity = 0.f;
	m_brush_menu.texture = m_state->getAssetPath("Menu\\menu_bg.png");

	m_brush_arrow.outline_opacity = 0.f;
	m_brush_arrow.texture = m_state->getAssetPath("Menu\\arrow.png");

}

void SetDiff::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_menu); // Background
	graphics::drawText(1, 1, 1, title, m_brush_menu); // Title

	for (int i = 0; i < buttons; i++) {
		graphics::drawText(1, i + 2.5, 0.5, menu_selection[i], m_brush_sel); // Draw all the buttons, with their respective brush
	}

	//graphics::drawText(5, 1, 0.5, std::to_string(curr_selected), m_brush_sel);

	graphics::drawRect(0.6f, curr_selected + 2.3, -0.5, 0.25, m_brush_arrow);

	/*graphics::drawText(1, 2.5, 0.5, std::string("PLAY"), m_brush_menu);
	graphics::drawText(1, 3.5, 0.5, std::string("SELECT CHARACTER"), m_brush_menu);
	graphics::drawText(1, 4.5, 0.5, std::string("QUIT"), m_brush_menu);*/
}