#include "collision_handling.h"
#include <typeinfo>
#include <vector>
#include "camera.h"
#include "math_util.h"

using namespace collision;

// "private" functions
bool check_collision_between_boxes(BoxCollider* box1, BoxCollider* box2);
bool check_collision_between_circles(CircleCollider* circle1, CircleCollider* circle2);
bool check_collision_box_and_circle(Collider* coll1, Collider* coll2);
void render_collision_box(SDL_Renderer* renderer, BoxCollider* box);
void render_collision_circle(SDL_Renderer* renderer, CircleCollider* circle);
Vector2 calculate_collision_response_between_boxes(BoxCollider* box1, BoxCollider* box2);
Vector2 calculate_collision_response_between_circles(CircleCollider* circle1, CircleCollider* circle2);
Vector2 calculate_collision_response_between_box_and_circle(Collider* coll1, Collider* coll2);

BoxCollider* collision::create_collision_box(Vector2 position, Vector2 size) {
	return new BoxCollider(position, size);
}

CircleCollider* collision::create_collision_circle(Vector2 position, float radius) {
	return new CircleCollider(position, radius);
}

void collision::render_collision(SDL_Renderer* renderer, Collider* coll) {
	// is it a box?
	if (typeid(*coll) == typeid(BoxCollider)) {
		BoxCollider* box = (BoxCollider*)coll;
		render_collision_box(renderer, box);
	}
	// is it a circle?
	else if (typeid(*coll) == typeid(CircleCollider)) {
		CircleCollider* circle = (CircleCollider*)coll;
		render_collision_circle(renderer, circle);
	}
}

void collision::render_point(SDL_Renderer* renderer, Vector2 point) {
	SDL_Rect* rect = new SDL_Rect();
	rect->x = (int)(point.x - 3 - Camera::get_instance()->get_viewport_offset().x);
	rect->y = (int)(point.y - 3 - Camera::get_instance()->get_viewport_offset().y);
	rect->w = 6;
	rect->h = 6;
	SDL_RenderDrawRect(renderer, rect);
}

void collision::render_min_x(SDL_Renderer* renderer, Collider* coll) {
	// draw red
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	Vector2 point = coll->get_min_x_point();
	render_point(renderer, point);
}

void collision::render_max_x(SDL_Renderer* renderer, Collider* coll) {
	// draw blue
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	Vector2 point = coll->get_max_x_point();
	render_point(renderer, point);
}

void collision::render_min_y(SDL_Renderer* renderer, Collider* coll) {
	// draw green
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	Vector2 point = coll->get_min_y_point();
	render_point(renderer, point);
}

void collision::render_max_y(SDL_Renderer* renderer, Collider* coll) {
	// draw white
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	Vector2 point = coll->get_max_y_point();
	render_point(renderer, point);
}

collision::ProjectionMinMax collision::get_min_max_projection(Collider* coll, Vector2 axis) {
	if (typeid(*coll) == typeid(BoxCollider)) {
		BoxCollider* box = (BoxCollider*)coll;
		double min = dot_product(box->getCorner(0), axis);
		double max = dot_product(box->getCorner(0), axis);
		for (int i = 1; i < 4; ++i) {
			double currentProjBox = dot_product(box->getCorner(i), axis);
			if (min > currentProjBox) {
				min = currentProjBox;
			}

			if (max < currentProjBox) {
				max = currentProjBox;
			}
		}

		ProjectionMinMax minMax;
		minMax.min = min;
		minMax.max = max;
		return minMax;
	}

	if (typeid(*coll) == typeid(CircleCollider)) {
		CircleCollider* circle = (CircleCollider*)coll;
		double min = INFINITY;
		double max = -INFINITY;
		for (int i = 0; i < 360; ++i) {
			double currentProjBox = dot_product(circle->getPointOnCircleAtAngle(i * PI / 180), axis);
			if (min > currentProjBox) {
				min = currentProjBox;
			}

			if (max < currentProjBox) {
				max = currentProjBox;
			}
		}

		ProjectionMinMax minMax;
		minMax.min = min;
		minMax.max = max;
		return minMax;
	}

	return ProjectionMinMax();
}

bool collision::check_collision(Collider* coll, Collider* coll2) {
	// box on box collision
	if (typeid(*coll) == typeid(*coll2) && typeid(*coll) == typeid(BoxCollider)) {
		return check_collision_between_boxes((BoxCollider*)coll, (BoxCollider*)coll2);
	}
	// circle on circle collision
	else if (typeid(*coll) == typeid(*coll2) && typeid(*coll) == typeid(CircleCollider)) {
		return check_collision_between_circles((CircleCollider*)coll, (CircleCollider*)coll2);
	}
	// circle on box collision
	else {
		return check_collision_box_and_circle(coll, coll2);
	}

	return false;
}

