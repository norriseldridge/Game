#include "game_time.h"

game_time::GameTime global_game_time;

Uint32 game_time::get_ticks() {
	return (Uint32)((global_game_time.current_tick - global_game_time.last_tick) * global_game_time.game_speed_mod);
}

void game_time::update() {
	global_game_time.last_tick = global_game_time.current_tick;
	global_game_time.current_tick = SDL_GetTicks();
}