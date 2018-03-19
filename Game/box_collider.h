#include "collider.h"
#include <vector>

#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

namespace collision {

	class BoxCollider : public Collider {
	private:
		std::vector<Vector2> corners;
		Vector2 minXPoint;
		Vector2 minYPoint;
		Vector2 maxXPoint;
		Vector2 maxYPoint;
		Vector2 size;
		void updateCorners();
		void updateMinMaxPoints();
	public:
		BoxCollider(Vector2 position, Vector2 size);
		Vector2 get_center_position();
		Vector2 get_min_x_point();
		Vector2 get_max_x_point();
		Vector2 get_min_y_point();
		Vector2 get_max_y_point();
		Vector2 getCorner(int index);
		std::vector<Vector2> getNormals();
	};

}

#endif // !BOX_COLLIDER_H
