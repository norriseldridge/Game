#include <cstdio>
#include <map>
#include "image_util.h"

std::map<const char*, SDL_Texture*> image_cache;

SDL_Texture* load_texture_from_file(SDL_Renderer* renderer, const char* file) {
	// check the cache first
	if (image_cache.find(file) != image_cache.end()) {
		return image_cache[file];
	}

	// load surface
	SDL_Surface* surface = IMG_Load(file);
	if (surface == NULL) {
		printf("Failed to load image \'%s\'. SDL Error: %s", file, IMG_GetError());
		return NULL;
	}
	
	// texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	// free the surface
	SDL_FreeSurface(surface);
	surface = NULL;

	// add this image to the cache
	image_cache[file] = texture;

	return texture;
}

Vector2 get_texture_dimensions(SDL_Texture* texture) {
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	return Vector2(w, h);
}

void clear_image_cache() {
	image_cache.clear();
}