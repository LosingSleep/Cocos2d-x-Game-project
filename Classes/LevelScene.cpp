#include "LevelScene.h"
#include "ScrollView.h"
#include "LevelSelectPage.h"
#include "GameStartScene.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define LAYER_NUMBER (3)

LevelScene* LevelScene::instance;

LevelScene *LevelScene::getInstance(){
	if (instance != NULL) {
		return instance;
	}
	return  NULL;
}

void LevelScene::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameStart::createScene()));
}

bool LevelScene::init(){
	if (!Scene::init()){
		return false;
	}
	instance = this;

	Size size = Director::getInstance()->getWinSize();

	//to create scrollview layer on the scene
	ScrollView* scrollView = ScrollView::create();

	Sprite* spritebg = Sprite::create("mainscene1.jpg");
	spritebg->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(spritebg);

	//to display total number of nodes
	auto width = Sprite::create("readyPage.png")->getContentSize().width;
	auto posX = size.width / 2 - width;
	for (int i = 0; i < LAYER_NUMBER; i++){
		Sprite* sprite = Sprite::create("readyPage.png");
		sprite->setPosition(Vec2(posX + i *width, size.height / 7));
		addChild(sprite);
	}

	//scroll to different nodes 
	for (int i = 0; i<LAYER_NUMBER; ++i) {
		if (0 == i) {
			auto page = LevelSelectPage::create("easyLevelPage.png", i);
			page->setTag(i);
			scrollView->addNode(page);

			//mark the current node by setting Tag(666)
			Sprite* spriteMark = Sprite::create("currentPage.png");
			spriteMark->setPosition(Vec2(posX + i *width, size.height / 7));
			spriteMark->setTag(666);
			addChild(spriteMark);
		}
		else if (1 == i) {
			auto page = LevelSelectPage::create("normalLevelPage.png", i);
			page->setTag(i);
			scrollView->addNode(page);
		}
		else if (2 == i) {
			auto page = LevelSelectPage::create("hardLevelPage.png", i);
			page->setTag(i);
			scrollView->addNode(page);
		}
	}

	
	auto closeItem = MenuItemImage::create(
		"back.png",
		"backselected.png",
		CC_CALLBACK_1(LevelScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(920, 600));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	// to add ScrollView layer into LevelScene
	this->addChild(scrollView);

	return true;
}

