#include "path_node.h"
#include "math_util.h"

namespace pathfinding {
	double AT_NODE_DISTANCE = 50; // we are "at a node" as long as we are within this distance from it

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

	bool at_node(Vector2 position, PathNode* path_node) {
		return (distance_between(position, path_node->position) <= AT_NODE_DISTANCE);
	}
}