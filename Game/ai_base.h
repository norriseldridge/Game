#include "stat.h"
#include "vector2.h"
#include "combat_unit.h"

#ifndef AI_BASE_H
#define AI_BASE_H

/*
NOTE:

As a design philosophy, things "have" an ai, things "aren't" an ai.

An example is Enemy. Enemy can have a melee ai, a ranged ai, a custom boss ai, etc.
but the core functionality of an Enemy does not change depending on the type of
behavior it has.

Enemy still has visuals, etc. So it doesn't make sense to define a new type of "Enemy"
when the only thing that changes between them is the behavior.
*/

namespace ai {

	class AI {
	protected:
		combat::CombatUnit* combat_unit;
	public:
		void set_combat_unit(combat::CombatUnit* combat_unit);
		combat::CombatUnit* get_combat_unit();
		virtual void run_ai()=0; // to be overridden
		virtual void set_position(Vector2 position)=0;
		virtual Vector2 get_position()=0;
		virtual void set_target(Vector2 position)=0;
	};

}

#endif // !AI_BASE_H
