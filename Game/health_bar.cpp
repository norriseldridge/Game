#include "health_bar.h"
#include <cstdio>

// create a rect to work with
SDL_Rect* ui_health_bar_rect = new SDL_Rect();

void ui::render_health_bar(SDL_Renderer* renderer, float health, float max_health, Vector2 position, Vector2 size) {
	// define a border size
	int border_width = 3;
	int shadow_height = 6;
	int glass_pixel = (int)(size.y * 0.1);

	// get the "health width"
	float health_scale = (health / max_health);
	if (health_scale > 1.0f) {
		health_scale = 1.0f;
	}
	if (health_scale < 0.0f) {
		health_scale = 0.0f;
	}
	float health_width = (size.x - border_width * 2) * health_scale;

	// draw the "border"
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // dark gray color
	ui_health_bar_rect->w = (int)size.x;
	ui_health_bar_rect->h = (int)size.y;
	ui_health_bar_rect->x = (int)position.x;
	ui_health_bar_rect->y = (int)position.y;
	SDL_RenderFillRect(renderer, ui_health_bar_rect);

	// draw the "fill inner"
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // dark gray color
	ui_health_bar_rect->w = (int)(size.x - (border_width * 2));
	ui_health_bar_rect->h = (int)(size.y - (border_width * 2));
	ui_health_bar_rect->x = (int)(position.x + border_width);
	ui_health_bar_rect->y = (int)(position.y + border_width);
	SDL_RenderFillRect(renderer, ui_health_bar_rect);

	// draw the "fill"
	SDL_SetRenderDrawColor(renderer, 150, 30, 30, 255); // dark red color
	ui_health_bar_rect->w = (int)health_width;
	ui_health_bar_rect->h = (int)(size.y - (border_width * 2));
	ui_health_bar_rect->x = (int)(position.x + border_width);
	ui_health_bar_rect->y = (int)(position.y + border_width);
	SDL_RenderFillRect(renderer, ui_health_bar_rect);

	// draw the "fill" shadow
	SDL_SetRenderDrawColor(renderer, 130, 30, 30, 255); // darker red color
	ui_health_bar_rect->w = (int)health_width;
	ui_health_bar_rect->h = (int)shadow_height;
	ui_health_bar_rect->x = (int)(position.x + border_width);
	ui_health_bar_rect->y = (int)(position.y + size.y - shadow_height - border_width);
	SDL_RenderFillRect(renderer, ui_health_bar_rect);

	// draw the "glassy shine"
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 130);
	for (int i = 0; i < 3; ++i) {
		for (int j = i; j < 3; ++j) {
			ui_health_bar_rect->w = glass_pixel;
			ui_health_bar_rect->h = glass_pixel;
			ui_health_bar_rect->x = (int)(position.x + size.x - (border_width * 2) - ((1 + i) * glass_pixel));
			ui_health_bar_rect->y = (int)position.y - ((j - 4) * glass_pixel);
			SDL_RenderFillRect(renderer, ui_health_bar_rect);
		}
	}
}