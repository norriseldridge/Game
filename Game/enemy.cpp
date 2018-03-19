#include "enemy.h"
#include "camera.h"
#include "health_bar.h"
#include <list>

enemy::Enemy::Enemy(sprite::Sprite* sprite, Stat stat, ai::AI* ai, Color blood_color) : CombatUnit(stat, blood_color) {
	this->position = sprite->position;
	this->sprite = sprite;
	this->ai = ai;
	this->ai->set_combat_unit(this);
}

Vector2 enemy::Enemy::get_position() {
	return position;
}

void enemy::Enemy::update(Vector2 target) {
	// update the ai's target
	ai->set_target(target);
	
	// update the ai's position
	ai->set_position(position);

	// let the ai figure out what it is supposed to do
	ai->run_ai();

	// update our position from the ai
	position = ai->get_position();
	sprite->position = position;
}

void enemy::Enemy::render() {
	sprite->render_with_offset(Camera::get_instance()->get_viewport_offset());
}

std::list<enemy::Enemy*> active_enemies;
void enemy::register_enemy(Enemy* enemy) {
	active_enemies.push_back(enemy);
}

void enemy::update_enemies(Vector2 target) {
	for (Enemy* enemy : active_enemies) {
		enemy->update(target);
	}

	active_enemies.remove_if([](Enemy* enemy) {
		if (enemy->get_stat().health <= 0.0f) {
			delete enemy;
			return true;
		}

		return false; 
	});
}

void enemy::render_enemies(SDL_Renderer* renderer) {
	for (Enemy* enemy : active_enemies) {
		enemy->render();
		ui::render_health_bar(renderer, 
			enemy->get_stat().health, enemy->get_stat().max_health,
			enemy->get_position() - Camera::get_instance()->get_viewport_offset() - Vector2(30, 50),
			Vector2(60, 20));
	}
}