#include "circle_collider.h"
#include <math.h>

collision::CircleCollider::CircleCollider(Vector2 position, float radius) {
	this->position = position;
	this->radius = radius;
}

float collision::CircleCollider::getRadius() {
	return radius;
}

Vector2 collision::CircleCollider::get_center_position() {
	return position;
}

Vector2 collision::CircleCollider::get_min_x_point() {
    return position - Vector2(radius, 0.0f);
}

Vector2 collision::CircleCollider::get_max_x_point() {
    return position + Vector2(radius, 0.0f);
}

Vector2 collision::CircleCollider::get_min_y_point() {
    return position - Vector2(0.0f, radius);
}

Vector2 collision::CircleCollider::get_max_y_point() {
    return position + Vector2(0.0f, radius);
}

Vector2 collision::CircleCollider::getPointOnCircleAtAngle(double angle) {
	Vector2 angleVec(cosf(angle), sinf(angle));

	return position + (angleVec * radius);
}