//
//  Obstacle.hpp
//  FlappyBird
//
//  Created by Shuhei Asada on 2016/05/12.
//
//

#ifndef Obstacle_hpp
#define Obstacle_hpp

#include "cocos2d.h"
//#include "Constants.hpp"
#include "cocostudio/CocoStudio.h"

class Obstacle : public cocos2d::Node
{
public:
    CREATE_FUNC(Obstacle);
    
    bool init() override;
    void onExit() override;
    void update( float dt  ) override;
    void onEnter() override;
    
    void moveLeft( float distance );
protected:
    cocostudio::timeline::ActionTimeline* timeline;
    
};

#endif /* Obstacle_hpp */
