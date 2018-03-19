#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "camera.h"
#include "image_util.h"
#include "sprite_animation.h"
#include "vector2.h"

#ifndef SPRITE_H
#define SPRITE_H

namespace sprite {

	class Sprite {
	private:
		std::map<std::string, SpriteAnimation> sprite_animations;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		SDL_Rect* src;
		SDL_Rect* dest;

	public:
		Vector2 position;
		Sprite(SDL_Renderer* renderer, const char* file, Vector2 position, Vector2 size);
		~Sprite();
		Vector2 get_sprite_texture_dimensions();
		void add_animation(std::string animation_name, SpriteAnimation sprite_animation);
		void play_animation(std::string animation_name);
		void render();
		void render_with_offset(Vector2 offset);
	};

	void render_sprite_with_camera(Sprite* sprite);

}

#endif // !SPRITE_H

