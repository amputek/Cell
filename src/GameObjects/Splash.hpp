#ifndef Splash_hpp
#define Splash_hpp

#include <iostream>
#include "Finite.hpp"


using namespace ci;

class Splash : public Finite, public IDrawable{
public:
    Splash(vec2 position, float size, int lifetime, float depth ) : Finite( position, lifetime, size, depth )
    {
        mStartSize = size;
    }
    
    void draw( CellRenderer & cellRenderer ){
        cellRenderer.drawSplash( mPosition, currentLife, maxLife, mStartSize );
    }

private:
    float mStartSize;
};


#endif
