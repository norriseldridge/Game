#include "core_game.h"
#include "collision_handling.h"
#include "map.h"
#include "player.h"
#include "game_time.h"
#include "game_state.h"
#include "enemy.h"
#include "ai_melee.h"
#include "particles.h"
#include "ui.h"
#include "math_util.h"
#include "pathfinding.h"
#include <list>

map::Map* current_map;
Player* player;
std::list<pathfinding::PathNode*> path;

pathfinding::PathNode* start_path = nullptr;
pathfinding::PathNode* end_path = nullptr;

void core_game::setup(SDL_Renderer* renderer) {
	
	current_map = new map::Map(renderer, "data/maps/test.json");
	start_path = current_map->get_path_nodes().front();
	end_path = current_map->get_path_nodes().back();

	PlayerData player_data = load_player_data("data/save_data/player_data.json");
	player = new Player(renderer, player_data);

	// set up dummy enemies
	for (int i = 0; i < 3; ++i) {
		// enemy stats
		Stat stat;
		stat.attack = 10;
		stat.health = 50;
		stat.max_health = 50;
		stat.speed = 15.0f;
		stat.attack_range = 45.0f;

		// enemy ai
		ai::AIRangeData range_data;
		range_data.active_range = 200.0f;
		range_data.inactive_range = 175.0f;
		range_data.attack_range = stat.attack_range;
		ai::AIMelee* melee = new ai::AIMelee(range_data, 2.0f);

		// enemy visuals
		sprite::Sprite* sprite = new sprite::Sprite(renderer, "assets/images/enemy.png", Vector2(150, 0), Vector2(50, 50));
		sprite->position += Vector2(i * 75, i * 15);
		enemy::register_enemy(new enemy::Enemy(sprite, stat, (ai::AI*)melee, Color(0, 235, 0, 255)));
	}
}

void core_game::main_loop(SDL_Renderer* renderer, const Uint8* keyboard_state, Uint32 mouse_state, Vector2 mouse_position) {
	// update game time
	game_time::update();

	// handle map collision
	collision::handle_collisions(current_map->get_collision_tiles(), player->get_collider(), &player->position);

	// update player
	player->update(keyboard_state);

	// update enemies
	enemy::update_enemies(player->get_position());

	// update particles
	particles::update_blood_particles(renderer);

	// update camera position
	Camera::get_instance()->set_position(player->get_position());

	// rendering
	// "in game" objects
	current_map->render();

	// set new "start"
	start_path = current_map->get_path_node_at_position(player->get_position());

	// set new end
	if (keyboard_state[SDL_SCANCODE_1]) {
		// set end
		end_path = current_map->get_path_node_at_position(player->get_position());
	}

	// render the path
	SDL_Rect* rect = new SDL_Rect();
	path = pathfinding::get_path(start_path, end_path);
	for (pathfinding::PathNode* node : path) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		rect->w = 10;
		rect->h = 10;
		rect->x = node->x - Camera::get_instance()->get_viewport_offset().x - 5;
		rect->y = node->y - Camera::get_instance()->get_viewport_offset().y - 5;
		SDL_RenderFillRect(renderer, rect);
	}
	delete rect;
	rect = nullptr;

	player->render();
	enemy::render_enemies(renderer);

	// particles
	particles::render_blood_particles(renderer);

	// ui
	ui::render_health_bar(renderer, player->get_stat().health, player->get_stat().max_health, Vector2(5, 5), Vector2(150, 40));
}

void core_game::cleanup() {
	delete player;
	delete current_map;
	ui::clean_up_fonts();
}