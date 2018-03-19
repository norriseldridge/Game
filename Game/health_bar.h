#include <SDL.h>
#include "stat.h"
#include "vector2.h"

#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

namespace ui {

	void render_health_bar(SDL_Renderer* render, float health, float max_health, Vector2 position, Vector2 size);

}

#endif // !HEALTH_BAR_H
