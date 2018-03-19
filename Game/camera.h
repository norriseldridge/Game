#include <SDL.h>
#include "vector2.h"

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
private:
	static Camera* instance;
	Camera();
	SDL_Rect* viewport;
	Vector2 position;
public:
	static Camera* get_instance();
	void set_window_dimensions(Vector2 window_dimensions);
	void set_position(Vector2 position);
	void offset_position(Vector2 offset_amount);
	Vector2 get_viewport_offset();
};

#endif // !CAMERA_H