#pragma once
#include <vector>
#include <string>
#include "MountPoint.h"
using namespace std;

class System
{
public:
	System();
	System(string, bool, float, float, int, int);

	string getName();
	void setName(string);

	bool getStatus();
	void setStatus(bool);

	float getEfficacy();
	void setEfficacy(float);

	float getEfficacyCap();
	void setEfficacyCap(float);

	int getPowerExpected();
	void setPowerExpected(int);

	int getPowerAllocated();
	void setPowerAllocated(int);

	vector<System*> getReliantSystems();
	void addReliantSystem(System*);

	vector<MountPoint*> getMountPoints();
	void addMountPoint(MountPoint*);
	void addMountPointUnreciprocated(MountPoint*);

	void updateEfficacy();
	void updateEfficacyCap();

	void destroy();
	void enable();
	void disable();

private:
	string name;
	bool status;
	float efficacy;
	float efficacy_cap;
	float efficacy_cap_buffer;
	int power_expected;
	int power_allocated;
	vector<System*> reliant_systems;
	vector<MountPoint*> mountpoints;

};

