#include "Feeler.hpp"

Feeler :: Feeler(vec2 loc, float depth, int jointCount, float base, float tip ) {
    
    baseWidth = base;
    tipWidth = tip;
    
    float stiffness = 2.0f;
    float mass = 5.0f;
    float damping = 7.0f;
    
    for(int i = 0; i < jointCount; i++){
        
        springs.push_back( new Spring(loc + vec2(i * 2.0f,i * 2.0f), depth, i == 0 ? 10.0f : stiffness, mass, damping ) );
    }

    update();
    feelerContact = false;
};



void Feeler :: collide(const vec2 & heroLoc, float colliderSize ){
    for(int i = 1; i < springs.size(); i++){
        springs.at(i)->collide(heroLoc, colliderSize);
        if(springs.at(i)->contact() == true){
            feelerContact = true;
        }
    }
}

bool Feeler :: feelTowards( const vec2 & colliderPos, float minDist, float force ){
    
    bool activated = false;
    
    
    
    for(int i = 1; i < springs.size(); i++){
    
        float alongRatio = (float)i / springs.size();
        
        Spring * spring = springs.at(i);
        if( glm::distance( spring->getPosition(), colliderPos ) < minDist )
        {
            activated = true;
        }
        if( activated )
        {
            spring->addForce( (colliderPos - spring->getPosition()) * force * alongRatio );
        }
    }
    return activated;
}


//add force - for environmental affects (gravity, flow etc)
void Feeler :: addForce(vec2 force){
    for(int i = 1; i < springs.size(); i++){
        springs.at(i)->addForce(force);
    }
}


void Feeler :: update(){
    feelerContact = false;
    
    //a Feeler's 'global' position is it's BASE point, the first spring gets updated agains this position
    if(springs.size() > 0){
        //springs.at(0)->update(global);
//        springs.at(0)->setPosition( mPosition );
        springs.at(0)->update();
    }
    
    //all other springs gets updated against the prior spring
    for(int i = 1; i < springs.size(); i++){
        springs.at(i)->moveTowards(springs.at(i-1)->getPosition());
        springs.at(i)->update();
    }

}


