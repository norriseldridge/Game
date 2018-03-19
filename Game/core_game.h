#include <SDL.h>
#include "vector2.h"

#ifndef CORE_GAME_H
#define CORE_GAME_H

namespace core_game {

	void setup(SDL_Renderer* renderer);
	void main_loop(SDL_Renderer* renderer, const Uint8* keyboard_state, Uint32 mouse_state, Vector2 mouse_position);
	void cleanup();

}

#endif // !CORE_GAME_H

