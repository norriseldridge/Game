#include "box_collider.h"
#include "math_util.h"

collision::BoxCollider::BoxCollider(Vector2 position, Vector2 size) {
	this->position = position;
	this->size = size;
	updateCorners();
}

Vector2 collision::BoxCollider::get_center_position() {
	return position;
}

Vector2 collision::BoxCollider::get_min_x_point() {
	return position + minXPoint;
}

Vector2 collision::BoxCollider::get_max_x_point() {
	return position + maxXPoint;
}

Vector2 collision::BoxCollider::get_min_y_point() {
	return position + minYPoint;
}

Vector2 collision::BoxCollider::get_max_y_point() {
	return position + maxYPoint;
}

Vector2 collision::BoxCollider::getCorner(int index) {
	return position + corners[index];
}

std::vector<Vector2> collision::BoxCollider::getNormals() {
	std::vector<Vector2> normals;
	for (int i = 0; i < corners.size() - 1; ++i) {
		Vector2 current = corners[i + 1] - corners[i];
		normals.push_back(calculate_unit_vector(get_vector_normal(current)));
	}

	Vector2 current = corners[0] - corners[corners.size() - 1];
	normals.push_back(calculate_unit_vector(get_vector_normal(current)));
	return normals;
}

void collision::BoxCollider::updateCorners() {
	// empty any previous corners
	corners.clear();

	double s = sin(rotation);
	double c = cos(rotation);

	double width = size.x / 2;
	double height = size.y / 2;

	Vector2 centerPoint;

	Vector2 topMiddle;
	topMiddle.x = centerPoint.x + (s * height);
	topMiddle.y = centerPoint.y - (c * height);

	Vector2 bottomMiddle;
	bottomMiddle.x = centerPoint.x - (s * height);
	bottomMiddle.y = centerPoint.y + (c * height);

	// soh cah toa
	Vector2 nw;
	nw.x = topMiddle.x - (c * width);
	nw.y = topMiddle.y - (s * width);

	Vector2 ne;
	ne.x = topMiddle.x + (c * width);
	ne.y = topMiddle.y + (s * width);

	Vector2 se;
	se.x = bottomMiddle.x + (c * width);
	se.y = bottomMiddle.y + (s * width);

	Vector2 sw;
	sw.x = bottomMiddle.x - (c * width);
	sw.y = bottomMiddle.y - (s * width);

	corners.push_back(nw);
	corners.push_back(ne);
	corners.push_back(se);
	corners.push_back(sw);

	// update min and max points
	updateMinMaxPoints();
}

void collision::BoxCollider::updateMinMaxPoints() {
	for (Vector2 corner : corners) {
		// min x
		if (corner.x < minXPoint.x) {
			minXPoint.x = corner.x;
			minXPoint.y = corner.y;
		}

		// max x
		if (corner.x > maxXPoint.x) {
			maxXPoint.x = corner.x;
			maxXPoint.y = corner.y;
		}

		// min y
		if (corner.y < minYPoint.y) {
			minYPoint.x = corner.x;
			minYPoint.y = corner.y;
		}

		// max y
		if (corner.y > maxYPoint.y) {
			maxYPoint.x = corner.x;
			maxYPoint.y = corner.y;
		}
	}
}