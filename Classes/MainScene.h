#ifndef __MAINSCENE_SCENE_H__
#define __MAINSCENE_SCENE_H__

#include "cocos2d.h"
#include "Obstacle.hpp"

class Character;
//cocos2d-xのvectorでは全てのノードがRefを継承している必要があるので、ヘッダーで継承情報をもらう必要がある
//class Obstacle;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void onEnter() override;
    
    void update( float dt ) override;
    
    void play();
    void stop();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    
    Character* character;
    cocos2d::Vector<Obstacle*> obstacles;
    cocos2d::Node* back;
    
    void setupTouchHandling();
    void createObstacle( float dt );
};

#endif // __MAINSCENE_SCENE_H__