Vector2 collision::calculate_response_vector(Collider* coll1, Collider* coll2) {
	// handle collision between circles
	if (typeid(*coll1) == typeid(*coll2) && typeid(*coll1) == typeid(CircleCollider)) {
		return calculate_collision_response_between_circles((CircleCollider*)coll1, (CircleCollider*)coll2);
	}

	// handle collision between boxes
	if (typeid(*coll1) == typeid(*coll2) && typeid(*coll1) == typeid(BoxCollider)) {
		return calculate_collision_response_between_boxes((BoxCollider*)coll1, (BoxCollider*)coll2);
	}

	// handle collision between circle and box
	return calculate_collision_response_between_box_and_circle(coll1, coll2);
}

// "private" functions
bool check_collision_between_boxes(BoxCollider* box1, BoxCollider* box2) {
	std::vector<Vector2> normals1 = box1->getNormals();
	std::vector<Vector2> normals2 = box2->getNormals();

	bool isSeparated = false;
	for (Vector2 normal : normals1) {
		ProjectionMinMax resBox1 = get_min_max_projection(box1, normal);
		ProjectionMinMax resBox2 = get_min_max_projection(box2, normal);

		isSeparated = (resBox1.max < resBox2.min) || (resBox2.max < resBox1.min);
		if (isSeparated)
			break;
	}

	if (!isSeparated) {
		for (Vector2 normal : normals2) {
			ProjectionMinMax resBox1 = get_min_max_projection(box1, normal);
			ProjectionMinMax resBox2 = get_min_max_projection(box2, normal);

			isSeparated = (resBox1.max < resBox2.min) || (resBox2.max < resBox1.min);
			if (isSeparated)
				break;
		}
	}

	return !isSeparated;
}

bool check_collision_between_circles(CircleCollider* circle1, CircleCollider* circle2) {
	double dist = distance_between(circle1->get_center_position(), circle2->get_center_position());
	double radius = circle1->getRadius() + circle2->getRadius();
	return (radius - dist >= 0);
}

bool check_collision_box_and_circle(Collider* coll1, Collider* coll2) {
	CircleCollider* circle = (CircleCollider*)(typeid(*coll1) == typeid(CircleCollider) ? coll1 : coll2);
	BoxCollider* box = (BoxCollider*)(typeid(*coll1) == typeid(BoxCollider) ? coll1 : coll2);

	std::vector<Vector2> normals = box->getNormals();
	bool isSeparated = false;

	for (Vector2 normal : normals) {
		ProjectionMinMax resBox1 = get_min_max_projection(box, normal);
		ProjectionMinMax resBox2 = get_min_max_projection(circle, normal);

		isSeparated = (resBox1.max < resBox2.min) || (resBox2.max < resBox1.min);
		if (isSeparated)
			break;
	}

	if (!isSeparated) {
		Vector2 normal = calculate_unit_vector(box->get_center_position() - circle->get_center_position());
		ProjectionMinMax resBox1 = get_min_max_projection(box, normal);
		ProjectionMinMax resBox2 = get_min_max_projection(circle, normal);

		isSeparated = (resBox1.max < resBox2.min) || (resBox2.max < resBox1.min);
	}

	return !isSeparated;
}

void render_collision_box(SDL_Renderer* renderer, BoxCollider* box) {
	SDL_SetRenderDrawColor(renderer, 0x00, 0xCC, 0x00, 0xFF);

	for (int index = 0; index < 4; ++index) {
		Vector2 corner = box->getCorner(index);
		switch (index) {
			case 0:
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderDrawLine(renderer, 
					(int)(corner.x - Camera::get_instance()->get_viewport_offset().x), 
					(int)(corner.y - Camera::get_instance()->get_viewport_offset().y),
					(int)(box->getCorner(1).x - Camera::get_instance()->get_viewport_offset().x),
					(int)(box->getCorner(1).y - Camera::get_instance()->get_viewport_offset().y));
				break;

			case 1:
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderDrawLine(renderer,
					(int)(corner.x - Camera::get_instance()->get_viewport_offset().x),
					(int)(corner.y - Camera::get_instance()->get_viewport_offset().y),
					(int)(box->getCorner(2).x - Camera::get_instance()->get_viewport_offset().x),
					(int)(box->getCorner(2).y - Camera::get_instance()->get_viewport_offset().y));
				break;

			case 2:
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
				SDL_RenderDrawLine(renderer,
					(int)(corner.x - Camera::get_instance()->get_viewport_offset().x),
					(int)(corner.y - Camera::get_instance()->get_viewport_offset().y),
					(int)(box->getCorner(3).x - Camera::get_instance()->get_viewport_offset().x),
					(int)(box->getCorner(3).y - Camera::get_instance()->get_viewport_offset().y));
				break;

			case 3:
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderDrawLine(renderer,
					(int)(corner.x - Camera::get_instance()->get_viewport_offset().x),
					(int)(corner.y - Camera::get_instance()->get_viewport_offset().y),
					(int)(box->getCorner(0).x - Camera::get_instance()->get_viewport_offset().x),
					(int)(box->getCorner(0).y - Camera::get_instance()->get_viewport_offset().y));
				break;
		}

		// line from center to corner
		SDL_RenderDrawLine(renderer,
			(int)(box->get_center_position().x - Camera::get_instance()->get_viewport_offset().x), 
			(int)(box->get_center_position().y - Camera::get_instance()->get_viewport_offset().y), 
			(int)(corner.x - Camera::get_instance()->get_viewport_offset().x),
			(int)(corner.y - Camera::get_instance()->get_viewport_offset().y));
	}
}

