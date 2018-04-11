#include "pathfinding.h"
#include "math_util.h"
#include <map>
#include <sstream>
#include <string>

namespace pathfinding {
	// helper function to get the distance between two nodes easily
	double distance_between_nodes(PathNode* node_a, PathNode* node_b) {
		return distance((double)node_a->x, (double)node_a->y, (double)node_b->x, (double)node_b->y);
	}

	struct PathCacheKey
	{
		PathNode* na;
		PathNode* nb;

		PathCacheKey(PathNode* a, PathNode* b) {
			na = a;
			nb = b;
		}
	};

	std::map<std::string, std::list<PathNode*>> path_cache;

	// returns the shortest path from the first node to the second node possible as quickly as possible
	std::list<PathNode*> get_path(PathNode* node_a, PathNode* node_b) {
		// error checking
		// if either our start or end is null,
		// there is no way to have a valid path,
		// so we shouldn't both checking.
		if (node_a == nullptr || node_b == nullptr)
			return std::list<PathNode*>();

		// construct or path cache key
		std::stringstream path_cache_key;
		path_cache_key << node_a;
		path_cache_key << node_b;

		// is this in our cache?
		if (path_cache.find(path_cache_key.str()) != path_cache.end()) {
			// if it is, just return that
			return path_cache[path_cache_key.str()];
		}

		// get our starting point to being our search
		AStarPathNode* start_node = new AStarPathNode();
		start_node->self = node_a;
		start_node->localGoal = 0.0;
		start_node->globalGoal = distance_between_nodes(node_a, node_b);

		// get a map of nodes visted to AStarData for that node
		std::map<PathNode*, AStarPathNode*> visited_nodes;

		// create our list of nodes to check and put our starting node in it
		std::list<AStarPathNode*> nodes_to_check;
		nodes_to_check.push_back(start_node);

		// create a "current node" this is the node we are currently checking
		AStarPathNode* current_node = nullptr;
		while (!nodes_to_check.empty()) {
			// sort the nodes
			nodes_to_check.sort([](const AStarPathNode* na, const AStarPathNode* nb) { return na->globalGoal < nb->globalGoal; });

			// remove any nodes we have already visited (checked)
			while (!nodes_to_check.empty() && visited_nodes[nodes_to_check.front()->self] != nullptr) {
				nodes_to_check.pop_front();
			}

			// if the list is empty at the point, stop checking
			if (nodes_to_check.empty())
				break;

			// set our current node and put this in the visited map
			current_node = nodes_to_check.front();
			visited_nodes[current_node->self] = current_node; // mark that we have checked it

			// look at each of the current node's neighbors
			for (PathNode* neighbor : current_node->self->neighbors) {
				if (visited_nodes[neighbor] != nullptr || neighbor->is_valid == false) {
					// we have already visited this node before or this node is not valid for pathing!
				}
				else {
					// create AStar data for this node
					AStarPathNode* astar_node = new AStarPathNode();
					astar_node->self = neighbor;

					// add this AStar data to the list to be checked
					nodes_to_check.push_back(astar_node);

					// determine if this node is helping us approach our end node
					double possible_lower_goal = current_node->localGoal + distance_between_nodes(current_node->self, neighbor);
					if (possible_lower_goal < astar_node->localGoal) {
						astar_node->parent = current_node->self;
						astar_node->localGoal = possible_lower_goal;
						astar_node->globalGoal = possible_lower_goal + distance_between_nodes(astar_node->self, node_b);
					}
				}
			}
		}

		// as long as the "end" is in the visited nodes,
		// we know we found a path
		std::list<PathNode*> path;
		if (visited_nodes[node_b]) {
			AStarPathNode* node = visited_nodes[node_b];

			while (node != nullptr) {
				path.push_back(node->self);
				node = visited_nodes[node->parent];
			}
		}

		// cache this path
		path_cache[path_cache_key.str()] = path;

		// return the path we found
		return path;
	}
}