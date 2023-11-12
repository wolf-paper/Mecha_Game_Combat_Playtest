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
	void setMass(float);

	float getReactionSpeed();
	void setReactionSpeed(float);

	float getEvasion();
	void setEvasion(float);

	float getAccuracy();
	void setAccuracy(float);

	float getTemperature();
	void setTemperature(float);

	float getTemperatureCap();
	void setTemperatureCap(float);
	
private:
	string name;
	bool status;

	float mass;
	float mass_factor;
	float reaction_speed;
	float evasion;
	float accuracy;
	float temperature;
	float temperature_cap;

	vector<Limb*> limbs;
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

	MountPoint* Head;
	MountPoint* LeftShouler;
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