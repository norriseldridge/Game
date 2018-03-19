#include "vector2.h"
#include "stat.h"

#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

struct PlayerData
{
	Vector2 position;
	Stat stat;
};

PlayerData load_player_data(const char* file);

#endif // !PLAYER_DATA_H