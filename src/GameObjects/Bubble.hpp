#ifndef Bubble_hpp
#define Bubble_hpp

#include <iostream>
#include "Dust.hpp"

class Bubble : public Dust{
public:
    Bubble( const vec2 & loc, vec2 const & vel, float d, gl::TextureRef * tex);
    bool alive();
    void draw();
    
private:
    gl::TextureRef * img;
    float opacity;
    
};


#endif
