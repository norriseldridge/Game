#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdio>
#include "camera.h"
#include "core_game.h"
#include "game_state.h"
#include "image_util.h"

int init();
void close(SDL_Window* window, SDL_Renderer* renderer);
void check_quit();

int main(int argc, char* args[]) {
	if (init() < 0) {
		return -1;
	}

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 480;

	// Create the window
	window = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 
		SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Failed to create window. SDL Error: %s", SDL_GetError());
		return -1;
	}

	// Set camera dimensions
	Camera::get_instance()->set_window_dimensions(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));

	// Create the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND); // set the alpha to blend

	// core game setup
	core_game::setup(renderer);

	// main loop
	while (!did_quit()) {
		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// get the keyboard state to work with
		const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
		int mouse_x, mouse_y;
		Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

		// main game loop
		core_game::main_loop(renderer, keyboard_state, mouse_state, Vector2(mouse_x, mouse_y));

		// allow the user to quit / pause the program
		check_quit();

		// render to the screen
		SDL_RenderPresent(renderer);
	}

	// core game cleanup
	core_game::cleanup();

	// clean up and close
	close(window, renderer);
	return 0;
}


int init() {
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Failed to init SDL. SDL Error: %s", SDL_GetError());
		return -1;
	}

	// Init Image
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
		printf("Failed to init SDL_image. IMG Error: %s", IMG_GetError());
		return -1;
	}

	// Init mixer
	if (Mix_OpenAudio(4410, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Failed to open audio. MIX Error: %s", Mix_GetError());
		return -1;
	}

	// Init ttf
	if (TTF_Init() < 0) {
		printf("Failed to init TTF. TTF Error: %s", TTF_GetError());
		return -1;
	}

	return 0;
}

void close(SDL_Window* window, SDL_Renderer* renderer) {
	clear_image_cache();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void check_quit() {
	SDL_Event e;
	if (SDL_PollEvent(&e) > 0) {
		switch (e.type)
		{
			// Quit the application entirely when we close the window
			case SDL_QUIT:
				quit_game();
				break;

			// Pause / Unpause the game if we press 'Esc'
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					toggle_paused();
				}
				break;
		}
	}
}