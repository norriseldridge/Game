#include "pathfinding.h"

#ifndef PATHFINDER
#define PATHFINDER

namespace pathfinding {
	class Pathfinder
	{
	public:
		PathNode* get_next_node();
		void update_path(Vector2 current, Vector2 target);
		int nodes_to_target();
	private:
		std::list<PathNode*> path_to_target;
	};
}

#endif // !PATHFINDER
