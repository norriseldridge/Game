#include "camera.h"
#include "map_tile.h"
#include "image_util.h"

map::MapTile map::create_map_tile(SDL_Renderer* renderer, const char* file, int columns, int rows, int index, Vector2 size, Vector2 position) {
	MapTile tile;
	tile.texture = load_texture_from_file(renderer, file);

	Vector2 texture_dimensions = get_texture_dimensions(tile.texture);
	int tile_width = (int)(texture_dimensions.x / columns);
	int tile_height = (int)(texture_dimensions.y / rows);
	int row = index / columns;
	int column = index - (row * columns);

	tile.src = new SDL_Rect();
	tile.src->w = tile_width;
	tile.src->h = tile_height;
	tile.src->x = column * tile_width;
	tile.src->y = row * tile_height;

	tile.dest = new SDL_Rect();
	tile.dest->w = (int)size.x;
	tile.dest->h = (int)size.y;
	tile.dest->x = (int)position.x;
	tile.dest->y = (int)position.y;

	return tile;
}

SDL_Rect* map_tile_dest = new SDL_Rect();
void map::render_map_tile(SDL_Renderer* renderer, MapTile& tile) {
	map_tile_dest->w = tile.dest->w;
	map_tile_dest->h = tile.dest->h;
	map_tile_dest->x = (int)(tile.dest->x - (map_tile_dest->w / 2) - Camera::get_instance()->get_viewport_offset().x);
	map_tile_dest->y = (int)(tile.dest->y - (map_tile_dest->h / 2) - Camera::get_instance()->get_viewport_offset().y);

	SDL_RenderCopy(renderer, tile.texture, tile.src, map_tile_dest);
}