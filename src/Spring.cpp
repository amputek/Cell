#include "Spring.h"

Spring :: Spring(Vec2f loc, float dep, float dmp, float stf, float ms) : Dust(loc, Vec2f(0,0), dep){
    damping = dmp;
    stiffness = stf; //0.5
    mass = ms;
    springContact = false;
}


//Collide with an outside object (generally the player's location)
void Spring :: collide(Vec2f heroLoc){
    Vec2f d = heroLoc - global;
    float dist = (heroLoc-global).lengthSquared();
    if(dist < 400){
        float angle = atan2(d.y,d.x);
        Vec2f target = Vec2f(global.x + cos(angle) * 20, global.y + sin(angle) * 20);
        Vec2f accel = (target - heroLoc) * (stiffness * 3);
        velocity -= accel;
        springContact = true;
    } else {
        springContact = false;
    }
}

void Spring :: update(Vec2f target){
    Vec2f force = (target-global) * stiffness;
    Vec2f accel = force / mass;
    velocity = (velocity + accel) * damping;
    Dust :: update();
}

void Spring :: addForce(Vec2f force){
    Vec2f accel = force / mass;
    velocity = (velocity + accel) * damping;
}