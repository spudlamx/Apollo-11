#pragma once
#include "point.h"
#include "ground.h"

class LunarModule
{
public:
	// constructor
	LunarModule();
	// methods
	bool groundCollision(Ground ground, double velocity);
	void updatePosition(double dx, double dy, double x, double y, double aDegrees);
	void updateAngle(double aDegrees);
	void updateFuel(bool isTurning, bool isThrustersOn);
	LunarModule getLunarModule();

private:
	// attributes
	double accelerationThrust;
	double ddxThrust;
	double ddyThrust;
	double ddx;
	double ddy;
	double angle;
	double verticalVelocity;
	double horizontalVelocity;
	double thrusters;
	double inertia;
	double fuel;
	double location;
	double weight;
	double totalVelocity;
	double acceleration;
	Point point;
	Ground ground;
};

