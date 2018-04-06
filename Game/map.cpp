#include <iostream>
#include <fstream>
#include <string>
#include "math_util.h"
#include "map.h"
#include "nlohmann\json.hpp"

using json = nlohmann::json;

map::Map::Map(SDL_Renderer* renderer, const char* file) {
	// set our renderer
	this->renderer = renderer;

	// open the file
	std::ifstream map_file(file);

	// create the json data from the file
	json j;
	map_file >> j;

	// close the file
	map_file.close();

	// loop over the collisions in the json
	for (json element : j["collisions"]) {
		int x = element["x"];
		int y = element["y"];

		if (element.count("r") > 0) {
			double r = element["r"];

			// offseting to be centered because
			// colliders are centered
			x += (int)r / 2;
			y += (int)r / 2;

			this->collision_tiles.push_back(collision::create_collision_circle(Vector2(x * TILE_SIZE, y * TILE_SIZE), (float)(r * TILE_SIZE)));
		}
		else {
			int w = element["w"];
			int h = element["h"];

			// offseting to be centered because
			// colliders are centered
			x += (int)w / 2;
			y += (int)h / 2;

			this->collision_tiles.push_back(collision::create_collision_box(Vector2(x * TILE_SIZE, y * TILE_SIZE), Vector2(w * TILE_SIZE, h * TILE_SIZE)));
		}
	}

	// loop over tiles in the json
	for (json element : j["tiles"]) {
		// get info to construct map tile
		std::string tile_texture = element["tile_image"];
		int columns = element["tile_image_colums"];
		int rows = element["tile_image_rows"];
		int tile_index = element["tile_index"];
		int x = element["x"];
		int y = element["y"];

		// determine if this node is a "collision" node
		bool is_valid = true;

		// is this tile inside a collision?
		for (auto collision_tile : this->collision_tiles) {
			if (x * TILE_SIZE >= collision_tile->get_min_x_point().x 
				&& x * TILE_SIZE <= collision_tile->get_max_x_point().x
				&& y * TILE_SIZE >= collision_tile->get_min_y_point().y
				&& y * TILE_SIZE <= collision_tile->get_max_y_point().y) {
				// this is a "collision" tile
				is_valid = false;
				break;
			}
		}

		// add path node to the path nodes
		if (is_valid) {
			pathfinding::PathNode * path_node = new pathfinding::PathNode();
			path_node->x = x * TILE_SIZE;
			path_node->y = y * TILE_SIZE;
			path_node->is_valid = true;
			this->path_nodes.push_back(path_node);
		}

		// add map tile to the map tiles
		this->map_tiles.push_back(create_map_tile(renderer,
			tile_texture.c_str(), columns, rows, tile_index,
			Vector2(TILE_SIZE, TILE_SIZE), Vector2(x * TILE_SIZE, y * TILE_SIZE)));
	}

	// look at each path node and determine its neighbors
	int path_nodes_count = path_nodes.size();
	for (int i = 0; i < path_nodes_count; ++i) {
		for (int j = 0; j < path_nodes_count; ++j) {
			if (i != j) {
				pathfinding::PathNode* path_node_i = path_nodes[i];
				pathfinding::PathNode* path_node_j = path_nodes[j];
				if (distance((double)path_node_i->x, (double)path_node_i->y,
					(double) path_node_j->x, (double)path_node_j->y) <= TILE_SIZE * 1.5) {
					pathfinding::add_neighbor(path_node_i, path_node_j);
				}
			}
		}
	}
}

std::vector<pathfinding::PathNode*> map::Map::get_path_nodes() {
	return path_nodes;
}

std::vector<collision::Collider*> map::Map::get_collision_tiles() {
	return collision_tiles;
}

void map::Map::render() {
	for (MapTile tile : map_tiles) {
		render_map_tile(renderer, tile);
	}
}