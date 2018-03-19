#include "ai_base.h"

void ai::AI::set_combat_unit(combat::CombatUnit* combat_unit) {
	this->combat_unit = combat_unit;
}

combat::CombatUnit* ai::AI::get_combat_unit() {
	return combat_unit;
}