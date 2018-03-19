#include <SDL.h>
#include <SDL_image.h>
#include "vector2.h"

#ifndef IMAGE_UTIL_H
#define IMAGE_UTIL_H

SDL_Texture* load_texture_from_file(SDL_Renderer* renderer, const char* file);
Vector2 get_texture_dimensions(SDL_Texture* texture);
void clear_image_cache();

#endif // !IMAGE_UTIL_H

