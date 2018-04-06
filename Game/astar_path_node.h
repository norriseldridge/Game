#include "path_node.h"
#include <numeric>

#ifndef ASTAR_PATH_NODE
#define ASTAR_PATH_NODE

namespace pathfinding {
	struct AStarPathNode
	{
		PathNode* parent = nullptr;
		PathNode* self = nullptr;
		double globalGoal = std::numeric_limits<double>::max();
		double localGoal = std::numeric_limits<double>::max();
	};
}

#endif // !ASTAR_PATH_NODE