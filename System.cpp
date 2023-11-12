#include <vector>
#include <string>
#include "System.h"
#include "MountPoint.h"
#include "Accord_Combat_Playtest.cpp"
using namespace std;

System::System() {
	name = "";
	status = true;
	efficacy = 100.0;
	efficacy_cap = 200.0;
	power_expected = BASE_POWER_EXPECTED;
	power_allocated = power_expected;
}

System::System(string new_name, bool stat, float eff, float efc, int pex, int pal) {
	name = new_name;
	status = stat;
	efficacy = eff;
	efficacy_cap = efc;
	power_expected = pex;
	power_allocated = pal;
}

string System::getName() {
	return name;
}

void System::setName(string new_name) {
	name = new_name;
}

bool System::getStatus() {
	return status;
}

void System::setStatus(bool stat) {
	status = stat;
}

float System::getEfficacy() {
	return efficacy;
}

void System::setEfficacy(float eff) {
	if (eff <= efficacy_cap) {
		efficacy = eff;
	}
	else {
		efficacy = efficacy_cap;
	}
}

float System::getEfficacyCap() {
	return efficacy_cap;
}

void System::setEfficacyCap(float efc) {
	if (efc <= 200.0) {
		efficacy_cap = efc;
	}
	else {
		efficacy_cap = 200.0;
	}
}

int System::getPowerExpected() {
	return power_expected;
}

void System::setPowerExpected(int pex) {
	power_expected = pex;
}

int System::getPowerAllocated() {
	return power_allocated;
}

void System::setPowerAllocated(int pal) {
	power_allocated = pal;
	updateEfficacy();
}

vector<System*> System::getReliantSystems() {
	return reliant_systems;
}

void System::addReliantSystem(System* rs) {
	reliant_systems.push_back(rs);
}

vector<MountPoint*> System::getMountPoints() {
	return mountpoints;
}

void System::addMountPoint(MountPoint* mnt) {
	mountpoints.push_back(mnt);
	mnt->addSystemUnreciprocated(this);
}

void System::addMountPointUnreciprocated(MountPoint* mnt) {
	mountpoints.push_back(mnt);
}

void System::destroy() {
	setStatus(false);
	setEfficacyCap(0.0);
	setPowerAllocated(0);
}

void System::disable() {
	setEfficacyCap(0.0);
	setPowerAllocated(0);
}

void System::updateEfficacy() {
	float power_ratio = power_allocated / power_expected;

	efficacy = efficacy * power_ratio;

	if (efficacy >= efficacy_cap) {
		efficacy = efficacy_cap;
	}
}

void System::updateEfficacyCap() {
	int mnt_destroyed;
	int mnt_total;

	mnt_destroyed = 0;
	mnt_total = mountpoints.size();
	for (MountPoint* mnt : mountpoints) {
		if (!mnt->getStatus()) {
			mnt_destroyed++;
		}
	}

	if (mnt_destroyed == mnt_total) {
		destroy();
	}

	efficacy_cap = efficacy_cap - ((efficacy_cap / mnt_total) * mnt_destroyed);
	
	float power_ratio;

	power_ratio = power_allocated / power_expected;
	if (power_ratio >= MAXIMUM_THRESHOLD) {
		efficacy_cap = efficacy_cap - power_ratio;
	}

	updateEfficacy();
}