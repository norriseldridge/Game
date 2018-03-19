#include "ai_base.h"
#include "sprite.h"
#include "combat_unit.h"

#ifndef ENEMY_H
#define ENEMY_H

namespace enemy {

	class Enemy : public combat::CombatUnit {
	private:
		sprite::Sprite* sprite;
		ai::AI* ai;
	public:
		Enemy(sprite::Sprite* sprite, Stat stat, ai::AI* ai, Color blood_color);
		Vector2 get_position();
		void update(Vector2 target);
		void render();
	};

	void register_enemy(Enemy* enemy);
	void update_enemies(Vector2 target);
	void render_enemies(SDL_Renderer* renderer);

}

#endif // !ENEMY_H
