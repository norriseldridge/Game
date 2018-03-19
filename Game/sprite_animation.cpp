#include "sprite_animation.h"

sprite::SpriteAnimation sprite::create_sprite_animation(Vector2 sprite_sheet_dimension, int columns, int rows, int frame_count, int* frame_indexes) {
	SpriteAnimation sprite_animation;
	
	int frame_width = (int)(sprite_sheet_dimension.x / columns);
	int frame_height = (int)(sprite_sheet_dimension.y / rows);

	for (int i = 0; i < frame_count; ++i) {
		int frame_index = frame_indexes[i];
		int row = (frame_index / columns);
		int column = frame_index - (row * columns);

		SDL_Rect frame;
		frame.w = frame_width;
		frame.h = frame_height;
		frame.x = column * frame_width;
		frame.y = row * frame_height;

		sprite_animation.frames.push_back(frame);
	}

	return sprite_animation;
}

void sprite::play_sprite_animation(SpriteAnimation& sprite_animation, SDL_Rect* src) {
	// should we bother going to the next frame?
	Uint32 now = SDL_GetTicks();
	if ((now - sprite_animation.last_tick) / 1000.0f > sprite_animation.frame_delay) {
		// update the last tick
		sprite_animation.last_tick = now;

		// next frame
		sprite_animation.current_frame++;

		// loop the animation
		if (sprite_animation.current_frame >= sprite_animation.frames.size()) {
			sprite_animation.current_frame = 0;
		}

		// assign the src to the current frame
		(*src) = sprite_animation.frames[sprite_animation.current_frame];
	}
}