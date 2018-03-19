#include "camera.h"

Camera* Camera::instance = nullptr;

Camera* Camera::get_instance() {
	if (instance == nullptr) {
		instance = new Camera();
	}

	return instance;
}

Camera::Camera() {
	viewport = new SDL_Rect();
	position.x = position.y = 0;
}

void Camera::set_window_dimensions(Vector2 window_dimensions) {
	viewport->w = (int)window_dimensions.x;
	viewport->h = (int)window_dimensions.y;
}

void Camera::set_position(Vector2 position) {
	this->position = position;
}

void Camera::offset_position(Vector2 offset_amount) {
	position += offset_amount;
}

Vector2 Camera::get_viewport_offset() {
	// update position
	viewport->x = (int)position.x;
	viewport->y = (int)position.y;
	return Vector2(viewport->x - viewport->w / 2, viewport->y - viewport->h / 2);
}