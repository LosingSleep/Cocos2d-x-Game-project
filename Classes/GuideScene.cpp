#include "GameStartScene.h"
#include"GuideScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GuideScene::createScene(){
	auto scene = Scene::create();
	auto layer = GuideScene::create();
	scene->addChild(layer);
	return scene;
}

void GuideScene::popScene(Ref* psender) {
	Director::getInstance()->popScene();
}

bool GuideScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto closeItem = MenuItemImage::create(
		"back.png",
		"backselected.png",
		CC_CALLBACK_1(GuideScene::popScene, this));

	closeItem->setPosition(Vec2(920, 600));
	auto menuC = Menu::create(closeItem, NULL);
	menuC->setPosition(Vec2::ZERO);
	this->addChild(menuC, 1);


	auto sprite = Sprite::create("story.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);


	//particle special effects
	ParticleSystem * p1 = ParticleSnow::create();
	p1->setTexture(TextureCache::sharedTextureCache()->addImage("snow.png"));
	p1->setAutoRemoveOnFinish(true);
	p1->setPositionType(ParticleSystem::PositionType::GROUPED);
	p1->setPosition(Vec2(480, 640));
	this->addChild(p1);

	return true;
}