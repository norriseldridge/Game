#include "sprite.h"

sprite::Sprite::Sprite(SDL_Renderer* renderer, const char* file, Vector2 position, Vector2 size) {
	// set the renderer
	this->renderer = renderer;

	// set the texture
	this->texture = load_texture_from_file(renderer, file);

	// set the size and position
	this->position = position;
	this->dest = new SDL_Rect();
	this->dest->x = (int)position.x;
	this->dest->y = (int)position.y;
	this->dest->w = (int)size.x;
	this->dest->h = (int)size.y;

	// set the clipping (by default, none)
	Vector2 texture_dimensions = get_sprite_texture_dimensions();
	this->src = new SDL_Rect();
	this->src->w = (int)texture_dimensions.x;
	this->src->h = (int)texture_dimensions.y;
	this->src->x = 0;
	this->src->y = 0;
}

sprite::Sprite::~Sprite() {
	sprite_animations.clear();
	SDL_DestroyTexture(texture);
	texture = NULL;
	dest = NULL;
	src = NULL;
}

Vector2 sprite::Sprite::get_sprite_texture_dimensions() {
	return get_texture_dimensions(texture);
}

void sprite::Sprite::add_animation(std::string animation_name, SpriteAnimation sprite_animation) {
	sprite_animations[animation_name] = sprite_animation;
}

void sprite::Sprite::play_animation(std::string animation_name) {
	// make sure this animation actually exists
	if (sprite_animations.find(animation_name) != sprite_animations.end()) {
		// play / progress to next frame
		play_sprite_animation(sprite_animations[animation_name], src);
	}
}

void sprite::Sprite::render() {
	render_with_offset(Vector2());
}

void sprite::Sprite::render_with_offset(Vector2 offset) {
	// set the position to be centered
	dest->x = (int)(position.x - (dest->w / 2) - offset.x);
	dest->y = (int)(position.y - (dest->h / 2) - offset.y);
	SDL_RenderCopyEx(renderer, texture, src, dest, 0.0f, NULL, SDL_FLIP_NONE);
}

void sprite::render_sprite_with_camera(Sprite* sprite) {
	sprite->render_with_offset(Camera::get_instance()->get_viewport_offset());
}