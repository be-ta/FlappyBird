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
    auto ground = this->back->getChildByName<Sprite*>("ground");
    ground->setLocalZOrder(1);
    
    auto ground2 = this->back->getChildByName<Sprite*>("ground2");
    ground2->setLocalZOrder(1);
    
    this->grounds.pushBack( ground );
    this->grounds.pushBack( ground2 );
    
    this->state = GameState::Ready;
    
    return true;
}

void MainScene::onEnter()
{
    Layer::onEnter();
    
    setupTouchHandling();
    
    triggerReady();
}

void MainScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        switch( this->state ){
        case GameState::Ready : this->triggerPlaying(); break;
        case GameState::Playing : this->character->jump(); break;
        case GameState::GameOver : {
            auto nextGameScene = MainScene::createScene();
            auto transition = TransitionFade::create( 1.0f, nextGameScene );
            Director::getInstance()->replaceScene(transition);
        }
        break;
        }
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

}

void MainScene::update(float dt)
{
    Rect characterRect = this->character->getRect();
    
    if( this->state == GameState::Playing ){
        
        //障害物の移動
        for( auto obstacle : this->obstacles ){
            obstacle->moveLeft( SCROLL_SPEED_X * dt );
        }
        
        //地面の移動
        for( auto ground : this->grounds ){
            ground->setPosition( ground->getPosition() - Vec2( SCROLL_SPEED_X * dt,0) );
        }
        
        if( this->grounds.back()->getPosition().x < 0 )
        {
            this->grounds.front()->setPosition( Vec2( this->grounds.back()->getPosition().x + this->grounds.back()->getContentSize().width, 100.0f ) );
            this->grounds.swap(0, 1);
        }
        
    }
    
    //障害物とキャラの衝突判定
    for( auto obstacle : this->obstacles ){
        auto obstacleRects = obstacle->getRects();
        
        for( Rect obstacleRect : obstacleRects )
        {
            if( characterRect.intersectsRect( obstacleRect ) != false )
            {
                this->triggerGameOver();
            }
        }
    }
    
    //地面とキャラの衝突判定
    for( auto ground : this->grounds ){
        Rect groundRect = Rect( ground->getPosition() - Vec2( 0.0f, 100.0f ) , Size( ground->getContentSize().width, 100.0f + characterRect.size.height/2 ) );
        
        if( characterRect.intersectsRect( groundRect ) != false )
        {
            this->character->setPosition( this->character->getPositionX(), 100.0f + characterRect.size.height );
            
            this->triggerGameOver();
            this->character->stopFly();
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

void MainScene::triggerReady()
{
    this->state = GameState::Ready;
}

void MainScene::triggerPlaying()
{
    this->state = GameState::Playing;
    this->character->startFly();
    
    this->scheduleUpdate();
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::createObstacle), OBSTACLE_TIME_SPAN);
}

void MainScene::triggerGameOver()
{
    this->state = GameState::GameOver;
    this->unschedule(CC_SCHEDULE_SELECTOR(MainScene::createObstacle));
}
