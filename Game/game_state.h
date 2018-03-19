#ifndef GAME_STATE_H
#define GAME_STATE_H

struct GameState
{
	bool quit = false;
	bool paused = false;
};

void quit_game();
bool did_quit();
void pause_game();
void unpause_game();
void toggle_paused();
bool is_paused();

#endif // !GAME_STATE_H

