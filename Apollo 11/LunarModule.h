#pragma once
#include "point.h"
#include "ground.h"
#include "Physics.h"

class LunarModule
{
private:
    double dx;
    double dy;
    double y;
    double x;
    double aDegrees;
    double t = 0.1;
    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust 
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double thrusters;
    double inertia;
    Point location;
    double weight = 15103.000;
    double width;
    double totalVelocity;
    double acceleration;
    int fuel;
    Point point;
    Ground ground;
    Physics physics;
    double MAX_LANDING_SPEED;

public:
    LunarModule(const Point& ptUpperRight) : ground(ptUpperRight) {
            // Other initialization code if needed
        }
    bool groundCollision(Ground ground, double velocity) {
        bool isCollide = false;
        if (ground.getElevation(point) <= 0) {
            if(ground.hitGround(point, width)) {
                isCollide = true;
            }
        }
        else if (ground.onPlatform(point, width)) {
            if (velocity >= MAX_LANDING_SPEED) {
                isCollide = true;
            }
            else {
                isCollide = false;
            }
        }
  
        return isCollide;

    }

    void updatePhysics(double dx, double dy, double x, double y, double aDegrees) {
        /*double dist = physics.computeDistance(dx, dy, aDegrees, t);
        double distX = physics.computeHoriztalComponent(acceleration, dist);
        double distY = physics.computeVerticalComponent(acceleration, dist);
        dx = dx + distX;
        dy = dy + distY;*/

        aRadians = physics.radians(aDegrees);
        accelerationThrust = physics.computeAcceleration(THRUST, WEIGHT);
        ddxThrust = physics.computeHoriztalComponent(aRadians, accelerationThrust);
        ddyThrust = physics.computeVerticalComponent(aRadians, accelerationThrust);
        ddx = ddxThrust;
        ddy = ddyThrust + GRAVITY;
        
        dx = physics.computeVelocity(dx, ddx, t);
        dy = physics.computeVelocity(dy, ddy, t);
        x = physics.computeDistance(x, dx, ddx, t);
        y = physics.computeDistance(y, dy, ddy, t);
        totalVelocity = physics.computeTotalComponent(dx, dy);
    }

    void updateAngle(double angle) {
        aDegrees = angle;
    }
    void move(const Interface *pUI){
        ogstream gout;
        if (pUI->isRight())
           updateAngle(aDegrees -= 1);
            updatePhysics(dx, dx, x, y, aDegrees);
        if (pUI->isLeft())
            updateAngle(aDegrees += 1);
            updatePhysics(dx, dx, x, y, aDegrees);
        
         if (pUI->isDown()){
             updatePhysics(dx, dx, x, y, aDegrees);
             location.addY(ddy);
             location.addX(0 - ddx);
         }else{
             location.addY(GRAVITY);
         }
        
        ground.draw(gout);

        // draw the lander and its flames
        gout.drawLander(location /*position*/, aRadians /*angle*/);
        gout.drawLanderFlames(location, aRadians, /*angle*/
                         pUI->isDown(), pUI->isLeft(), pUI->isRight());

        // put some text on the screen
        gout.setPosition(Point(30.0, 30.0));
        gout << "Demo (" << (int)location.getX() << ", " << (int)location.getY() << ")" << "\n";
    }

    void updateFuel(bool isTurning, bool isThrustersOn) {
        
        if(fuel > 0) {
            if (isTurning) {
                fuel -= 1;
            }
            if (isThrustersOn) {
                fuel -= 10;
            }
        }
    }


};



