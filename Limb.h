#pragma once
#include <vector>
#include <string>
#include "MountPoint.h"
#include "Mecha.h"
using namespace std;

class Limb
{
public:
	Limb();
	Limb(string);
	Limb(string, bool, float);
	
	string getName();
	void setName(string);

	bool getStatus();
	void setStatus(bool);

	float getLimbMass();
	void setLimbMass(float);

	Mecha* getMecha();
	void setMecha(Mecha*);

	vector<MountPoint*> getMountPoints();
	void addMountPoint(MountPoint*);
	void addMountPointUnreciprocated(MountPoint*);

	void destroy();
	
private:
	string name;
	bool status;
	float limb_mass;
	Mecha* mecha;
	vector<MountPoint*> mountpoints;
	

};

