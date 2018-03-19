#include "ai_base.h"
#include "ai_range_data.h"
#include "ai_state.h"
#include <cstdio>

#ifndef AI_MELEE_H
#define AI_MELEE_H

namespace ai {

	class AIMelee : public AI {
	private:
		AIState state;
		Vector2 position;
		Vector2 target;
		float last_attack;

		// ai melee "constants"
		float active_range;
		float inactive_range;
		float attack_range;
		float attack_cooldown;

		// private melee ai functionality
		void update_state();
		void move_torward(Vector2 destination);
		void strike_when_in_range();
		void update_last_attack();
		bool attack_is_ready();
		void do_attack();
	public:
		AIMelee(AIRangeData range_data, float attack_cooldown);
		void set_position(Vector2 position);
		Vector2 get_position();
		void set_target(Vector2 position);
		void run_ai();
	};

}

#endif // !AI_MELEE_H
