#include "text_display.h"

ui::TextDisplay::TextDisplay(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string message, Vector2 position) {
	this->font = font;
	this->renderer = renderer;
	this->message = message;
	this->color = color;
	this->position = position;
	this->dest = new SDL_Rect();
	update_texture();
}

ui::TextDisplay::~TextDisplay() {
	SDL_DestroyTexture(texture);
}

void ui::TextDisplay::update_texture() {
	SDL_Surface* temp_surface = TTF_RenderText_Solid(font, message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
	dest->w = temp_surface->w;
	dest->h = temp_surface->h;
	SDL_FreeSurface(temp_surface);
	temp_surface = NULL;
}

void ui::TextDisplay::set_message(std::string message) {
	this->message = message;
	update_texture();
}

void ui::TextDisplay::set_position(Vector2 position) {
	this->position = position;
}

void ui::TextDisplay::render() {
	dest->x = (int)position.x;
	dest->y = (int)position.y;
	SDL_RenderCopy(renderer, texture, NULL, dest);
}