#include "Player.hpp"


Player :: Player(const vec2 & loc) : Braitenberg(loc, true, 5.0f, 0.5f){
    level = 1;
    longTail = new Tail( 10, true, 2, false);
    leftTail = new Tail( 2, false, 3, false);
    rightTail = new Tail( 2, false, 3, false);
    playerLevelling = false;
    falling = false;

    
    for(int i = 0; i < 7; i ++){
        planktonEaten.push_back(0);
    }

    
}


//move to a specified location
void Player :: moveTo(vec2 mousePos){
    
    
    setDestination( globalise(mousePos, 1) );

    Braitenberg::moveTo( targetDestination );
    
}

void Player :: slow(bool t){
    if(t == true){
        mSpeed = 0.15f;
    } else {
        mSpeed = 0.5f;
    }
}


void Player :: update(float deltaTime){
    
    falling = mPosition.y < -7000;
    
    //check if player is in the process of 'levelling up'
    if(playerLevelling == true){
        levelCount++;
        if(levelCount >= 40){       //player levels up for 40 ticks
            playerLevelling = false;
        }
    }
    
    //update tails
    longTail->update(vec2(mPosition.x - sin(mDirection) * mRadius, mPosition.y - cos(mDirection) * mRadius), mDirection);
    leftTail->update(vec2(mPosition.x - sin(mDirection - 1.0) * mRadius, mPosition.y - cos(mDirection - 1.0) * mRadius), mDirection);
    rightTail->update(vec2(mPosition.x - sin(mDirection + 1.0) * mRadius, mPosition.y - cos(mDirection + 1.0) * mRadius), mDirection);
    
}


void Player:: draw( CellRenderer & renderer ){
    
    renderer.drawPlayer(mPosition, mDirection, mRadius, bodyType);
    longTail->draw( renderer );
    if( sideTailsOn )
    {
        leftTail->draw( renderer );
        rightTail->draw( renderer );
    }
}

//returns number of eaten plankton
int Player :: getEaten(){
    int eaten = 0;
    for(int i = 0; i < planktonEaten.size(); i++){
        eaten += planktonEaten.at(i);
    }
    return eaten;
}

void Player :: levelUp(){
    level++;
    
    if(level < 40 && level % 3 == 0){
        mRadius++;
    }
    if(level == 20){ bodyType = 1;        }
    if(level == 20){ sideTailsOn = true;  }
    if(level == 40){ bodyType = 2;        }
    if(level == 12){ longTail->setWide(); }
    if(level == 35){ longTail->setFins(); }
    
    if(level > 20){
        leftTail->incLength(0.5);
        rightTail->incLength(0.5);
    }
    
    playerLevelling = true;
    levelCount = 0;
    longTail->incLength(0.5);
    longTail->incWidth(0.02);


}
