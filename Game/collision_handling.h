#include <SDL.h>
#include "collider.h"
#include "box_collider.h"
#include "circle_collider.h"

#ifndef COLLISION_HANDLING_H
#define COLLISION_HANDLING_H

namespace collision {

	struct ProjectionMinMax {
		double min;
		double max;
	};

	// creation methods
	BoxCollider* create_collision_box(Vector2 position, Vector2 size);
	CircleCollider* create_collision_circle(Vector2 position, float radius);

	// rendering methods
	void render_collision(SDL_Renderer* renderer, Collider* coll);
	void render_point(SDL_Renderer* renderer, Vector2 point);
	void render_min_x(SDL_Renderer* renderer, Collider* coll);
	void render_max_x(SDL_Renderer* renderer, Collider* coll);
	void render_min_y(SDL_Renderer* renderer, Collider* coll);
	void render_max_y(SDL_Renderer* renderer, Collider* coll);

	// calculation methods
	ProjectionMinMax get_min_max_projection(Collider* coll, Vector2 axis);
	bool check_collision(Collider* coll, Collider* coll2);
	Vector2 calculate_response_vector(Collider* coll, Collider* coll2);
	void handle_collisions(std::vector<Collider*> colliders, Collider* collider_to_check, Vector2* position_to_update);

}

#endif // !COLLISION_HANDLING_H
