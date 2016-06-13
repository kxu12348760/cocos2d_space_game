#ifndef Cocos2DxFirstIosSample_ParallaxNodeExtras_h
#define Cocos2DxFirstIosSample_ParallaxNodeExtras_h

#include "cocos2d.h"

USING_NS_CC;

class ParallaxNodeExtras : public ParallaxNode {

    public :

    // Need to provide a constructor
    ParallaxNodeExtras();

    // just to avoid ugly later cast and also for safety
    static ParallaxNodeExtras * node();

    // Facility method (it’s expected to have it soon in COCOS2DX)
    void incrementOffset(Vec2 offset, Node* node);
} ;

#endif
