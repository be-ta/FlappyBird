//
//  Obstacle.cpp
//  FlappyBird
//
//  Created by Shuhei Asada on 2016/05/12.
//
//

#include "cocos2d.h"
#include "Obstacle.hpp"
#include "Constants.h"

USING_NS_CC;

bool Obstacle::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    // キャラクターのアニメーションのタイムラインを読み込む
    this->timeline = CSLoader::createTimeline("Character.csb");
    this->timeline->retain();
        
    return true;
}

void Obstacle::onExit()
{
    Node::onExit();
    
    // initで呼び出したretainを解放する
    this->timeline->release();
}

void Obstacle::onEnter()
{
    Node::onEnter();
    
    this->scheduleUpdate();
}

void Obstacle::update( float dt )
{
 
}

void Obstacle::moveLeft( float distance )
{
    this->setPosition( this->getPosition() - Vec2(distance,0) );
}
