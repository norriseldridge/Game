#include "combat_unit.h"
#include "combat.h"
#include "particles.h"

combat::CombatUnit::CombatUnit(Stat stat, Color blood_color) {
	this->combat_id = combat::generate_combat_id();
	this->stat = stat;
	this->blood_color = blood_color;
	combat::register_combatant(this);
}

combat::CombatUnit::~CombatUnit() {
	combat::unregister_combatant(this);
}

Stat combat::CombatUnit::get_stat() {
	return stat;
}

int combat::CombatUnit::get_combat_id() {
	return combat_id;
}

void combat::CombatUnit::receive_attack(Stat stat) {
	this->stat.health -= stat.attack;
	particles::create_blood_particles(2, position, Vector2(0.05f, 0.1f), 2.0f, blood_color);
}