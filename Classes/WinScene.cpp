#include"GameStartScene.h"
#include"WinScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include "GameManager.hpp"
#include "LevelScene.h"
#include "LevelInfoScene.hpp"
USING_NS_CC;
using namespace cocostudio::timeline;


Scene* WinScene::createScene(){
	auto scene = Scene::create();
	auto layer = WinScene::create();
	scene->addChild(layer);
	return scene;
}

void WinScene::menuContinueCallback(Ref* psender) {
    auto instance = GameManager::getInstance();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("win.mp3");
    if (instance->getIsBackgroundMusicPlay()) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Still Doll.mp3", true);
    }
    
    Director::getInstance()->replaceScene(TransitionShrinkGrow::create(3.0f, LevelInfoScene::createScene()));
}

void WinScene::menuBackCallback(Ref* psender) {
    auto instance = GameManager::getInstance();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("lose.mp3");
    if (instance->getIsBackgroundMusicPlay()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Still Doll.mp3", true);
    }
    Director::getInstance()->replaceScene(TransitionShrinkGrow::create(3.0f, LevelScene::create()));
}

void WinScene::menuMusicStop(Ref* psender) {
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	auto musicsItem = MenuItemImage::create(
		"musicselected.png",
		"music.png",
		CC_CALLBACK_1(WinScene::menuMusicStart, this));
	musicsItem->setPosition(Vec2(920, 600));
	auto menuMs = Menu::create(musicsItem, NULL);
	menuMs->setPosition(Vec2::ZERO);
	this->addChild(menuMs, 1);

	auto instance = GameManager::getInstance();
	instance->setIsBackgroundMusicPlay(false);
}

void WinScene::menuMusicStart(Ref* psender) {
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("win.mp3", true);
	auto musicItem = MenuItemImage::create(
		"music.png",
		"musicselected.png",
		CC_CALLBACK_1(WinScene::menuMusicStop, this));
	musicItem->setPosition(Vec2(920, 600));
	auto menuM = Menu::create(musicItem, NULL);
	menuM->setPosition(Vec2::ZERO);
	this->addChild(menuM, 1);

	auto instance = GameManager::getInstance();
	instance->setIsBackgroundMusicPlay(true);
}

bool WinScene::init(){
	if (!Scene::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto instance = GameManager::getInstance();

    auto nextItem = MenuItemImage::create(
                                          "next.jpg",
                                          "nextselected.jpg",
                                          CC_CALLBACK_1(WinScene::menuContinueCallback, this));
    
    nextItem->setPosition(Vec2(480, 250));
    auto menuT = Menu::create(nextItem, NULL);
    menuT->setPosition(Vec2::ZERO);
    this->addChild(menuT, 1);
    
    
    auto backItem = MenuItemImage::create(
                                          "back.jpg",
                                          "backselected.jpg",
                                          CC_CALLBACK_1(WinScene::menuBackCallback, this));
    
    backItem->setPosition(Vec2(visibleSize.width / 2, 150));
    auto menuE = Menu::create(backItem, NULL);
    menuE->setPosition(Vec2::ZERO);
    this->addChild(menuE, 1);


	auto sprite = Sprite::create("winscene.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	if (instance->getIsBackgroundMusicPlay()) {
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("Still Doll.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("win.mp3", true);
		auto musicItem = MenuItemImage::create(
			"music.png",
			"musicselected.png",
			CC_CALLBACK_1(WinScene::menuMusicStop, this));
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
			CC_CALLBACK_1(WinScene::menuMusicStart, this));
		musicsItem->setPosition(Vec2(920, 600));
		auto menuMs = Menu::create(musicsItem, NULL);
		menuMs->setPosition(Vec2::ZERO);
		this->addChild(menuMs, 1);
	}

	//particle special effects
	ParticleSystem * p1 = ParticleFireworks::create();
	p1->setTexture(TextureCache::sharedTextureCache()->addImage("star.png"));
	p1->setAutoRemoveOnFinish(true);
	p1->setPositionType(ParticleSystem::PositionType::GROUPED);
	p1->setPosition(Vec2(480, 290));
	this->addChild(p1);

	return true;
}