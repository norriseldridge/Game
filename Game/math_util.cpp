#include "math_util.h"
#include <math.h>

float distance(float x1, float y1, float x2, float y2) {
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}

Vector2 calculate_unit_vector(Vector2 vec) {
	float dist = distance(0, 0, vec.x, vec.y);
	// can't divide by 0
	if (dist == 0.0f) {
		return Vector2();
	}

	return Vector2(vec.x / dist, vec.y / dist);
}

double degrees_to_radians(double degrees) {
	return degrees * PI / 180;
}

double distance(double x1, double y1, double x2, double y2) {
	double dx = x1 - x2;
	double dy = y1 - y2;
	return sqrt((dx * dx) + (dy * dy));
}

double distance_between(Vector2 a, Vector2 b) {
	return distance(a.x, a.y, b.x, b.y);
}

double angle_between(Vector2 a, Vector2 b) {
	return atan2(a.y - b.y, a.x - b.x);
}

double angle_of_vector(Vector2 a) {
	return angle_between(Vector2(a.x, a.y), Vector2(0, 0));
}

double dot_product(Vector2 a, Vector2 b) {
	return (a.x * b.x) + (a.y * b.y);
}

double magnitude_of_vector(Vector2 a) {
	return distance_between(Vector2(0, 0), Vector2(a.x, a.y));
}

Vector2 get_vector_normal(Vector2 a) {
	return Vector2(-1 * a.y, a.x);
}

double min(double a, double b) {
	return (a < b) ? a : b;
}

double max(double a, double b) {
	return (a > b) ? a : b;
}

bool on_segment(Vector2 p, Vector2 q, Vector2 r) {
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Vector2 p, Vector2 q, Vector2 r) {
	// See http://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool do_intersect(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2) {
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && on_segment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && on_segment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && on_segment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && on_segment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}