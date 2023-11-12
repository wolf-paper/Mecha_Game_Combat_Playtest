#pragma once
#include <vector>
#include <string>
#include "Limb.h"
#include "MountPoint.h"
#include "System.h"
#include "Weapon.h"
using namespace std;


#define BASE_POWER_EXPECTED 100
#define MAXIMUM_THRESHOLD 1.35

class Mecha
{
public:
	Mecha();

	string getName();
	void setName(string);

	bool getStatus();
	void setStatus(bool);
	
	float getMass();
	void updateMass();

	float getHeight();
	void setHeight(float);

	float getMassFactor();
	void updateMassFactor();

	float getReactionSpeed();
	float getBaseSpeed();
	void updateReactionSpeed();
	void setReactionSpeed(float);

	float getEvasion();
	float getBaseEvasion();
	void setEvasion(float);

	float getAccuracy();
	float getBaseAccuracy();
	void setAccuracy(float);

	float getThrust();
	float getBaseThrust();
	void setThrust(float);

	float getTemperature();
	void updateTemperature();
	void activateCoolant(); // Don't like this tbh
	void setTemperature(float);

	float getTemperatureCap();
	void setTemperatureCap(float);
	
	vector<Limb*> getLimbs();
	void addLimb(Limb*, vector<MountPoint*>);
	void addLimbDeclared(Limb*, string, vector<MountPoint*>);

	vector<System*> getSystems();
	void addSystem(System*, vector<MountPoint*>);
	void addSystemDeclared(System*, string, vector<MountPoint*>);

	vector<System*> getControllableSystems();
	void addControllableSystem(System*);

	vector<System*> getKeySystems();
	void addKeySystem(System*);

	vector<Weapon*> getWeapons();
	void addWeapon(Weapon*, MountPoint*);

private:
	string name;
	bool status;
	bool power_override;

	float mass;
	float height;
	float mass_factor;
	float reaction_speed;
	float evasion;
	float accuracy;
	float thrust;
	float temperature;
	float temperature_cap;
	float power_generated;
	float power_allocated;
	float power_available;

	vector<Limb*> limbs;
	vector<System*> systems;
	vector<System*> controllable_systems;
	vector<System*> key_systems;
	vector<Weapon*> weapons;

	System* Targeting;
	System* Sensors;
	System* Thrusters;
	System* Power;
	System* Coolant;
	System* Cockpit;

	Limb* Head;
	Limb* Torso;
	Limb* LeftArm;
	Limb* RightArm;
	Limb* LeftLeg;
	Limb* RightLeg;

	MountPoint* Skull;
	MountPoint* LeftShoulder;
	MountPoint* RightShoulder;
	MountPoint* Chest;
	MountPoint* Stomach;
	MountPoint* InnerChest;
	MountPoint* UpperLeftArm;
	MountPoint* LowerLeftArm;
	MountPoint* LeftHand;
	MountPoint* UpperRightArm;
	MountPoint* LowerRightArm;
	MountPoint* RightHand;
	MountPoint* UpperLeftLeg;
	MountPoint* LowerLeftLeg;
	MountPoint* LeftFoot;
	MountPoint* UpperRightLeg;
	MountPoint* LowerRightLeg;
	MountPoint* RightFoot;


};