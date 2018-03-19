#include <SDL.h>

#ifndef GAME_TIME_H
#define GAME_TIME_H

namespace game_time {

	struct GameTime {
		Uint32 last_tick;
		Uint32 current_tick;
		float game_speed_mod = 1.0f;
	};

	Uint32 get_ticks();
	void update();

}

#endif // !GAME_TIME_H