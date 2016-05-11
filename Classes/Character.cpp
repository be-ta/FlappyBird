//
//  Character.cpp
//  SushiNeko
//
//  Created by Shuhei Asada on 2016/04/26.
//
//

#include "cocos2d.h"
#include "Character.hpp"

USING_NS_CC;


bool Character::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    // キャラクターのアニメーションのタイムラインを読み込む
    this->timeline = CSLoader::createTimeline("Character.csb");
    this->timeline->retain();
    
    this->velocity = 0.0f;
    this->accel = -2000.0f;
    
    return true;
}

void Character::onExit()
{
    Node::onExit();
    
    // initで呼び出したretainを解放する
    this->timeline->release();
}

void Character::onEnter()
{
    Node::onEnter();
    
    this->scheduleUpdate();
    
    this->jump();
}

void Character::update( float dt )
{
    this->velocity += this->accel * dt;
    
    if( this->velocity > 0 ){
        this->accel = -6000.0f;
    }
    else
    {
        this->accel = -2000.0f;
    }
    
    if( this->velocity < -2000.0f ){
        this->velocity = -2000.0f;
    }
    
    this->setPosition( this->getPosition() + Vec2(0, this->velocity * dt) );
}

void Character::jump()
{
    this->velocity = 1000.0f;
}


