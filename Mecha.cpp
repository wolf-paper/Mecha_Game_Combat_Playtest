#include <vector>
#include <string>
#include "Mecha.h"
#include "Limb.h"
#include "MountPoint.h"
#include "Weapon.h"
#include "System.h"

using namespace std;

Mecha::Mecha() {
	name = "";
	status = true;
	power_override = false;

	mass = 0.0; // in metric tons
	height = 1.0; // in meters
	mass_factor = mass / height;
	reaction_speed = (mass_factor - 1) * 100;
	evasion = 0.0;
	accuracy = 0.0;
	thrust = 0.0;
	temperature = 0.0;
	temperature_cap = 200;

	// Initializing MountPoints: Head...
	vector<MountPoint*> head_mps = { Skull };
	Skull = new MountPoint("Head");
	
	// Initializing MountPoints: Torso...
	vector<MountPoint*> torso_mps = { LeftShoulder, RightShoulder, Chest, Stomach, InnerChest };
	LeftShoulder = new MountPoint("Left Shoulder");
	RightShoulder = new MountPoint("Right Shoulder");
	Chest = new MountPoint("Chest");
	InnerChest = new MountPoint("Inner Chest");
	Stomach = new MountPoint("Stomach");

	// Initializing MountPoints: Arms...
	vector<MountPoint*> l_arm_mps = { UpperLeftArm, LowerLeftArm, LeftHand };
	UpperLeftArm = new MountPoint("Upper Left Arm");
	LowerLeftArm = new MountPoint("Lower Left Arm");
	LeftHand = new MountPoint("Left Hand");

	vector<MountPoint*> r_arm_mps = { UpperRightArm, LowerRightArm, RightHand };
	UpperRightArm = new MountPoint("Upper Right Arm");
	LowerRightArm = new MountPoint("Lower Right Arm");
	RightHand = new MountPoint("Right Hand");

	// Initializing MountPoints: Legs...
	vector<MountPoint*> l_leg_mps = { UpperLeftLeg, LowerLeftLeg, LeftFoot };
	UpperLeftLeg = new MountPoint("Upper Left Leg");
	LowerLeftLeg = new MountPoint("Lower Left Leg");
	LeftFoot = new MountPoint("Left Foot");

	vector<MountPoint*> r_leg_mps = { UpperRightLeg, LowerRightLeg, RightFoot };
	UpperRightLeg = new MountPoint("Upper Right Leg");
	LowerRightLeg = new MountPoint("Lower Right Leg");
	RightFoot = new MountPoint("Right Foot");

	// Initializing Limbs...

	addLimbDeclared(Head, "Head", head_mps);
	addLimbDeclared(Torso, "Torso", torso_mps);
	addLimbDeclared(LeftArm, "Left Arm", l_arm_mps);
	addLimbDeclared (RightArm, "Right Arm", r_arm_mps);
	addLimbDeclared(LeftLeg, "Left Leg", l_leg_mps);
	addLimbDeclared(RightLeg, "Right Leg", r_leg_mps);

	// Initializing Systems...
	vector<MountPoint*> targeting_mps = { Skull, LowerLeftArm, LowerRightArm };
	vector<MountPoint*> sensor_mps = { Skull, Chest };
	vector<MountPoint*> thruster_mps = { Chest, UpperLeftLeg, LowerLeftLeg, UpperRightLeg, LowerRightLeg };
	vector<MountPoint*> power_mps = { InnerChest, Stomach };
	vector<MountPoint*> coolant_mps = { Chest, InnerChest, Stomach };
	vector<MountPoint*> cockpit_mps = { InnerChest };
	addSystemDeclared(Targeting, "Targeting", targeting_mps);
	addSystemDeclared(Sensors, "Sensors", sensor_mps);
	addSystemDeclared(Thrusters, "Thrusters", thruster_mps);
	addSystemDeclared(Power, "Power", power_mps);
	addSystemDeclared(Coolant, "Coolant", coolant_mps);
	addSystemDeclared(Cockpit, "Life Support", cockpit_mps);

	// Establishing Reliant Systems...
	for (System* sys : systems) {
		sys->addReliantSystem(Power);
	}
	Targeting->addReliantSystem(Sensors);

	// Establishing Controllable and Key Systems
	controllable_systems = { Targeting, Sensors, Thrusters, Coolant };
	key_systems = { Sensors, Power, Cockpit };

	// Initialization Complete
}

string Mecha::getName() {
	return name;
}
void Mecha::setName(string newname) {
	name = newname;
}

