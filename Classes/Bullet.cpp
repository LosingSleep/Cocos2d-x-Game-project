//
//  Bullet.cpp
//  MyGame
//
//  Created by 陈晖 on 16/6/1.
//
//

#include "Bullet.hpp"
#include "GameManager.hpp"
USING_NS_CC;

Bullet::Bullet():sprite(nullptr){};
Bullet::~Bullet(){};

bool Bullet::init(Type t){
    if (!Sprite::init()) {
        return false;
    }
    
    sprite = Sprite::createWithSpriteFrameName(PICTURE[t]);
    this->addChild(sprite);
    setSpeed(SPEED[t]);
    setLethality(LETHALITY[t]);
    return true;
}

Bullet* Bullet::create(Type t){
    Bullet* pRet = new Bullet();
    
    if (pRet && pRet->init(t)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void Bullet::removeBullet(Node* pSender){
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;

	//Make the parent class pointer point to a child class,
	//to store the bullet in the bullet vector;
    Bullet *bullet = (Bullet *)pSender;
    instance->bulletVector.eraseObject(bullet);
    bullet->removeFromParent();
}

void Bullet::shoot(){
    this->runAction(Sequence::create(bulletAction, CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this)),NULL));
}

