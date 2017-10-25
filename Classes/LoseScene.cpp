#include"GameStartScene.h"
#include"LoseScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"SimpleAudioEngine.h" 
#include "GameManager.hpp"
#include "LevelScene.h"
#include "LevelInfoScene.hpp"
#include "GamePlayLayer.hpp"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* LoseScene::createScene(){
	auto scene = Scene::create();
	auto layer = LoseScene::create();
	scene->addChild(layer);
	return scene;
}

void LoseScene::menuBackCallback(Ref* psender) {
    auto instance = GameManager::getInstance();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("lose.mp3");
    if (instance->getIsBackgroundMusicPlay()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Still Doll.mp3", true);
    }
        Director::getInstance()->replaceScene(TransitionShrinkGrow::create(3.0f, LevelScene::create()));
}


void LoseScene::menuTryAgainCallback(Ref* psender) {
    auto instance = GameManager::getInstance();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("lose.mp3");
    if (instance->getIsBackgroundMusicPlay()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Still Doll.mp3", true);
    }

    Director::getInstance()->replaceScene(TransitionShrinkGrow::create(3.0f, LevelInfoScene::createScene()));
}

void LoseScene::menuMusicStop(Ref* psender) {
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	auto musicsItem = MenuItemImage::create(
		"musicselected.png",
		"music.png",
		CC_CALLBACK_1(LoseScene::menuMusicStart, this));
	musicsItem->setPosition(Vec2(920, 600));
	auto menuMs = Menu::create(musicsItem, NULL);
	menuMs->setPosition(Vec2::ZERO);
	this->addChild(menuMs, 1);

	auto instance = GameManager::getInstance();
	instance->setIsBackgroundMusicPlay(false);
}

void LoseScene::menuMusicStart(Ref* psender) {
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("lose.mp3", true);
	auto musicItem = MenuItemImage::create(
		"music.png",
		"musicselected.png",
		CC_CALLBACK_1(LoseScene::menuMusicStop, this));
	musicItem->setPosition(Vec2(920, 600));
	auto menuM = Menu::create(musicItem, NULL);
	menuM->setPosition(Vec2::ZERO);
	this->addChild(menuM, 1);

	auto instance = GameManager::getInstance();
	instance->setIsBackgroundMusicPlay(true);
}

bool LoseScene::init(){
	if (!Scene::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto instance = GameManager::getInstance();
	
    auto tryItem = MenuItemImage::create(
                                         "try.jpg",
                                         "tryselected.jpg",
                                         CC_CALLBACK_1(LoseScene::menuTryAgainCallback, this));
    
    tryItem->setPosition(Vec2(480, 250));
    auto menuT = Menu::create(tryItem, NULL);
    menuT->setPosition(Vec2::ZERO);
    this->addChild(menuT, 1);
    
    
    auto backItem = MenuItemImage::create(
                                          "back.jpg",
                                          "backselected.jpg",
                                          CC_CALLBACK_1(LoseScene::menuBackCallback, this));
    
    backItem->setPosition(Vec2(480, 150));
    auto menuE = Menu::create(backItem, NULL);
    menuE->setPosition(Vec2::ZERO);
    this->addChild(menuE, 1);

	auto sprite = Sprite::create("losescene.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	if (instance->getIsBackgroundMusicPlay()) {
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("Still Doll.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("lose.mp3", true);
		auto musicItem = MenuItemImage::create(
			"music.png",
			"musicselected.png",
			CC_CALLBACK_1(LoseScene::menuMusicStop, this));
		musicItem->setPosition(Vec2(920, 600));
		auto menuM = Menu::create(musicItem, NULL);
		menuM->setPosition(Vec2::ZERO);
		this->addChild(menuM, 1);
	}
	else {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("Still Doll.mp3");
		auto musicsItem = MenuItemImage::create(
			"musicselected.png",
			"music.png",
			CC_CALLBACK_1(LoseScene::menuMusicStart, this));
		musicsItem->setPosition(Vec2(920, 600));
		auto menuMs = Menu::create(musicsItem, NULL);
		menuMs->setPosition(Vec2::ZERO);
		this->addChild(menuMs, 1);
	}

	//particle special effect
	ParticleSystem * p1=ParticleExplosion::create();
	p1->setTexture(TextureCache::sharedTextureCache()->addImage("bloods.png"));
	p1->setAutoRemoveOnFinish(true);
	p1->setPositionType(ParticleSystem::PositionType::GROUPED);
	p1->setPosition(Vec2(480,320));
	this->addChild(p1);

	return true;
}