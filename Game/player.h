#include "sprite.h"
#include "sprite_animation.h"
#include "player_data.h"
#include "player_state.h"
#include "direction.h"
#include "circle_collider.h"
#include "combat_unit.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public combat::CombatUnit {
private:
	collision::CircleCollider* collider;
	float speed;
	sprite::Sprite* sprite;
	PlayerState player_state;
	Direction direction;
	void move(const Uint8* keyboard_state);
	void attack(const Uint8* keyboard_state);
	void play_state_animation();
public:
	Player(SDL_Renderer* renderer, PlayerData player_data);
	void set_position(Vector2 position);
	Vector2 get_position();
	collision::Collider* get_collider();
	void update(const Uint8* keyboard_state);
	void render();
};

#endif // !PLAYER_H