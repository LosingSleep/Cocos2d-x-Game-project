//
//  TowerPanleLayer.cpp
//  MyGame
//
//  Created by 陈晖 on 16/5/31.
//
//

#include "TowerPanleLayer.hpp"

USING_NS_CC;



TowerPanleLayer::TowerPanleLayer():
sprite1(NULL)
,sprite2(NULL)
,sprite3(NULL)
,choseTowerType(TowerType::ANOTHER)
{};
TowerPanleLayer::~TowerPanleLayer(){};

bool TowerPanleLayer::init(){
    if (!Layer::init()){
        return false;
    }
    auto sprite = Sprite::createWithSpriteFrameName("selectPoint.png");
    sprite->setPosition(Vec2(0, 0));
    this->addChild(sprite);
    
    sprite1 = Sprite::createWithSpriteFrameName("buyAT.png");
    sprite1->setAnchorPoint(Vec2(0.5f, 0));
    sprite1->setPosition(Vec2(-sprite->getContentSize().width, sprite->getContentSize().height / 2));
    this->addChild(sprite1);
    
    sprite2 = Sprite::createWithSpriteFrameName("buyCT.png");
    sprite2->setAnchorPoint(Vec2(0.5f, 0));
    sprite2->setPosition(Vec2(0, sprite->getContentSize().height / 2));
    this->addChild(sprite2);
    
    sprite3 = Sprite::createWithSpriteFrameName("buyMDT.png");
    sprite3->setAnchorPoint(Vec2(0.5f, 0));
    sprite3->setPosition(Vec2(sprite->getContentSize().width, sprite->getContentSize().height / 2));
    this->addChild(sprite3);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanleLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanleLayer::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite3);

    return true;
}



bool TowerPanleLayer::onTouchBegan(Touch *touch, Event *event){
    //upcast
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 touchLocationInNode = target->convertTouchToNodeSpace(touch);
    
    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    
    if (rect.containsPoint(touchLocationInNode)) {
        //set the Opacity to show it was chose
        target->setOpacity(180);
        return true;
    }
    else {
        return false;
    }
    
}


void TowerPanleLayer::onTouchEnded(Touch* touch, Event* event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    if (target == sprite1){
        choseTowerType = ARROW_TOWER;
    }
    else if(target == sprite2){
        choseTowerType = ATTACK_TOWER;
    }
    else if(target == sprite3){
        choseTowerType = MULTIDIR_TOWER;
    }
    else {
        choseTowerType = ANOTHER;
    }
    
    return ;
}

