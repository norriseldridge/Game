#include <vector>
#include "collision_handling.h"
#include "map_tile.h"
#include "path_node.h"

#ifndef MAP_H
#define MAP_H

namespace map {

	const int TILE_SIZE = 75;

	class Map {
	private:
		SDL_Renderer* renderer;
		std::vector<MapTile> map_tiles;
		std::vector<pathfinding::PathNode*> path_nodes;
		std::vector<collision::Collider*> collision_tiles;
	public:
		Map(SDL_Renderer* renderer, const char* file);
		std::vector<pathfinding::PathNode*> get_path_nodes();
		std::vector<collision::Collider*> get_collision_tiles();
		pathfinding::PathNode* get_path_node_at_position(Vector2 position);
		void render();
	};

}

#endif // !MAP_H