void render_collision_circle(SDL_Renderer* renderer, CircleCollider* circle) {
	Vector2 center = circle->get_center_position() - Camera::get_instance()->get_viewport_offset();
	double radius = circle->getRadius();

	int index = 0;
	for (int i = 0; i <= 360; ++i) {
		if (i % 90 == 0) {
			switch (index) {
				case 0:
					SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
					break;

				case 1:
					SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
					break;

				case 2:
					SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
					break;

				case 3:
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					break;
			}
			++index;
		}

		double angle = circle->rotation + (PI / 180 * i);
		double dx = cos(angle) * radius;
		double dy = sin(angle) * radius;
		SDL_RenderDrawPoint(renderer, (int)(center.x + dx), (int)(center.y + dy));
	}
}

Vector2 calculateResponseVector(Collider* coll1, Collider* coll2) {
	// handle collision between circles
	if (typeid(*coll1) == typeid(*coll2) && typeid(*coll1) == typeid(CircleCollider)) {
		return calculate_collision_response_between_circles((CircleCollider*)coll1, (CircleCollider*)coll2);
	}

	// handle collision between boxes
	if (typeid(*coll1) == typeid(*coll2) && typeid(*coll1) == typeid(BoxCollider)) {
		return calculate_collision_response_between_boxes((BoxCollider*)coll1, (BoxCollider*)coll2);
	}

	// handle collision between circle and box
	return calculate_collision_response_between_box_and_circle(coll1, coll2);
}

Vector2 calculate_collision_response_between_boxes(BoxCollider* box1, BoxCollider* box2) {
	Vector2 closestNormal;

	// which surface intersects the line between box and box2?
	for (int i = 0; i < 4; ++i) {
		Vector2 p1 = box2->getCorner(i);

		int j = i - 1;
		if (j < 0)
			j = 3;

		Vector2 q1 = box2->getCorner(j);

		if (do_intersect(p1, q1, box1->get_center_position(), box2->get_center_position())) {
			closestNormal = get_vector_normal(q1 - p1);
		}
	}

	return calculate_unit_vector(closestNormal);
}

Vector2 calculate_collision_response_between_circles(CircleCollider* circle1, CircleCollider* circle2) {
	double angle = angle_between(circle1->get_center_position(), circle2->get_center_position());
	return Vector2(cosf(angle), sinf(angle));
}

Vector2 calculate_collision_response_between_box_and_circle(Collider* coll1, Collider* coll2) {
	CircleCollider* circle = (CircleCollider*)(typeid(*coll1) == typeid(CircleCollider) ? coll1 : coll2);
	BoxCollider* box = (BoxCollider*)(typeid(*coll1) == typeid(BoxCollider) ? coll1 : coll2);

	Vector2 closestNormal;

	// which surface intersects the line between box and box2?
	for (int i = 0; i < 4; ++i) {
		Vector2 p1 = box->getCorner(i);

		int j = i - 1;
		if (j < 0)
			j = 3;

		Vector2 q1 = box->getCorner(j);

		if (do_intersect(p1, q1, circle->get_center_position(), box->get_center_position())) {
			closestNormal = get_vector_normal(q1 - p1);
		}
	}

	return calculate_unit_vector(closestNormal);
}

void collision::handle_collisions(std::vector<Collider*> colliders, Collider* collider_to_check, Vector2* position_to_update) {
	for (collision::Collider* collider : colliders) {
		if (collision::check_collision(collider_to_check, collider)) {
			Vector2 res = collision::calculate_response_vector(collider_to_check, collider);
			if (res.x == 0 && res.y == 0) {
				res.y = 1; // if there is a collision but the vector is 0, 0 
						   // that means we are directly on the collider
						   // doing this to prevent infinite loops
			}

			// move away from the collision util there is not longer a collision
			do {
				*position_to_update += res;
				collider_to_check->position = *position_to_update;
			} while (collision::check_collision(collider_to_check, collider));
		}
	}
}