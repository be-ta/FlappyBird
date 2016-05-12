#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Character.hpp"
#include "CharacterReader.hpp"

#include "Obstacle.hpp"
#include "ObstacleReader.hpp"

#include "Constants.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    instance->registReaderObject("ObstacleReader", (ObjectFactory::Instance) ObstacleReader::getInstance);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    
    //Cocosのバグ修正のために以下の３行を追加
    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    
    addChild(rootNode);
    
    this->back = rootNode->getChildByName("back");
    this->character = back->getChildByName<Character*>("character");
    
    this->character->setLocalZOrder(1);
    auto ground = this->back->getChildByName("ground");
    ground->setLocalZOrder(1);
    
    return true;
}

void MainScene::onEnter()
{
    Layer::onEnter();
    
    setupTouchHandling();
    
    this->scheduleUpdate();
    
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::createObstacle), OBSTACLE_TIME_SPAN);
}

void MainScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        this->character->jump();
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

}

void MainScene::update(float dt)
{
    //障害物の移動
    for( auto obstacle : this->obstacles ){
        obstacle->moveLeft( SCROLL_SPEED_X * dt );
    }
        
    //障害物とキャラの衝突判定
    Rect characterRect = this->character->getRect();
    for( auto obstacle : this->obstacles ){
        auto obstacleRects = obstacle->getRects();
        
        for( Rect obstacleRect : obstacleRects )
        {
            if( characterRect.intersectsRect( obstacleRect ) != false )
            {
                  //this->unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::step));
            }
        }
    }
    
}

void MainScene::createObstacle( float dt )
{
    Obstacle* obstacle = dynamic_cast<Obstacle*>(CSLoader::createNode("Obstacle.csb"));
    this->obstacles.pushBack( obstacle );
    this->back->addChild( obstacle );
    
    float obstacleY = ( OBSTACLE_MAX_Y - OBSTACLE_MIN_Y ) * CCRANDOM_0_1() + OBSTACLE_MIN_Y;
    obstacle->setPosition( Vec2( OBSTACLE_INIT_X, obstacleY ) );
    
    if( this->obstacles.size() > OBSTACLE_LIMIT )
    {
        this->obstacles.front()->removeFromParent();
        this->obstacles.erase(this->obstacles.begin());
    }
}
