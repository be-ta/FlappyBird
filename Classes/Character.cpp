//
//  Character.cpp
//  SushiNeko
//
//  Created by Shuhei Asada on 2016/04/26.
//
//

#include "cocos2d.h"
#include "Character.hpp"
#include "Constants.h"

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
    this->accel = GRAVITY_ACCEL;
    
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
        this->accel = GRAVITY_ACCEL * 3.0f;
    }
    else
    {
        this->accel = GRAVITY_ACCEL;
    }
    
    if( this->velocity < -1.0f * JUMP_SPEED ){
        this->velocity = -1.0f * JUMP_SPEED;
    }
    
    this->setPosition( this->getPosition() + Vec2(0, this->velocity * dt) );
}

void Character::jump()
{
    this->velocity = JUMP_SPEED;
}


