#include "vector2.h"

#ifndef COLLIDER_H
#define COLLIDER_H

namespace collision {

	class Collider {
	public:
		Vector2 position;
		float rotation;
		virtual Vector2 get_center_position() = 0;
		virtual Vector2 get_min_x_point() = 0;
		virtual Vector2 get_max_x_point() = 0;
		virtual Vector2 get_min_y_point() = 0;
		virtual Vector2 get_max_y_point() = 0;
	};

}

#endif // !COLLIDER_H
