//
//  Enemy.cpp
//  MyGame
//
//  Created by 陈晖 on 16/5/25.
//
//

#include "Enemy.hpp"

USING_NS_CC;

Enemy::Enemy():
hpPercentage(100)
,sprite(NULL)
,hpBackgroundSprite(NULL)
,pointCounter(0)
,animationRight(NULL)
,animationLeft(NULL)
,pointsVector(NULL)
,runSpeed(0)
,maxHp(0)
,currentHp(0)
,hpBar(NULL)
,enemySuccessful(false)
{}

Enemy::~Enemy(){};


bool Enemy::init(enemyType t){
    if (!Sprite::init()) {
        return false;
    }
    
    setType(t);
    setRunSpeed(RUNSPEED[t]);
    setVaule(VALUE[t]);
    
    std::string string = RIGHT_FRAME_NAME[t] + "_1.png";
    sprite = Sprite::createWithSpriteFrameName(string);
    sprite->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(sprite);
    
    animationRight = createAnimation(RIGHT_FRAME_NAME[t], FRAME_NAM[t], ANIMATION_DELAY[t]);
    AnimationCache::getInstance()->addAnimation(animationRight, RIGHT_ANIMATION_NAME[t]);
    animationLeft = createAnimation(LEFT_FRAME_NAME[t], FRAME_NAM[t], ANIMATION_DELAY[t]);
    AnimationCache::getInstance()->addAnimation(animationLeft, LEFT_ANIMATION_NAME[t]);
    
    createAndSetHpBar();
    schedule(schedule_selector(Enemy::changeDirection), 0.2f);
    return true;
    
};

Enemy* Enemy::create(cocos2d::Vector<Node *> points, int hp, enemyType t){
    Enemy *pRet = new Enemy();
    if (pRet && pRet->init(t)) {
        pRet->setPointsVector(points);
        pRet->runFollowPoint();
        pRet->setMaxHp(hp);
        pRet->setCurrentHp(hp);
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Animation* Enemy::createAnimation(std::string prefixName, int framesNum, float delay){
    Vector<SpriteFrame*> animationFrames;
    
    //pushBack each frame into the vector. All the frame has been load in SpriteFrameCache when the plist file read.
    for (int i = 1; i <= framesNum; ++i) {
        char buffer[20] = { 0 };
        sprintf(buffer, "_%i.png", i);
        std::string str = prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animationFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animationFrames, delay);
    return animation;
}

void Enemy::createAndSetHpBar(){
    hpBackgroundSprite = Sprite::createWithSpriteFrameName("hpBarBackground.png");
    hpBackgroundSprite->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height + 10));
    sprite->addChild(hpBackgroundSprite);
    
    hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("hpBar.png"));
    hpBar->setType(ProgressTimer::Type::BAR);
    //set the change start direction
    hpBar->setMidpoint(Vec2(0, 0.5f));
    hpBar->setBarChangeRate(Vec2(1, 0));
    hpBar->setPercentage(hpPercentage);
    hpBar->setPosition(Vec2(hpBackgroundSprite->getContentSize().width / 2, hpBackgroundSprite->getContentSize().height / 2));
    hpBackgroundSprite->addChild(hpBar);
    
    return ;
}

Node* Enemy::getCurrentPoint(){
    if (!pointsVector.empty()) {
        return this->pointsVector.at(pointCounter);
    }
    else {
        return NULL;
    }
}

Node* Enemy::getNextPoint(){
    int maxCount = this->pointsVector.size();
    pointCounter++;
    
    if (pointCounter < maxCount) {
        auto node = this->pointsVector.at(pointCounter);
        return node;
    }
    else {
        setEnemySuccessful(true);
    }
    
    return NULL;
}


void Enemy::runFollowPoint(){
    auto point = getCurrentPoint();
    this->setPosition(point->getPosition());
    point = getNextPoint();
    
    //using a sequence to call back itself, so the enemy will change direction when arrived next point.
    if (point != NULL) {
        runAction(Sequence::create(MoveTo::create(getRunSpeed(), point->getPosition()),CallFuncN::create(CC_CALLBACK_0(Enemy::runFollowPoint, this)), NULL));
    }
    
    return ;
}


void Enemy::setPointsVector(cocos2d::Vector<Node *> points) {
    this->pointsVector = points;
    
    return ;
}

void Enemy::changeDirection(float dt){
    auto currPoint = getCurrentPoint();
    if (currPoint == NULL) {
        return ;
    }
    if (currPoint->getPosition().x >= this->getPosition().x) {
        sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(RIGHT_ANIMATION_NAME[getType()])));
    }
    else {
        sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(LEFT_ANIMATION_NAME[getType()])));
    }
}


void Enemy::enemyDead(){
    hpBackgroundSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(schedule_selector(Enemy::changeDirection));
    sprite->removeFromParent();
}















