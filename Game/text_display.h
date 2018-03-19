#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "vector2.h"

#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

namespace ui {

	class TextDisplay
	{
	private:
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		TTF_Font* font;
		SDL_Color color;
		std::string message;
		Vector2 position;
		SDL_Rect* dest;
		void update_texture();
	public:
		TextDisplay(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string message, Vector2 position);
		~TextDisplay();
		void set_message(std::string message);
		void set_position(Vector2 position);
		void render();
	};

}

#endif // !TEXT_DISPLAY_H
