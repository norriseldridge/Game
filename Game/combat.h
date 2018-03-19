#include "combat_unit.h"

#ifndef COMBAT_H
#define COMBAT_H

namespace combat {

	int generate_combat_id();
	void register_combatant(CombatUnit* unit);
	void unregister_combatant(CombatUnit* unit);
	void dispatch_attack(CombatUnit* source_unit);

}

#endif // !COMBAT_H
