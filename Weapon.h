#pragma once
#include <vector>
#include <string>
#include "MountPoint.h"
#include "Mecha.h"
using namespace std;

class Weapon
{
public:
	Weapon();
	Weapon(string, bool, bool, bool, bool, float, float, float, float, float, int, int, int, bool);

	string getName();
	void setName(string);

	bool getStatus();
	void setStatus(bool);

	bool getInAtmo();
	void setInAtmo(bool);

	bool getInSpace();
	void setInSpace(bool);

	bool getMelee();
	void setMelee(bool);

	float getWeaponMass();
	void setWeaponMass(float);

	float getAccuracy();
	void setAccuracy(float);

	int getDamage();
	void setDamage(int);

	float getPenetration();
	void setPenetration(float);

	float getShred();
	void setShred(float);

	int getAmmo();
	void setAmmo(int);

	int getAmmoCap();
	void setAmmoCap(int);

	int getCooldown();
	void setCooldown(int);

	bool getOnCooldown();
	void setOnCooldown(bool);

	void addMountPoint(MountPoint*);
	void addMountPointUnreciprocated(MountPoint*);

	void attack(Mecha*, Mecha*, MountPoint*);
	void destroy();

private:
	string name;
	bool status;
	bool in_atmo;
	bool in_space;
	bool melee;
	float weapon_mass;
	float accuracy;
	float damage;
	float penetration;
	float shred;
	int ammo;
	int ammo_cap;
	int cooldown;
	bool on_cd;
	MountPoint* mountpoint;
};

