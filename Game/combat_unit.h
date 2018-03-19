#include "stat.h"
#include "vector2.h"
#include "color.h"

#ifndef COMBAT_UNIT_H
#define COMBAT_UNIT_H

namespace combat {

	class CombatUnit {
	protected:
		Stat stat;
		int combat_id;
		Color blood_color;
		~CombatUnit();
	public:
		Vector2 position;
		CombatUnit(Stat stat, Color blood_color);
		Stat get_stat();
		int get_combat_id();
		void receive_attack(Stat stat);
	};

}

#endif // !COMBAT_UNIT_H
