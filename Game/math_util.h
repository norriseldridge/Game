#include "vector2.h"
#include <cmath>

#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#define PI 3.14159265359
#define ROOT_2 1.41421356237
#define RADIAN 0.0174533

float distance(float x1, float y1, float x2, float y2);
Vector2 calculate_unit_vector(Vector2 vec);

double degrees_to_radians(double degrees);
double distance(double x1, double y1, double x2, double y2);
double distance_between(Vector2 a, Vector2 b);
double angle_between(Vector2 a, Vector2 b);
double angle_of_vector(Vector2 a);
double dot_product(Vector2 a, Vector2 b);
double magnitude_of_vector(Vector2 a);
Vector2 get_vector_normal(Vector2 a);
double min(double a, double b);
double max(double a, double b);
bool on_segment(Vector2 p, Vector2 q, Vector2 r);
int orientation(Vector2 p, Vector2 q, Vector2 r);
bool do_intersect(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2);

#endif // !MATH_UTIL_H