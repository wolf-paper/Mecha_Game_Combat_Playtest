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

	// Initializing Systems...
	systems = { Targeting, Sensors, Thrusters, Power, Coolant, Cockpit };
	controllable_systems = { Targeting, Sensors, Thrusters, Coolant };
	key_systems = { Sensors, Power, Cockpit };
	for (System* system : systems) {
		system = new System();
	}
	Targeting->setName("Targeting");
	Sensors->setName("Sensors");
	Thrusters->setName("Thrusters");
	Power->setName("Power");
	Coolant->setName("Coolant");
	Cockpit->setName("Life Support");

	// Initializing Limbs...
	limbs = { Head, Torso, LeftArm, RightArm, LeftLeg, RightLeg };
	for (Limb* limb : limbs) {
		limb = new Limb();
		limb->setMecha(this);
	}
	Head->setName("Head");
	Torso->setName("Torso");
	LeftArm->setName("Left Arm");
	RightArm->setName("Right Arm");
	LeftLeg->setName("Left Leg");
	RightLeg->setName("Right Leg");

	// Initializing MountPoints: Head...
	Skull = new MountPoint();
	Skull->setName("Head");
	Head->addMountPoint(Skull);

	// Initializing MountPoints: Torso...
	vector<MountPoint*> torso_mps = { LeftShoulder, RightShoulder, Chest, Stomach, InnerChest };
	for (MountPoint* mp : torso_mps) {
		mp = new MountPoint();
		Torso->addMountPoint(mp);
	}
	LeftShoulder->setName("Left Shoulder");
	RightShoulder->setName("Right Shoulder");
	Chest->setName("Chest");
	InnerChest->setName("Inner Chest");
	Stomach->setName("Stomach");

	// Initializing MountPoints: Arms...
	vector<MountPoint*> l_arm_mps = { UpperLeftArm, LowerLeftArm, LeftHand };
	for (MountPoint* mp : l_arm_mps) {
		mp = new MountPoint();
		LeftArm->addMountPoint(mp);
	}
	UpperLeftArm->setName("Upper Left Arm");
	LowerLeftArm->setName("Lower Left Arm");
	LeftHand->setName("Left Hand");

	vector<MountPoint*> r_arm_mps = { UpperRightArm, LowerRightArm, RightHand };
	for (MountPoint* mp : r_arm_mps) {
		mp = new MountPoint();
		RightArm->addMountPoint(mp);
	}
	UpperRightArm->setName("Upper Right Arm");
	LowerRightArm->setName("Lower Right Arm");
	RightHand->setName("Right Hand");

	// Initializing MountPoints: Legs...
	vector<MountPoint*> l_leg_mps = { UpperLeftLeg, LowerLeftLeg, LeftFoot };
	for (MountPoint* mp : l_leg_mps) {
		mp = new MountPoint();
		LeftLeg->addMountPoint(mp);
	}
	UpperLeftLeg->setName("Upper Left Leg");
	LowerLeftLeg->setName("Lower Left Leg");
	LeftFoot->setName("Left Foot");

	vector<MountPoint*> r_leg_mps = { UpperRightLeg, LowerRightLeg, RightFoot };
	for (MountPoint* mp : r_leg_mps) {
		mp = new MountPoint();
		RightLeg->addMountPoint(mp);
	}
	UpperRightLeg->setName("Upper Right Leg");
	LowerRightLeg->setName("Lower Right Leg");
	RightFoot->setName("Right Foot");

	// Establishing Reliant Systems...
	for (System* sys : systems) {
		sys->addReliantSystem(Power);
	}
	Targeting->addReliantSystem(Sensors);

	// Connecting Systems to MountPoint...
	Targeting->addMountPoint(Skull);
	Targeting->addMountPoint(LowerLeftArm);
	Targeting->addMountPoint(LowerRightArm);
	Sensors->addMountPoint(Skull);
	Sensors->addMountPoint(Chest);
	Thrusters->addMountPoint(Chest);
	Thrusters->addMountPoint(UpperLeftLeg);
	Thrusters->addMountPoint(LowerLeftLeg);
	Thrusters->addMountPoint(UpperRightLeg);
	Thrusters->addMountPoint(LowerRightLeg);
	Power->addMountPoint(InnerChest);
	Power->addMountPoint(Stomach);
	Coolant->addMountPoint(Chest);
	Coolant->addMountPoint(InnerChest);
	Coolant->addMountPoint(Stomach);
	Cockpit->addMountPoint(InnerChest);

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
	else {
		temperature += ((.05 * temperature_cap) * (Power->getEfficacy() / 100));
	}

}