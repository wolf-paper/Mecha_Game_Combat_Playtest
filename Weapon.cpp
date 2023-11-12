#include <vector>
#include <string>
#include "Weapon.h"
#include "Mecha.h"
#include "Accord_Combat_Playtest.cpp"

Weapon::Weapon() {
	name = "";
	status = true;
	in_atmo = true;
	in_space = true;
	melee = false;
	weapon_mass = 1.5;
	accuracy = 85;
	damage = 250;
	penetration = 20;
	shred = 0.5;
	ammo_cap = 10;
	ammo = ammo_cap;
	cooldown = 0;
	on_cd = false;
}

Weapon::Weapon(string new_name, bool stat, bool inatmo, bool inspace, bool mel, float wma, float wac, float dmg, float pen, float srd, int amo, int amc, int cd, bool oncd) {
	name = "";
	status = true;
	in_atmo = true;
	in_space = true;
	melee = false;
	weapon_mass = 1.5;
	accuracy = 85;
	damage = 250;
	penetration = 20;
	shred = 0.5;
	ammo_cap = 10;
	ammo = ammo_cap;
	cooldown = cd;
	on_cd = oncd;
}


string Weapon::getName() {
	return name;
}

void Weapon::setName(string newname) {
	name = newname;
}

bool Weapon::getStatus() {
	return status;
}
void Weapon::setStatus(bool stat) {
	status = stat;
}

bool Weapon::getInAtmo() {
	return in_atmo;
}
void Weapon::setInAtmo(bool inatmo) {
	in_atmo = inatmo;
}

bool Weapon::getInSpace() {
	return in_space;
}
void Weapon::setInSpace(bool inspace) {
	in_space = inspace;
}

bool Weapon::getMelee() {
	return melee;
}
void Weapon::setMelee(bool mel) {
	melee = mel;
}

float Weapon::getWeaponMass() {
	return weapon_mass;
}
void Weapon::setWeaponMass(float wma) {
	weapon_mass = wma;
}

float Weapon::getAccuracy() {
	return accuracy;
}
void Weapon::setAccuracy(float wac) {
	accuracy = wac;
}

int Weapon::getDamage() {
	return damage;
}
void Weapon::setDamage(int dmg) {
	damage = dmg;
}

float Weapon::getPenetration() {
	return penetration;
}
void Weapon::setPenetration(float pen) {
	penetration = pen;
}

float Weapon::getShred() {
	return shred;
}
void Weapon::setShred(float srd) {
	shred = srd;
}

int Weapon::getAmmo() {
	return ammo;
}
void Weapon::setAmmo(int amo) {
	ammo = amo;
}

int Weapon::getAmmoCap() {
	return ammo_cap;
}
void Weapon::setAmmoCap(int cap) {
	ammo_cap = cap;
}

int Weapon::getCooldown() {
	return cooldown;
}
void Weapon::setCooldown(int cd) {
	cooldown = cd;
}

bool Weapon::getOnCooldown() {
	return on_cd;
}
void Weapon::setOnCooldown(bool oncd) {
	on_cd = oncd;
}

void Weapon::addMountPoint(MountPoint* mp) {
	mountpoint = mp;
	mp->addWeaponUnreciprocated(this);
}
void Weapon::addMountPointUnreciprocated(MountPoint* mp) {
	mountpoint = mp;
}

void Weapon::attack(Mecha* actor, Mecha* other, MountPoint* target) {
	if ((mountpoint->getStatus()) && (!on_cd) && (ammo != 0)) {
		float threshold = (accuracy * actor->getAccuracy()) * (1 - (actor->getEvasion()/100));
		int roll = rand() % 100;
		if (roll <= threshold) {
			float dmg = damage;
			if (roll <= target->getTargetingDifficulty()) {
				vector<MountPoint*> mps = target->getLimb()->getMountPoints();
				int index = rand() % mps.size();
				while (!mps.at(index)->getStatus()) {
					index = rand() % mps.size();
				}
				if (mps.at(index) != target) {
					target = mps.at(index);
				}
				else {
					cout << actor->getName() << "'s attack has missed." << endl;
					return;
				}
			}
			if (melee) {
				dmg = (damage * (target->getLimb()->getLimbMass() + weapon_mass) * actor->getThrust());
			}
			target->damage(dmg, penetration, shred);
		}
		else {
			cout << actor->getName() << "'s attack has missed." << endl;
		}
	}
}
void Weapon::destroy() {

}