bool Mecha::getStatus() {
	return status;
}
void Mecha::setStatus(bool stat) {
	status = stat;
}

float Mecha::getMass() {
	return mass;
}
void Mecha::updateMass() {
	mass = 0;
	for (Limb* limb : limbs) {
		mass += limb->getLimbMass();
	}
	updateMassFactor;
	updateReactionSpeed;
}

float Mecha::getHeight() {
	return height;
}
void Mecha::setHeight(float newheight) {
	height = newheight;
}

float Mecha::getMassFactor() {
	return mass_factor;
}
void Mecha::updateMassFactor() {
	mass_factor = mass / height;
}

float Mecha::getReactionSpeed() {
	return reaction_speed * (Sensors->getEfficacy() / 100);
}
float Mecha::getBaseSpeed() {
	return reaction_speed;
}
void Mecha::updateReactionSpeed() {
	reaction_speed = (mass_factor - 1) * 100;
}
void Mecha::setReactionSpeed(float spd) {
	reaction_speed = spd;
}

float Mecha::getEvasion() {
	return evasion * (Thrusters->getEfficacy() / 100);
}
float Mecha::getBaseEvasion() {
	return evasion;
}
void Mecha::setEvasion(float eva) {
	evasion = eva;
}

float Mecha::getAccuracy() {
	return accuracy * ((Sensors->getEfficacy() * Targeting->getEfficacy()) / 10000);
}
float Mecha::getBaseAccuracy() {
	return accuracy;
}
void Mecha::setAccuracy(float acc) {
	accuracy = acc;
}

float Mecha::getThrust() {
	return thrust * (Thrusters->getEfficacy() / 100);
}
float Mecha::getBaseThrust() {
	return thrust;
}
void Mecha::setThrust(float thr) {
	thrust = thr;
}

float Mecha::getTemperature() {
	return temperature;
}
void Mecha::updateTemperature() {
	if (Power->getEfficacy() == 0) {
		temperature -= (temperature_cap / 10);
		if (power_override && (temperature <= (temperature_cap * .65))) {
			power_override = false;
			Power->enable();
			Power->setPowerAllocated(BASE_POWER_EXPECTED);
		}
	}
	else if (Power->getEfficacyCap() == 200) {
		temperature += (.05 * temperature_cap);
	}
	else {
		temperature += ((.05 * temperature_cap) / (1 - (Power->getEfficacyCap() / 200))); 
	}
	if (temperature >= temperature_cap) {
		power_override = true;
		Power->disable();
	}
}
void Mecha::activateCoolant() {
	temperature -= (.02 * (Coolant->getEfficacy() / 100) * temperature_cap);
}
void Mecha::setTemperature(float tmp) {
	temperature = tmp;
	updateTemperature();
	activateCoolant(); // Any forcible changes to temperature would cause coolant to kick in preemptively
}

float Mecha::getTemperatureCap() {
	return temperature_cap;
}
void Mecha::setTemperatureCap(float tmc) {
	temperature_cap = tmc;
	updateTemperature();
	activateCoolant(); // Any forcible changes to temperature cap would cause coolant to kick in preemptively
}

vector<Limb*> Mecha::getLimbs() {
	return limbs;
}
void Mecha::addLimb(Limb* limb, vector<MountPoint*> mps) {
	for (MountPoint* mp : mps) {
		limb->addMountPoint(mp);
	}
	limbs.push_back(limb);
	limb->setMecha(this);
}
void Mecha::addLimbDeclared(Limb* limb, string name, vector<MountPoint*> mps) {
	limb = new Limb(name);
	addLimb(limb, mps);
}

vector<System*> Mecha::getSystems() {
	return systems;
}
void Mecha::addSystem(System* sys, vector<MountPoint*> mps) {
	for (MountPoint* mp : mps) {
		sys->addMountPoint(mp);
	}
	systems.push_back(sys);
}
void Mecha::addSystemDeclared(System* sys, string name, vector<MountPoint*> mps) {
	sys = new System(name);
	addSystem(sys, mps);
}

vector<System*> Mecha::getControllableSystems() {
	return controllable_systems;
}
void Mecha::addControllableSystem(System* sys) {
	controllable_systems.push_back(sys);
}

vector<System*> Mecha::getKeySystems() {
	return key_systems;
}
void Mecha::addKeySystem(System* sys) {
	key_systems.push_back(sys);
}

vector<Weapon*> Mecha::getWeapons() {
	return weapons;
}
void Mecha::addWeapon(Weapon* wep, MountPoint* mp) {
	weapons.push_back(wep);
	wep->addMountPoint(mp);
}