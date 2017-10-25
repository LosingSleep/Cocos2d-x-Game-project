//
//  LevelInfoScene.cpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/16.
//
//

#include "LevelInfoScene.hpp"

#include "GamePlayLayer.hpp"
#include "LevelScene.h"
#include "GameManager.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define STAR_NUMBER (3)

LevelInfoScene::LevelInfoScene()
:info(NULL)
,fileName("")
{
}

LevelInfoScene::~LevelInfoScene(){}

Scene* LevelInfoScene::createScene()
{
    Scene *scene = Scene::create();
    LevelInfoScene *layer = LevelInfoScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelInfoScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto instance = GameManager::getInstance();
    instance->clearGameManager();
    
    log("%s", FileUtils::getInstance()->getWritablePath().c_str());
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameResouce.plist");
    fileName =  UserDefault::getInstance()->getStringForKey("nextLevelFile");
    if( fileName == "") {
        fileName = "levelInfo_0.plist";
    }
   
	//add null stars
    Size size = Director::getInstance()->getVisibleSize();
    auto starWidth = Sprite::createWithSpriteFrameName("star1_bg.png")->getContentSize().width;
    auto startPosX = (size.width - STAR_NUMBER * starWidth) / 2 ;
    for(int i = 1; i <= STAR_NUMBER; i++) {
        auto sprite = Sprite::createWithSpriteFrameName("star1_bg.png");
        sprite->setPosition(Point(startPosX + (i - 1) * starWidth, size.height/ 2));
        sprite->setAnchorPoint(Point(0, 0.5f));
        this->addChild(sprite, 0);
    }
    
	//add full stars according to the information
    auto star = UserDefault::getInstance()->getIntegerForKey(fileName.c_str());
    for(int i = 1; i <= star; i++) {
        auto sprite = Sprite::createWithSpriteFrameName("star1.png");
        sprite->setPosition(Point(startPosX + (i - 1) * starWidth, size.height/ 2));
        sprite->setAnchorPoint(Point(0, 0.5f));
        this->addChild(sprite, 0);
    }
    
    addBackGround();
    return true;
}

void LevelInfoScene::addBackGround()
{
    Size size = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("mainscene1.jpg");
    sprite->setPosition(Vec2(size.width/2 , size.height/2 ));
    this->addChild(sprite, -1);
    
    auto spritePanel = Sprite::create("levelInfo.png");
    spritePanel->setPosition(Point(size.width/2 , size.height/2 ));
    this->addChild(spritePanel, -1);
    
    Sprite *start = Sprite::createWithSpriteFrameName("start.jpg");
    MenuItemSprite *startItem = MenuItemSprite::create(start, start, CC_CALLBACK_1(LevelInfoScene::menuStartCallback, this));
    Sprite *back= Sprite::createWithSpriteFrameName("back.jpg");
    MenuItemSprite *backItem = MenuItemSprite::create(back, back, CC_CALLBACK_1(LevelInfoScene::menuBackCallback, this));
    
    auto menu = Menu::create(startItem, backItem, NULL);
    menu->alignItemsHorizontally();
    
    menu->setPosition(Vec2(size.width / 2,size.height / 5));
    
    this->addChild(menu);
}

void LevelInfoScene::menuBackCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, LevelScene::create()));
}

void LevelInfoScene::menuStartCallback(Ref* pSender)
{
    info = LoadLevelinfo::createLoadLevelinfo(fileName.c_str());
    info->readLevelInfo();
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, GamePlayLayer::createScene()));
}