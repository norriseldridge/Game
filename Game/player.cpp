#include "player.h"
#include "math_util.h"
#include "game_time.h"
#include "combat.h"

Player::Player(SDL_Renderer* renderer, PlayerData player_data) : CombatUnit(player_data.stat, Color(255, 0, 0, 255)) {
	// set the position
	this->position = player_data.position;

	// set up collision
	collider = new collision::CircleCollider(position, 25.0f);

	// set up player state and data
	player_state = PlayerState::idle_state;
	direction = Direction::down;
	speed = player_data.stat.speed;

	// set up visuals
	sprite = new sprite::Sprite(renderer, "assets/images/player.png", position, Vector2(50, 50));

	// walking animations
	sprite->add_animation("walk_up", sprite::create_sprite_animation(sprite->get_sprite_texture_dimensions(), 4, 4, 4, new int[4]{ 12, 13, 14, 15 }));
	sprite->add_animation("walk_down", sprite::create_sprite_animation(sprite->get_sprite_texture_dimensions(), 4, 4, 4, new int[4]{ 0, 1, 2, 3 }));
	sprite->add_animation("walk_left", sprite::create_sprite_animation(sprite->get_sprite_texture_dimensions(), 4, 4, 4, new int[4]{ 8, 9, 10, 11 }));
	sprite->add_animation("walk_right", sprite::create_sprite_animation(sprite->get_sprite_texture_dimensions(), 4, 4, 4, new int[4]{ 4, 5, 6, 7 }));

	// idle animations
	sprite->add_animation("idle_up", sprite::create_sprite_animation(sprite->get_sprite_texture_dimensions(), 4, 4, 1, new int[1]{ 13 }));
	sprite->add_animation("idle_down", sprite::create_sprite_animation(sprite->get_sprite_texture_dimensions(), 4, 4, 1, new int[1]{ 1 }));
	sprite->add_animation("idle_left", sprite::create_sprite_animation(sprite->get_sprite_texture_dimensions(), 4, 4, 1, new int[1]{ 8 }));
	sprite->add_animation("idle_right", sprite::create_sprite_animation(sprite->get_sprite_texture_dimensions(), 4, 4, 1, new int[1]{ 5 }));
}

void Player::set_position(Vector2 position) {
	this->position = position;
	sprite->position = position;
	collider->position = position;
}

Vector2 Player::get_position() {
	return position;
}

collision::Collider* Player::get_collider() {
	return collider;
}

void Player::update(const Uint8* keyboard_state) {
	move(keyboard_state);
	attack(keyboard_state);
	play_state_animation();
}

void Player::move(const Uint8* keyboard_state) {
	// default idle state
	player_state = PlayerState::idle_state;

	// movement vector
	Vector2 movement;
	if (keyboard_state[SDL_SCANCODE_W]) {
		movement -= Vector2(0, 1);
		player_state = PlayerState::walking;
		direction = Direction::up;
	}

	if (keyboard_state[SDL_SCANCODE_S]) {
		movement += Vector2(0, 1);
		player_state = PlayerState::walking;
		direction = Direction::down;
	}

	if (keyboard_state[SDL_SCANCODE_A]) {
		movement -= Vector2(1, 0);
		player_state = PlayerState::walking;
		direction = Direction::left;
	}

	if (keyboard_state[SDL_SCANCODE_D]) {
		movement += Vector2(1, 0);
		player_state = PlayerState::walking;
		direction = Direction::right;
	}

	// update position of visuals and collider
	float game_speed = speed * game_time::get_ticks() / 1000.0f;
	position += calculate_unit_vector(movement) * game_speed; // move the combat unit's position
	sprite->position = position;
	collider->position = position;
}

void Player::attack(const Uint8* keyboard_state) {
	if (keyboard_state[SDL_SCANCODE_SPACE]) {
		// TODO are we able to attack? is an attack ready?
		combat::dispatch_attack(this);
	}
}

void Player::play_state_animation() {
	std::string current_animation = "";

	// base animation
	switch (player_state)
	{
		case PlayerState::walking:
			current_animation += "walk";
			break;

		case PlayerState::idle_state:
		default:
			current_animation += "idle";
			break;
	}

	// direction animation
	switch (direction) {
		case Direction::up:
			current_animation += "_up";
			break;

		case Direction::down:
			current_animation += "_down";
			break;

		case Direction::left:
			current_animation += "_left";
			break;

		case Direction::right:
			current_animation += "_right";
			break;
	}

	// play the animation
	sprite->play_animation(current_animation);
}

void Player::render() {
	sprite->render_with_offset(Camera::get_instance()->get_viewport_offset());
}