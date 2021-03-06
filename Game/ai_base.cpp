#include "ai_base.h"

namespace ai {
	void AI::set_combat_unit(combat::CombatUnit* combat_unit) {
		this->combat_unit = combat_unit;
	}

	combat::CombatUnit* AI::get_combat_unit() {
		return combat_unit;
	}
}