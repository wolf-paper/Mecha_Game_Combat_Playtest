#include "Limb.h"
#include <vector>
#include "MountPoint.h"

Limb::Limb() {
	name = "";
	status = true;
	limb_mass = 5.0;
}
Limb::Limb(string newname) {
	name = newname;
	status = true;
	limb_mass = 5.0;
}

Limb::Limb(string new_name, bool stat, float lma) {
	name = new_name;
	status = stat;
	limb_mass = lma;
}

string Limb::getName() {
	return name;
}
void Limb::setName(string new_name) {
	name = new_name;
}

bool Limb::getStatus() {
	return status;
}
void Limb::setStatus(bool stat) {
	status = stat;
}

float Limb::getLimbMass() {
	return limb_mass;
}
void Limb::setLimbMass(float lma) {
	limb_mass = lma;
}

Mecha* Limb::getMecha() {
	return mecha;
}
void Limb::setMecha(Mecha* newmecha) {
	mecha = newmecha;
}

vector<MountPoint*> Limb::getMountPoints() {
	return mountpoints;
}
void Limb::addMountPoint(MountPoint* frame) {
	mountpoints.push_back(frame);
	frame->addLimbUnreciprocated(this);
}
void Limb::addMountPointUnreciprocated(MountPoint* frame) {
	mountpoints.push_back(frame);
}

void Limb::destroy() {
	status = false;
	limb_mass = 0;
	for (MountPoint* frame : mountpoints) {
		frame->destroy();
	}
}