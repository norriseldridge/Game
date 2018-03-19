#include <SDL.h>
#include <vector>
#include "vector2.h"

#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

namespace sprite {

	struct SpriteAnimation
	{
		unsigned int current_frame = 0;
		std::vector<SDL_Rect> frames;
		Uint32 last_tick = 0;
		float frame_delay = 0.2f;
	};

	SpriteAnimation create_sprite_animation(Vector2 sprite_sheet_dimension, int columns, int rows, int frame_count, int* frame_indexes);
	void play_sprite_animation(SpriteAnimation& sprite_animation, SDL_Rect* src);

}

#endif // !SPRITE_ANIMATION_H
