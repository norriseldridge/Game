#include <SDL.h>
#include "vector2.h"

#ifndef MAP_TILE_H
#define MAP_TILE_H

namespace map {

	struct MapTile
	{
		SDL_Texture* texture;
		SDL_Rect* src = NULL;
		SDL_Rect* dest = NULL;
	};

	MapTile create_map_tile(SDL_Renderer* renderer, const char* file, int columns, int rows, int index, Vector2 size, Vector2 position);
	void render_map_tile(SDL_Renderer* renderer, MapTile& tile);

}

#endif // !MAP_TILE_H