#pragma once
#include <vector>
#include <string>
#include "System.h"
#include "Weapon.h"
using namespace std;

class MountPoint
{
public:
	MountPoint();
	MountPoint(string, bool, int, int, float, float, float);
	
	string getName();
	void setName(string);

	bool getStatus();
	void setStatus(bool);

	int getMaxHP();
	void setMaxHP(int);

	int getHP();
	void setHP(int);

	float getTargetingDifficulty();
	void setTargetingDifficulty(float);

	float getArmor();
	void setArmor(float);

	float getArmorRemaining();
	void setArmorRemaining(float);

	void addSystem(System*);
	void addSystemUnreciprocated(System*);
	vector<System*> getAttachedSystems();

	void addWeapon(Weapon*);
	void addWeaponUnreciprocated(Weapon*);
	vector<Weapon*> getAttachedWeapons();

	void addLimb(Limb*);
	void addLimbUnreciprocated(Limb*);
	Limb* getLimb();

	void damage(float, float, float);
	void destroy();


private:
	string name;
	bool status;
	int max_hp;
	int hp;
	float targeting_difficulty;
	float armor;
	float armor_remaining;
	vector<System*> systems;
	vector<Weapon*> weapons;
	Limb* limb;
};

