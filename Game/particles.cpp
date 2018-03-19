#include "particles.h"
#include <list>
#include "game_time.h"
#include "camera.h"
#include <cstdlib>

std::list<particles::Particle*> blood_particles;

const int PARTICLE_SIZE = 10;

void particles::create_blood_particles(int count, Vector2 position, Vector2 acceleration, float life_time, Color color) {
	for (int i = 0; i < count; ++i) {
		Vector2 rand_acc(
			(rand() % (int)((100 * acceleration.x) + 1)) / 100.0f,
			(rand() % (int)((100 * acceleration.y) + 1)) / 100.0f);
		bool odd = rand() % 50 < 50;
		if (odd) {
			rand_acc.x *= -1;
		}
		float particle_life = (rand() % (int)(life_time * 100)) / 100.0f;
		blood_particles.push_back(new Particle(position, Vector2(), rand_acc, particle_life, color));
	}
}

SDL_Rect* particle_rect = new SDL_Rect();
void update_blood_particle(SDL_Renderer* renderer, particles::Particle* particle) {
	particle->life_time -= game_time::get_ticks() / 1000.0f;
	if (particle->life_time >= 0.0f) {
		particle->acceleration *= Vector2(0.9f, 1.0f);
		particle->acceleration += Vector2(0.0f, 0.05f * game_time::get_ticks() / 1000.0f);

		particle->velocity += particle->acceleration;

		if (particle->velocity.y > 1.75f) {
			particle->velocity.y = -1.0f * particle->life_time;
		}

		particle->position += particle->velocity;
	}
}

void particles::update_blood_particles(SDL_Renderer* renderer) {
	for (Particle* particle : blood_particles) {
		update_blood_particle(renderer, particle);
	}

	blood_particles.remove_if([&](Particle* p) {
		if (p->life_time <= 0.0f) {
			delete p;
			return true;
		}

		return false; 
	});
}

void render_particle(SDL_Renderer* renderer, particles::Particle* particle) {
	float alpha = particle->life_time;
	if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	particle_rect->w = PARTICLE_SIZE;
	particle_rect->h = PARTICLE_SIZE;
	particle_rect->x = (int)(particle->position.x - Camera::get_instance()->get_viewport_offset().x);
	particle_rect->y = (int)(particle->position.y - Camera::get_instance()->get_viewport_offset().y);
	SDL_SetRenderDrawColor(renderer, (Uint8)particle->color.r, (Uint8)particle->color.g, (Uint8)particle->color.b, (Uint8)(particle->color.a * alpha));
	SDL_RenderFillRect(renderer, particle_rect);
}

void particles::render_blood_particles(SDL_Renderer* renderer) {
	for (Particle* particle : blood_particles) {
		render_particle(renderer, particle);
	}
}