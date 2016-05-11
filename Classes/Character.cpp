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
    
    return true;
}

void Character::onExit()
{
    Node::onExit();
    
    // initで呼び出したretainを解放する
    this->timeline->release();
}
