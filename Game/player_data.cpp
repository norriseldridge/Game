#include <iostream>
#include <fstream>
#include "player_data.h"
#include "nlohmann\json.hpp"

using json = nlohmann::json;

PlayerData load_player_data(const char* file) {
	// open the file
	std::ifstream player_file(file);

	// create the json data from the file
	json j;
	player_file >> j;

	// close the file
	player_file.close();

	PlayerData player_data;
	player_data.stat.health = j["health"];
	player_data.stat.max_health = j["max_health"];
	player_data.stat.speed = j["speed"];
	player_data.stat.attack = j["attack"];
	player_data.stat.attack_range = j["attack_range"];
	player_data.position.x = j["x"];
	player_data.position.y = j["y"];

	return player_data;
}