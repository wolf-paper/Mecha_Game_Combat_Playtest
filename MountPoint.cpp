#include <vector>
#include <string>
#include <iostream>
#include "MountPoint.h"
#include "System.h"
#include "Weapon.h"
using namespace std;

MountPoint::MountPoint() {
	name = "";
	status = true;
	max_hp = 500;
	hp = max_hp;
	targeting_difficulty = 25;
	armor = 300;
	armor_remaining = 100;
}

MountPoint::MountPoint(string new_name, bool stat, int maxhp, int currhp, float td, float arm, float ar) {
	name = new_name;
	status = stat;
	max_hp = maxhp;
	hp = currhp;
	targeting_difficulty = td;
	armor = arm;
	armor_remaining = ar;
}

string MountPoint::getName() {
	return name;
}

void MountPoint::setName(string newname) {
	name = newname;
}

bool MountPoint::getStatus() {
	return status;
}

void MountPoint::setStatus(bool stat) {
	status = stat;
}

int MountPoint::getMaxHP() {
	return max_hp;
}
void MountPoint::setMaxHP(int maxhp) {
	max_hp = maxhp;
}

int MountPoint::getHP() {
	return hp;
}
void MountPoint::setHP(int currhp) {
	hp = currhp;
}

float MountPoint::getTargetingDifficulty() {
	return targeting_difficulty;
}

void MountPoint::setTargetingDifficulty(float td) {
	targeting_difficulty = td;
}

float MountPoint::getArmor() {
	return armor;
}
void MountPoint::setArmor(float arm) {
	armor = arm;
}

float MountPoint::getArmorRemaining() {
	return armor_remaining;
}
void MountPoint::setArmorRemaining(float ar) {
	armor_remaining = ar;
}

void MountPoint::addSystem(System* sys) {
	systems.push_back(sys);
	sys->addMountPointUnreciprocated(this);

}
void MountPoint::addSystemUnreciprocated(System* sys){
	systems.push_back(sys);
}

vector<System*> MountPoint::getAttachedSystems() {
	return systems;
}

void MountPoint::addWeapon(Weapon* wep) {
	weapons.push_back(wep);
	wep->addMountPointUnreciprocated(this);

}
void MountPoint::addWeaponUnreciprocated(Weapon* sys) {
	weapons.push_back(sys);
}

vector<Weapon*> MountPoint::getAttachedWeapons() {
	return weapons;
}

void MountPoint::addLimb(Limb* newlimb) {
	limb = newlimb;
	limb->addMountPointUnreciprocated(this);
}


void MountPoint::damage(float dmg, float pen, float shred) {
	float net_damage;
	float pierced_damage;

	net_damage = dmg - (armor * (armor_remaining / 100));
	pierced_damage = (dmg * pen) / (armor * (armor_remaining / 100));

	armor_remaining = armor_remaining - (pierced_damage * shred);
	hp = hp - net_damage;
	hp = hp - pierced_damage;

	if (hp == 0) {
		destroy();
	}
	else {
		cout << this->getLimb()->getMecha()->getName() << "'s " << this->getName() << " has taken " << net_damage + pierced_damage << " damage." << endl;
	}
}

void MountPoint::destroy() {
	hp = 0;
	armor_remaining = 0;
	armor = 0;
	for (Weapon* wep : weapons) {
		wep->destroy();
	}
	cout << this->getLimb()->getMecha()->getName() << "'s " << this->getName() << " has been destroyed." << endl;
}
