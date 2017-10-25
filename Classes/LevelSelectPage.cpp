#include "LevelSelectPage.h"
#include "LevelInfoScene.hpp"
#include"GameStartScene.h"
#include "SimpleAudioEngine.h" 
#include "GamePlayLayer.hpp"
USING_NS_CC;

#define LEVEL_ROW (3)

LevelSelectPage* LevelSelectPage::create(const std::string& bgName, int level){
	LevelSelectPage *pRet = new LevelSelectPage();
	if (pRet && pRet->initLevelPage(bgName, level)){
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void LevelSelectPage::menuStartCallback(Ref* pSender) {
	auto button = (Sprite *)pSender;

	char buffer[20] = { 0 };
	sprintf(buffer, "levelInfo_%d.plist", button->getTag());
	std::string strName = buffer;
	UserDefault::getInstance()->setStringForKey("nextLevelFile", strName);

	Scene *scene = Scene::create();
	auto layer = LevelInfoScene::create();
	scene->addChild(layer);
	auto sence = TransitionFade::create(0.5, scene);

	Director::getInstance()->replaceScene(sence);
}

bool LevelSelectPage::initLevelPage(const std::string& bgName, int level){
	if (!Node::init()){
		return false;
	}

	auto size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create(bgName);
	sprite->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(sprite, -2);

	Vector<MenuItem*> menuItemVector;
	auto buttonSize = Sprite::create("locked.png")->getContentSize();
	auto gap = buttonSize.width / 4;
	auto startWidth = (size.width - LEVEL_ROW* buttonSize.width - (LEVEL_ROW - 1)*gap) / 2;
	
	auto height = 220;
	for (int col = 0; col < LEVEL_ROW; col++){
		auto width = startWidth + (buttonSize.width + gap) * col;
		auto item = MenuItemImage::create(
				"unlocked.png",
				"unlockedselected.png",
				"locked.png",
				CC_CALLBACK_1(LevelSelectPage::menuStartCallback, this));
		item->setAnchorPoint(Vec2::ZERO);
		item->setPosition(Vec2(width, height));
		item->setTag( col + level * LEVEL_ROW );
		menuItemVector.pushBack(item);
		auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum");

		if (levelNum < col + level * LEVEL_ROW ){
			item->setEnabled(false);
		}
	}

	auto levelMenu = Menu::createWithArray(menuItemVector);
	levelMenu->setPosition(Point::ZERO);
	this->addChild(levelMenu, -1);

	return true;
}

