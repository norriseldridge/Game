#include "game_state.h"

GameState gameState;

void quit_game() {
	gameState.quit = true;
}

bool did_quit() {
	return gameState.quit;
}

void pause_game() {
	gameState.paused = true;
}

void unpause_game() {
	gameState.paused = false;
}

void toggle_paused() {
	gameState.paused = !gameState.paused;
}

bool is_paused() {
	return gameState.paused;
}