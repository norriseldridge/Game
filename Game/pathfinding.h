#include <list>
#include "astar_path_node.h"

#ifndef PATHFINDING
#define PATHFINDING

namespace pathfinding {
	std::list<PathNode*> get_path(PathNode* node_a, PathNode* node_b);
}

#endif // !PATHFINDING