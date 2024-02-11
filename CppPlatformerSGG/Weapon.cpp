#include "Weapon.h"
#include "Player.h"

void Weapon::update(float dt)
{

	activation(dt);
	GameObject::update(dt);

	float delta_t = dt / 1000.f;

	
	m_pos_x += direction * delta_t * speed;

	m_active = fabs(m_pos_x-start_point) <= 6 ;


}


void Weapon::init()
{
	direction = m_state->getPlayer()->getDirection();

	start_point = direction * (m_state->getPlayer()->m_width / 2)+ m_state->getPlayer()->m_pos_x;
	m_pos_y = m_state->getPlayer()->m_pos_y;

	m_pos_x = start_point;

	m_width = 1;
	m_height = 0.2;

	hitbox = new Box(m_pos_x, m_pos_y, m_width*3, m_height*1.5);


	frame_count = 0;
	m_brush_weapon.fill_opacity = 1.f;
	m_brush_weapon.outline_opacity = 0.f;
	m_brush_weapon.texture = m_state->getAssetPath("Weapon\\output_1.png"); 

	m_brush_hbox.fill_opacity = 0.f;
	m_brush_hbox.outline_opacity = 1.f;

}

void Weapon::draw()
{
	if (m_state->isOnEdge()) {
		if (m_state->m_global_offset_x - w / 2 > 0) {
			if (m_state->m_global_offset_y - h / 2 > 0) {
				graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight() / 2, m_width, m_height, m_brush_weapon);

				//Debug Frame:
				if (m_state->debug_mode) {
					graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight() / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
			else {
				graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_weapon);
				//HITBOX
				if (m_state->debug_mode) {
					graphics::drawRect(m_pos_x + m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
			
		}
		else {
			if (m_state->m_global_offset_y - h / 2 > 0) {
				graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight() / 2, m_width, m_height, m_brush_weapon);

				//Debug Frame:
				if (m_state->debug_mode) {
					graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->getBackgroundHeight() / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
			else {
				graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_weapon);

				//HITBOX
				if (m_state->debug_mode) {
					graphics::drawRect(m_pos_x + m_state->getCanvasWidth() - m_state->getBackgroundWidth() / 2, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
				}
			}
			
		}
	}
	else {
		if (m_state->m_global_offset_y - h / 2 > 0) {
			graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->getBackgroundHeight() / 2, m_width, m_height, m_brush_weapon);

			//Debug Frame:
			if (m_state->debug_mode) {
				graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->getBackgroundHeight() / 2, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
		else {
			graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush_weapon);

			//HITBOX
			if (m_state->debug_mode) {
				graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, hitbox->m_width, hitbox->m_height, m_brush_hbox);
			}
		}
		
	}

}

void Weapon::activation(float dt)
{
	int current_frame;

	float delta_t = dt / 100.f;
	if (is_firing) {
		if (fire_frame == 0.f) {
			graphics::playSound(m_state->getAssetPath("fire.wav"), 1.f, false);
		}

		fire_frame += 2.0 * fire_frame_sum * delta_t;
		current_frame = (static_cast<int>(floor(fire_frame)) % fire_frame_sum) ;

		if (current_frame >= fire_frame_sum) {
			is_firing = false;
			fire_frame = 0.f;
			m_active = false;
		}
	}
	else {
		frame_count += animation_cycle * delta_t; // In 1s we will have circled 1 animation
		current_frame = (static_cast<int>(floor(frame_count)) % animation_cycle) + 1;
	}


}
