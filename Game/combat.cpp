#include "combat.h"
#include "math_util.h"
#include <list>

int combat_id = 0;
std::list<combat::CombatUnit*> combat_units;

int combat::generate_combat_id() {
	++combat_id;
	return combat_id;
}

void combat::register_combatant(combat::CombatUnit* unit) {
	combat_units.push_back(unit);
}

void combat::unregister_combatant(combat::CombatUnit* unit) {
	combat_units.remove(unit);
}

void combat::dispatch_attack(CombatUnit* source_unit) {
	for (CombatUnit* unit : combat_units) {
		if (unit->get_combat_id() != source_unit->get_combat_id()) {
			if (distance_between(source_unit->position, unit->position) <= source_unit->get_stat().attack_range) {
				unit->receive_attack(source_unit->get_stat());
			}
		}
	}
}