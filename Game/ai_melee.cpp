#include "ai_melee.h"
#include "math_util.h"
#include "game_time.h"
#include "combat.h"

namespace ai {
	AIMelee::AIMelee(AIRangeData range_data, float attack_cooldown) {
		state = AIState::idle_state;
		active_range = range_data.active_range;
		inactive_range = range_data.inactive_range;
		attack_range = range_data.attack_range;
		this->attack_cooldown = attack_cooldown;
		last_attack = 0;
	}

	void AIMelee::set_position(Vector2 position) {
		this->position = position;
	}

	Vector2 AIMelee::get_position() {
		return position;
	}

	void AIMelee::set_target(Vector2 target) {
		this->target = target;
	}

	void AIMelee::update_state() {
		switch (state)
		{
			case AIState::idle_state:
			{
				// are we in range of the target?
				state = (distance_between(position, target) <= active_range) ? AIState::active_state : AIState::idle_state;
			}
			break;

			case AIState::active_state:
			{
				// are we out of range of the target?
				float dist = (float)distance_between(position, target);
				state = (dist >= inactive_range) ? AIState::idle_state : AIState::active_state;

				// are we in range of attacking the target?
				if (dist <= attack_range) {
					state = AIState::attack_state;
				}
			}
			break;

			case AIState::attack_state:
			{
				state = (distance_between(position, target) > attack_range) ? AIState::active_state : AIState::attack_state;
			}
			break;
		}
	}

	void AIMelee::move_torward(Vector2 destination) {
		Vector2 movement = calculate_unit_vector(destination - position);
		position += movement * combat_unit->get_stat().speed * (float)game_time::get_ticks() / 1000.0f;
	}

	void AIMelee::strike_when_in_range() {
		float dist = (float)distance_between(position, target);

		if (dist <= attack_range) {
			if (attack_is_ready()) {
				do_attack();
			}
		}
	}

	void AIMelee::update_last_attack() {
		last_attack += game_time::get_ticks() / 1000.0f;
	}

	bool AIMelee::attack_is_ready() {
		return (last_attack >= attack_cooldown);
	}

	void AIMelee::do_attack() {
		last_attack = 0.0f; // reset the attack delay
		combat::dispatch_attack(combat_unit);
	}

	void AIMelee::run_ai() {
		update_state();
		update_last_attack();

		if (state == AIState::active_state) {
			if (path_to_target.size() > 1) {
				next_node = path_to_target.back();
				if (distance(next_node->x, next_node->y, position.x, position.y) < 45) {
					path_to_target.pop_back();
				}
				
				move_torward(Vector2(next_node->x, next_node->y));
			}
			else {
				move_torward(target);
			}
		}

		strike_when_in_range();
	}

	void AIMelee::update_path(pathfinding::PathNode* current_node, pathfinding::PathNode* target_node) {
		if (this->target_node != target_node) {
			this->target_node = target_node;
			path_to_target = pathfinding::get_path(current_node, target_node);
		}
	}
}