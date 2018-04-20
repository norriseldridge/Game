#include <list>
#include <vector>
#include "astar_path_node.h"

#ifndef PATHFINDING
#define PATHFINDING

namespace pathfinding {
	std::list<PathNode*> get_path(PathNode* node_a, PathNode* node_b);
	void register_path_node(PathNode* path_node);
	int get_path_nodes_size();
	PathNode* get_path_node_at_index(int index);
	PathNode* get_path_node_at_position(Vector2 position);
}

#endif // !PATHFINDING