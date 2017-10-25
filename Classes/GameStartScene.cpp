#include"SimpleAudioEngine.h"
#include "GameStartScene.h"
#include"LevelScene.h"
#include"GuideScene.h"
#include"AppDelegate.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include<vector>
#include "GameManager.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

GameStart::GameStart(){}
GameStart::~GameStart(){};

Scene* GameStart::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameStart::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void GameStart::menuCloseCallback(Ref* psender) {
	exit(0);
}

void GameStart::menuChangeCallback(Ref* psender) {
	Director::getInstance()->pushScene(TransitionCrossFade::create(1.0f,LevelScene::create()));
}

void GameStart::menuGuideCallback(Ref* psender){
	Director::getInstance()->pushScene(TransitionCrossFade::create(1.0f,GuideScene::createScene()));
}

void GameStart::menuMusicStop(Ref* psender) {
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	auto musicsItem = MenuItemImage::create(
		"musicselected.png",
		"music.png",
		CC_CALLBACK_1(GameStart::menuMusicStart,this));
	musicsItem->setPosition(Vec2(920, 600));
	auto menuMs = Menu::create(musicsItem, NULL);
	menuMs->setPosition(Vec2::ZERO);
	this->addChild(menuMs, 1);
    
    auto instance = GameManager::getInstance();
	instance->setIsBackgroundMusicPlay(false);
}

void GameStart::menuMusicStart(Ref* psender) {
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Still Doll.mp3", true);
	auto musicItem = MenuItemImage::create(
		"music.png",
		"musicselected.png",
		CC_CALLBACK_1(GameStart::menuMusicStop, this));
	musicItem->setPosition(Vec2(920, 600));
	auto menuM = Menu::create(musicItem, NULL);
	menuM->setPosition(Vec2::ZERO);
	this->addChild(menuM, 1);
    
    auto instance = GameManager::getInstance();
    instance->setIsBackgroundMusicPlay(true);
}


bool GameStart::init(){
  
    if ( !Layer::init() ){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto instance = GameManager::getInstance();
    
    if (!instance->getIsFirstTimeInit()) {
        instance->setIsBackgroundMusicPlay(true);
    }
    
    auto closeItem = MenuItemImage::create(
                                           "exit.jpg",
                                           "exitselected.jpg",
                                           CC_CALLBACK_1(GameStart::menuCloseCallback, this));  
	closeItem->setPosition(Vec2(740,250));
    auto menuC = Menu::create(closeItem, NULL);
    menuC->setPosition(Vec2::ZERO);
    this->addChild(menuC, 1);

	auto startItem = MenuItemImage::create(
											"start.jpg",
											"startselected.jpg",
											CC_CALLBACK_1(GameStart::menuChangeCallback, this));
	startItem->setPosition(Vec2(480, 250));
	auto menuS = Menu::create(startItem, NULL);
	menuS->setPosition(Vec2::ZERO);
	this->addChild(menuS, 1);

	auto guideItem = MenuItemImage::create(
											"guide.jpg",
											"guideselected.jpg",
											CC_CALLBACK_1(GameStart::menuGuideCallback, this));
	guideItem->setPosition(Vec2(220, 250));
	auto menuG = Menu::create(guideItem, NULL);
	menuG->setPosition(Vec2::ZERO);
	this->addChild(menuG, 1);
   

    auto sprite = Sprite::create("mainscene.jpg");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
   
	ParticleSystem * p1 = ParticleRain::create();
	p1->setTexture(TextureCache::sharedTextureCache()->addImage("blood.png"));
	p1->setAutoRemoveOnFinish(true);
	p1->setPositionType(ParticleSystem::PositionType::GROUPED);
	p1->setPosition(Vec2(480, 640));
	this->addChild(p1);

	if (instance->getIsBackgroundMusicPlay()) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Still Doll.mp3", true);
		auto musicItem = MenuItemImage::create(
			"music.png",
			"musicselected.png",
			CC_CALLBACK_1(GameStart::menuMusicStop, this));
		musicItem->setPosition(Vec2(920, 600));
		auto menuM = Menu::create(musicItem, NULL);
		menuM->setPosition(Vec2::ZERO);
		this->addChild(menuM, 1);
	}
	else {
		auto musicsItem = MenuItemImage::create(
			"musicselected.png",
			"music.png",
			CC_CALLBACK_1(GameStart::menuMusicStart, this));
		musicsItem->setPosition(Vec2(920, 600));
		auto menuMs = Menu::create(musicsItem, NULL);
		menuMs->setPosition(Vec2::ZERO);
		this->addChild(menuMs, 1);
	}
    
    instance->setIsFirstTimeInit(true);


    return true;
}
