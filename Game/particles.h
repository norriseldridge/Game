#include <SDL.h>
#include "color.h"
#include "vector2.h"

#ifndef PARTICLES_H
#define PARTICLES_H

namespace particles {

	struct Particle
	{
		Particle(Vector2 position, Vector2 velocity, Vector2 acceleration, float life_time, Color color) {
			this->position = position;
			this->velocity = velocity;
			this->acceleration = acceleration;
			this->life_time = life_time;
			this->color = color;
		}
		Color color;
		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;
		float life_time;
	};

	void create_blood_particles(int count, Vector2 position, Vector2 acceleration, float life_time, Color color);
	void update_blood_particles(SDL_Renderer* renderer);
	void render_blood_particles(SDL_Renderer* renderer);

}

#endif // !PARTICLES_H
