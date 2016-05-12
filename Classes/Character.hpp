//
//  Character.hpp
//  SushiNeko
//
//  Created by Shuhei Asada on 2016/04/26.
//
//

#ifndef Character_hpp
#define Character_hpp

#include "cocos2d.h"
//#include "Constants.hpp"
#include "cocostudio/CocoStudio.h"

class Character : public cocos2d::Node
{
public:
    CREATE_FUNC(Character);
        
    bool init() override;
    void onExit() override;
    void update( float dt  ) override;
    void onEnter() override;
    void jump();
    cocos2d::Rect getRect();
    
protected:
    
    cocostudio::timeline::ActionTimeline* timeline;

    float velocity;
    float accel;
    
};

#endif /* Character_hpp */
