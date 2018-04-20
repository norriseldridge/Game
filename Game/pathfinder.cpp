#include "pathfinder.h"

namespace pathfinding {
	PathNode* Pathfinder::get_next_node() {
		if (path_to_target.size() > 0) {
			return path_to_target.back();
		}

		return nullptr;
	}

	void Pathfinder::update_path(Vector2 current, Vector2 target) {
		path_to_target = pathfinding::get_path(pathfinding::get_path_node_at_position(current), pathfinding::get_path_node_at_position(target));

		if (at_node(current, path_to_target.back())) {
			path_to_target.pop_back();
		}
	}

	int Pathfinder::nodes_to_target() {
		return path_to_target.size();
	}
}