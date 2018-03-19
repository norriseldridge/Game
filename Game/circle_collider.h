#include "collider.h"

#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

namespace collision {

	class CircleCollider : public Collider {
	private:
		float radius;
	public:
		CircleCollider(Vector2 position, float radius);
		Vector2 get_center_position();
		Vector2 get_min_x_point();
		Vector2 get_max_x_point();
		Vector2 get_min_y_point();
		Vector2 get_max_y_point();
		float getRadius();
		Vector2 getPointOnCircleAtAngle(double angle);
	};

}

#endif // !CIRCLE_COLLIDER_H
