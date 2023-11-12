#pragma once
#include <vector>
#include <string>
#include "MountPoint.h"
using namespace std;

class Limb
{
public:
	Limb();
	Limb(string, bool, float);
	
	string getName();
	void setName(string);

	bool getStatus();
	void setStatus(bool);

	float getLimbMass();
	void setLimbMass(float);

	vector<MountPoint*> getMountPoints();
	void addMountPoint(MountPoint*);

	void destroy();
	
private:
	string name;
	bool status;
	float limb_mass;
	vector<MountPoint*> mountpoints;
};

