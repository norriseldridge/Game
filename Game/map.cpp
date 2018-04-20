#include <iostream>
#include <fstream>
#include <string>
#include "math_util.h"
#include "map.h"
#include "nlohmann\json.hpp"

namespace map {

	using json = nlohmann::json;

	Map::Map(SDL_Renderer* renderer, const char* file) {
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
				float r = element["r"];

				// offseting to be centered because
				// colliders are centered
				x += (int)(r / 2);
				y += (int)(r / 2);

				this->collision_tiles.push_back(collision::create_collision_circle(Vector2(x * TILE_SIZE, y * TILE_SIZE), (float)(r * TILE_SIZE)));
			}
			else {
				float w = element["w"];
				float h = element["h"];

				float off_x = 0.0f;
				if ((int)w % 2 == 0) {
					off_x = -0.5f;
				}

				float off_y = 0.0f;
				if ((int)h % 2 == 0) {
					off_y = -0.5f;
				}

				x += (int)(w / 2.0f);
				y += (int)(h / 2.0f);

				collision::BoxCollider* coll = collision::create_collision_box(Vector2(((float)x + off_x) * TILE_SIZE, ((float)y + off_y) * TILE_SIZE), Vector2(w * TILE_SIZE, h * TILE_SIZE));

				this->collision_tiles.push_back(coll);
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
				path_node->position.x = (float)(x * TILE_SIZE);
				path_node->position.y = (float)(y * TILE_SIZE);
				path_node->is_valid = true;
				pathfinding::register_path_node(path_node);
			}

			// add map tile to the map tiles
			this->map_tiles.push_back(create_map_tile(renderer,
				tile_texture.c_str(), columns, rows, tile_index,
				Vector2(TILE_SIZE, TILE_SIZE), Vector2(x * TILE_SIZE, y * TILE_SIZE)));
		}

		// look at each path node and determine its neighbors
		int path_nodes_count = pathfinding::get_path_nodes_size();
		for (int i = 0; i < path_nodes_count; ++i) {
			for (int j = 0; j < path_nodes_count; ++j) {
				if (i != j) {
					pathfinding::PathNode* path_node_i = pathfinding::get_path_node_at_index(i);
					pathfinding::PathNode* path_node_j = pathfinding::get_path_node_at_index(j);
					if (distance_between(path_node_i->position, path_node_j->position) <= TILE_SIZE) { // to include diagonals * 1.5f
						pathfinding::add_neighbor(path_node_i, path_node_j);
					}
				}
			}
		}
	}

	std::vector<collision::Collider*> Map::get_collision_tiles() {
		return collision_tiles;
	}

	void Map::render() {
		for (MapTile tile : map_tiles) {
			render_map_tile(renderer, tile);
		}

		for (auto coll : collision_tiles) {
			collision::render_collision(renderer, coll);
		}
	}
}