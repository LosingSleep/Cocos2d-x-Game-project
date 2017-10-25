//
//  TowerOperateLayer.cpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/16.
//
//

#include "TowerOperateLayer.hpp"

USING_NS_CC;

TowerOperateLayer::TowerOperateLayer():
sprite1(NULL)
,sprite2(NULL)
,choseOperateType(CANCEL)
{};

TowerOperateLayer::~TowerOperateLayer(){};

bool TowerOperateLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    sprite1 = Sprite::createWithSpriteFrameName("deleteTower.png");
    sprite1->setAnchorPoint(Vec2(0.5f, 0));
    sprite1->setPosition(Vec2(-32, 32));
    this->addChild(sprite1);
    
    sprite2 = Sprite::createWithSpriteFrameName("upgradeTower.png");
    sprite2->setAnchorPoint(Vec2(0.5f, 0));
    sprite2->setPosition(Vec2(32, 32));
    this->addChild(sprite2);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TowerOperateLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TowerOperateLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
    
    return true;
}

bool TowerOperateLayer::onTouchBegan(Touch *touch, Event *event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 touchLocationInNode = target->convertTouchToNodeSpace(touch);
    
    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    
    if (rect.containsPoint(touchLocationInNode)) {
        target->setOpacity(180);
        return true;
    }
    else {
        return false;
    }
}

void TowerOperateLayer::onTouchEnded(Touch *touch, Event *event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    if (target == sprite1) {
        choseOperateType = DELETE;
    }
    else if (target == sprite2) {
        choseOperateType = UPGRADE;
    }
    else {
        choseOperateType = CANCEL;
    }
    
    return ;
}


