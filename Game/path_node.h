#include <vector>

#ifndef PATH_NODE_H
#define PATH_NODE_H

namespace pathfinding {
	struct PathNode {
		int x, y;
		bool is_valid;
		std::vector<PathNode*> neighbors;
	};

	void add_neighbor(PathNode* path_node, PathNode* neighbor);
}

#endif // !PATH_NODE_H

