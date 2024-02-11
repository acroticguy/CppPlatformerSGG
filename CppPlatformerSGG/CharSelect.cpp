#include "CharSelect.h"


CharSelect* CharSelect::instance = nullptr;

CharSelect::CharSelect() : Menu()
{
}

CharSelect* CharSelect::getInstance()
{
	if (instance == nullptr) {
		instance = new CharSelect();
	}
	return instance;
}

void CharSelect::update(float dt)
{
	float delta_t = dt / 1000.f;

	curr_cd += delta_t;
	frame_count += animation_cycle * delta_t;

	bool cd_exceeded = (curr_cd > m_state->cooldown);

	if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
		if (cd_exceeded) {
			sel--;
			graphics::playSound("assets\\Menu\\gta hover.mp3", 0.2f, false);
			curr_selected = ((sel % buttons) + buttons) % buttons;
			curr_cd = 0;
		}
	}
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
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
			m_state->p_name = menu_selection[curr_selected];
			m_state->in_menu = true;
			m_state->in_char_sel = false;
		}
	}

	for (int i = 0; i < buttons; i++) {
		if (i == curr_selected) {
			m_brush_sel[i].outline_opacity = 1.f;
			animate(i);
		}
		else {
			m_brush_sel[i].outline_opacity = 0.f;
			m_brush_sel[i].texture = m_state->getAssetPath("Players\\" + menu_selection[i] + "\\Idle\\output_1.png");
		}
	}
}

void CharSelect::init()
{
	curr_cd = 0;
	curr_selected = ((sel % buttons) + buttons) % buttons;
	title = "CHARACTER SELECT";

	m_brush_menu.outline_opacity = 0.f;
	m_brush_menu.texture = m_state->getAssetPath("Menu\\menu_bg.png");

}

void CharSelect::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, m_state->getBackgroundWidth(), m_state->getBackgroundHeight(), m_brush_menu); // Background
	graphics::drawText(1, 1, 1, title, m_brush_menu); // Title

	for (int i = 0; i < buttons; i++) {
		graphics::drawRect(3 + (3 * i), m_state->getCanvasHeight() / 2, 2, 2, m_brush_sel[i]); // Draw all the buttons, with their respective brush
	}

	graphics::drawText(1, 6, 0.5, std::string("Currently Selecting: " + menu_selection[curr_selected]), m_brush_menu); // Title
}

void CharSelect::animate(int p) {
	int current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
	m_brush_sel[p].texture = m_state->getAssetPath("Players\\" + menu_selection[p] + "\\Idle\\output_") + std::to_string(current_frame) + ".png";
}