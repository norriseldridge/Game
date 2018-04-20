#include <vector>
#include "vector2.h"

#ifndef PATH_NODE_H
#define PATH_NODE_H

namespace pathfinding {
	struct PathNode {
		Vector2 position;
		bool is_valid;
		std::vector<PathNode*> neighbors;
	};

	void add_neighbor(PathNode* path_node, PathNode* neighbor);
	bool at_node(Vector2 position, PathNode* path_node);
}

#endif // !PATH_NODE_H

