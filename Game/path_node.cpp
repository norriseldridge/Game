#include "path_node.h"

namespace pathfinding {

	void add_neighbor(PathNode* path_node, PathNode* neighbor) {
		// if we already contain this node, add it to our neighbors
		if (std::find(path_node->neighbors.begin(), path_node->neighbors.end(), neighbor)
			!= path_node->neighbors.end()) {
			return;
		}
		else {
			path_node->neighbors.push_back(neighbor);
		}
	}

}