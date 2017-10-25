//
//  GamePlayLayer.cpp
//  MyGame
//
//  Created by 陈晖 on 16/5/24.
//
//
#include"SimpleAudioEngine.h"
#include "GamePlayLayer.hpp"
#include "LoadLevelInfo.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Bullet.hpp"
#include "MultiDirTower.hpp"
#include "AttackTower.hpp"
#include "ColdTower.hpp"
#include "LoseScene.h"
#include "WinScene.h"
#include "LevelScene.h"

const int Tower1_Money = 300;
const int Tower2_Money = 400;
const int Tower3_Money = 500;

USING_NS_CC;

GamePlayLayer::GamePlayLayer()
:map(NULL)
,objects(NULL)
,pointVector(NULL)
,choseTowerpanle(NULL)
,choseTowerOperatepanle(NULL)
,towerMatrix(NULL)
,groupCounter(0)
,money(0)
,playHpBar(NULL)
,playHpPercentage(100)
,moneyLabel(NULL)
,successful(false)
,choseTowerInMatrix(NULL)
{}

GamePlayLayer::~GamePlayLayer(){
    if (towerMatrix) {
        free(towerMatrix);
    }
    pointVector.clear();
};


bool GamePlayLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    instance = GameManager::getInstance();

    //add the game background.
    auto gameBackground = Sprite::create(instance->getCurrBackgroundName());
    gameBackground->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(gameBackground, -20);

    //loading the map in current level, and add it into the game.
    map = TMXTiledMap::create(instance->getCurrMapName());
    mapWidth = (int)map->getMapSize().width;
    mapHeight = (int)map->getMapSize().height;
    roadLayer = map->getLayer("Foreground");
    objects = map->getObjectGroup("Object");
    this->addChild(map, -10);
   
    initToolLayer();
    this->initPointVector();

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    schedule(schedule_selector(GamePlayLayer::gameLogic), 0.8f);
    
	//init the towerMatrix using to record the which panles have placed a tower
    int arraySize = sizeof(Tower *) * mapWidth * mapHeight;
    towerMatrix = (Tower **)malloc(arraySize);
    memset((void*)towerMatrix, 0, arraySize);
    
    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            towerMatrix[row * mapWidth + col] = NULL;
        }
    }

    return true;
}

Scene* GamePlayLayer::createScene(){
    auto Scene = Scene::create();
    auto Layer = GamePlayLayer::create();
    Scene->addChild(Layer);
    return Scene;
}


void GamePlayLayer::initPointVector(){
    Node* runOfPoint = NULL;
    int counter = 0;
    ValueMap point;
    
    point = objects->getObject(std::to_string(counter));
    //when point is empty, break the while
    while (point.begin() != point.end()) {
        float x = point.at("x").asFloat();
        float y = point.at("y").asFloat();
        runOfPoint = Node::create();
        runOfPoint->setPosition(Vec2(x, y));
        this->pointVector.pushBack(runOfPoint);
        
        counter++;
        point = objects->getObject(std::to_string(counter));
    }

    runOfPoint = NULL;
    return ;
}

void GamePlayLayer::initToolLayer(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    toolLayer = Layer::create();
    this->addChild(toolLayer);
    
    auto toolBackground = Sprite::createWithSpriteFrameName("toolLayer.png");
    toolBackground->setAnchorPoint(Vec2(0.5f, 1));
    toolBackground->setPosition(visibleSize.width / 2, visibleSize.height);
    toolLayer->addChild(toolBackground);
    
    money = instance->getMoney();
    auto moneyText = std::to_string(money);
    moneyLabel = Label::createWithBMFont("boundsTestFont.fnt", "");
    moneyLabel->setString(moneyText);
    moneyLabel->setAnchorPoint(Vec2(0, 0.5f));
    moneyLabel->setPosition(toolBackground->getContentSize().width / 6, toolBackground->getContentSize().height / 2);
    toolBackground->addChild(moneyLabel);
    
    auto playHpBarBg = Sprite::createWithSpriteFrameName("playerHpBarBg.png");
    playHpBarBg->setPosition(toolBackground->getContentSize().width - 300, toolBackground->getContentSize().height / 2);
    toolBackground->addChild(playHpBarBg);
    
    playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("playerHpBar.png"));
    playHpBar->setType(ProgressTimer::Type::BAR);
    playHpBar->setMidpoint(Vec2(0, 0.4f));
    playHpBar->setBarChangeRate(Vec2(1, 0));
    playHpBar->setPercentage(playHpPercentage);
    playHpBar->setPosition(toolBackground->getContentSize().width - 300, toolBackground->getContentSize().height / 2);
    toolBackground->addChild(playHpBar);
    
    auto backItem = MenuItemImage::create(
                                           "back.png",
                                           "backselected.png",
                                           CC_CALLBACK_1(GamePlayLayer::menuBackCallback, this));
    backItem->setPosition(Vec2(920, 600));
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    if (instance->getIsBackgroundMusicPlay()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Still Doll.mp3", true);
        auto musicItem = MenuItemImage::create(
                                               "music.png",
                                               "musicselected.png",
                                               CC_CALLBACK_1(GamePlayLayer::menuMusicStop, this));
        musicItem->setPosition(Vec2(850, 600));
        auto menuM = Menu::create(musicItem, NULL);
        menuM->setPosition(Vec2::ZERO);
        this->addChild(menuM, 1);
    }
    else {
        auto musicsItem = MenuItemImage::create(
                                                "musicselected.png",
                                                "music.png",
                                                CC_CALLBACK_1(GamePlayLayer::menuMusicStart, this));
        musicsItem->setPosition(Vec2(850, 600));
        auto menuMs = Menu::create(musicsItem, NULL);
        menuMs->setPosition(Vec2::ZERO);
        this->addChild(menuMs, 1);
    }
    
    return ;
}

void GamePlayLayer::menuBackCallback(cocos2d::Ref *pSender){
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, LevelScene::create()));
    return ;
}

void GamePlayLayer::menuMusicStop(cocos2d::Ref *psender){
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    auto musicsItem = MenuItemImage::create(
                                            "musicselected.png",
                                            "music.png",
                                            CC_CALLBACK_1(GamePlayLayer::menuMusicStart,this));
    musicsItem->setPosition(Vec2(850, 600));
    auto menuMs = Menu::create(musicsItem, NULL);
    menuMs->setPosition(Vec2::ZERO);
    this->addChild(menuMs, 1);
    
    auto instance = GameManager::getInstance();
    instance->setIsBackgroundMusicPlay(false);
    return ;
}

void GamePlayLayer::menuMusicStart(cocos2d::Ref *psender){
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Still Doll.mp3",true);
    }
    auto musicItem = MenuItemImage::create(
                                           "music.png",
                                           "musicselected.png",
                                           CC_CALLBACK_1(GamePlayLayer::menuMusicStop, this));
    musicItem->setPosition(Vec2(850, 600));
    auto menuM = Menu::create(musicItem, NULL);
    menuM->setPosition(Vec2::ZERO);
    this->addChild(menuM, 1);
    
    auto instance = GameManager::getInstance();
    instance->setIsBackgroundMusicPlay(true);
    return ;
}

bool GamePlayLayer::onTouchBegan(Touch *touch, Event *event){
    this->removeChild(choseTowerpanle);
    this->removeChild(choseTowerOperatepanle);
    choseTowerpanle = NULL;
    choseTowerOperatepanle = NULL;
    
    auto location = touch->getLocation();
    checkAndHandleTouch(location);
    return true;
}

void GamePlayLayer::addTowerChoosePanle(cocos2d::Vec2 position){
    choseTowerpanle = TowerPanleLayer::create();
    choseTowerpanle->setPosition(position);
    this->addChild(choseTowerpanle);
    return ;
}

void GamePlayLayer::addTowerOperatePanle(cocos2d::Vec2 position){
    choseTowerOperatepanle = TowerOperateLayer::create();
    choseTowerOperatepanle->setPosition(position);
    this->addChild(choseTowerOperatepanle);
    return ;
}

Vec2 GamePlayLayer::convertToTileCoord(cocos2d::Vec2 position){
    int x = position.x / (map->getContentSize().width / map->getMapSize().width);
    int y = map->getMapSize().height - position.y / (map->getContentSize().height / map->getMapSize().height);
    
    return Vec2(x, y);
};

Vec2 GamePlayLayer::convertToMatrixCoord(cocos2d::Vec2 position){
    int x = position.x / (map->getContentSize().width / map->getMapSize().width);
    int y = position.y / (map->getContentSize().height / map->getMapSize().height);
    
    return Vec2(x, y);
};

void GamePlayLayer::checkAndHandleTouch(cocos2d::Vec2 position){
    Vec2 tileCoord = convertToTileCoord(position);
    Vec2 matrixCoord = convertToMatrixCoord(position);
    
    int GID = roadLayer->getTileGIDAt(tileCoord);
    auto tileTemp = map->getPropertiesForGID(GID).asValueMap();

    int MatrixIndex = static_cast<int>(matrixCoord.y * mapWidth + matrixCoord.x);
    
    int TouchValue = tileTemp.at("canTouch").asInt();
    
    //convert the tile coord into OpenGL coord
    auto tileWidth = map->getTileSize().width;
    auto tileHeight = map->getTileSize().height;
    towerPos = Vec2((tileCoord.x * tileWidth) + (tileWidth / 2), map->getContentSize().height - (tileCoord.y * tileHeight) - (tileHeight / 2));
    
    if (TouchValue == 1 && towerMatrix[MatrixIndex] == NULL){
        addTowerChoosePanle(towerPos);
    }
    else if (towerMatrix[MatrixIndex] != NULL){
        choseTowerInMatrix = MatrixIndex;
        addTowerOperatePanle(towerPos);
    }
    else {
        auto tips = Sprite::createWithSpriteFrameName("error.png");
        tips->setPosition(towerPos);
        this->addChild(tips);
        tips->runAction(Sequence::create(DelayTime::create(0.8f),CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)), NULL));
    }
    
    return ;
}

void GamePlayLayer::addTower(){
    if (choseTowerpanle != NULL) {
        auto towerType = choseTowerpanle->getChoseTowerType();
        bool noMoneyTips = false;
        Tower* tower = NULL;
        
        Vec2 matrixCoord = convertToMatrixCoord(towerPos);
        int MatrixIndex = static_cast<int>( matrixCoord.y * mapWidth + matrixCoord.x );
        
        switch (towerType) {
            case TowerType::ARROW_TOWER: {
                if (money >= Tower1_Money) {
                    tower = AttackTower::create();
                    money -= Tower1_Money;
                }
                else{
                    noMoneyTips = true;
                }
            }
                break;
                
            case TowerType::ATTACK_TOWER: {
                if (money >= Tower2_Money) {
                    tower = ColdTower::create();
                    money -= Tower2_Money;
                }
                else{
                    noMoneyTips = true;
                }
            }
                break;
                
            case TowerType::MULTIDIR_TOWER: {
                if (money >= Tower3_Money) {
                    tower = MultiDirTower::create();
                    
                    money -= Tower3_Money;
                }
                else{
                    noMoneyTips = true;
                }
            }
                break;
                
            case TowerType::ANOTHER: {
                return ;
            }
        }
        
        if(tower != NULL){
            tower->setPosition(towerPos);
            tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
            this->addChild(tower);
            towerMatrix[MatrixIndex] =  tower;
        }
        towerType = TowerType::ANOTHER;
        choseTowerpanle->setChoseTowerType(TowerType::ANOTHER);
        this->removeChild(choseTowerpanle);
        choseTowerpanle = NULL;
        
        auto moneyText = std::to_string(money);
        moneyLabel->setString(moneyText);
        
        if( noMoneyTips == true ){
            auto tips = Sprite::createWithSpriteFrameName("noMoney.png");
            tips->setPosition(towerPos);
            this->addChild(tips);
            tips->runAction(Sequence::create(DelayTime::create(0.5f),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                             NULL));
        }
    }
    return ;
}

void GamePlayLayer::operateTower(){
    if (choseTowerOperatepanle != NULL) {
        auto operateType = choseTowerOperatepanle->getChoseOperateType();
        bool noMoneyTips = false;
        
        switch (operateType) {
            case OperateType::DELETE: {
                //delete tower
                money += towerMatrix[choseTowerInMatrix]->getTowerValue() / 2;
                towerMatrix[choseTowerInMatrix]->removeFromParent();
                instance->towerVector.eraseObject(towerMatrix[choseTowerInMatrix]);
                towerMatrix[choseTowerInMatrix]->release();
                towerMatrix[choseTowerInMatrix] = NULL;
                choseTowerInMatrix = NULL;
            }
                break;
                
            case OperateType::UPGRADE: {
                //upgrade tower
                if (money >= 500) {
                    towerMatrix[choseTowerInMatrix]->upgrade();
                    money -= 500;
                }
                else {
                     noMoneyTips = true;
                }
            }
                break;
                
            case OperateType::CANCEL:{
                return ;
            }
        }
        
        operateType = OperateType::CANCEL;
        choseTowerOperatepanle->setChoseOperateType(OperateType::CANCEL);
        this->removeChild(choseTowerOperatepanle);
        choseTowerOperatepanle = NULL;
        
        auto moneyText = std::to_string(money);
        moneyLabel->setString(moneyText);
        
        if( noMoneyTips == true ){
            auto tips = Sprite::createWithSpriteFrameName("noMoney.png");
            tips->setPosition(towerPos);
            this->addChild(tips);
            tips->runAction(Sequence::create(DelayTime::create(0.3f),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                             NULL));
        }
    }
    
    return ;
}

void GamePlayLayer::collisionDetection(){
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;
    
    if (bulletVector.empty() || enemyVector.empty()) {
        return ;
    }
    
    //store the enemy or bullets need to delete
    Vector<Enemy*> enemyToDelete;
    Vector<Bullet*> bulletToDelete;
    
    for (int i = 0; i < bulletVector.size(); ++i) {
        auto bullet = bulletVector.at(i);
        Vec2 towerPosition = bullet->towerPos;
        //get the bullet rect base on OpenGL coord
        auto bulletRect = Rect(bullet->getPositionX() + towerPosition.x - bullet->sprite->getContentSize().width / 2,
                               bullet->getPositionY() + towerPosition.y - bullet->sprite->getContentSize().height / 2,
                               bullet->sprite->getContentSize().width,
                               bullet->sprite->getContentSize().height);
        
        for (int j = 0; j < enemyVector.size(); ++j) {
            auto enemy = enemyVector.at(j);
            //get the enemy rect base in OpenGL coord
            auto enemyRect = Rect(enemy->getPositionX() + enemy->sprite->getContentSize().width / 4,
                                  enemy->getPositionY() + enemy->sprite->getContentSize().height / 4,
                                  enemy->sprite->getContentSize().width / 2,
                                  enemy->sprite->getContentSize().height / 2);
            //when an enemy and a bullet intersect
            if (bulletRect.intersectsRect(enemyRect)) {
                auto currHp = enemy->getCurrentHp();
                currHp -= bullet->getLethality();
                enemy->setCurrentHp(currHp);
                auto currHpPercentage = enemy->getHpPercentage();
                auto offHpPercentage = (bullet->getLethality() / enemy->getMaxHp()) * 100;
                currHpPercentage -= offHpPercentage;
                if (currHpPercentage < 0) {
                    currHpPercentage = 0;
                }
                enemy->setHpPercentage(currHpPercentage);
                enemy->getHpBar()->setPercentage(currHpPercentage);
                if (currHp <= 0) {
                    enemyToDelete.pushBack(enemy);
                    auto valueMoney = enemy->getVaule();
                    money += valueMoney;
                    auto moneyText = std::to_string(money);
                    moneyLabel->setString(moneyText);
                }
                bulletToDelete.pushBack(bullet);
                
                //if a bullet hit an enemy, break the loop to make sure one bullet only can hit one enemy
                break;
            }
        }
        
        for (Enemy* enemyTemp : enemyToDelete){
            enemyTemp->enemyDead();
            instance->enemyVector.eraseObject(enemyTemp);
            enemyVector.eraseObject(enemyTemp);
        }
        enemyToDelete.clear();
    }
    
    for (Bullet* bulletTemp : bulletToDelete){
        instance->bulletVector.eraseObject(bulletTemp);
        bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
    }
    bulletToDelete.clear();
    
    return ;
}

void GamePlayLayer::enemyIntoHome(){
    auto enemyVector  = instance->enemyVector;
    
    for (int i = 0; i < enemyVector.size(); ++i){
        auto enemy = enemyVector.at(i);
        if (enemy->getEnemySuccessful() == true){
            instance->enemyVector.eraseObject(enemy);
            enemy->removeFromParent();
            auto playHp = getPlayHpPercentage() - 10;
            if (playHp > 0) {
                setPlayHpPercentage(playHp);
                playHpBar->setPercentage(playHp);
            }
            else {
                instance->clearGameManager();
                Director::getInstance()->replaceScene(TransitionFade::create(0.2f, LoseScene::create()));
            }
        }
    }
    
    return;
}

void GamePlayLayer::isSuccessful(){
    if (successful == true) {
        successful = false;
        auto star = 0;
        auto playHp = this->getPlayHpPercentage();
        
        if ( playHp > 0 && playHp <= 30) {
            star = 1;
        }
        else if (playHp > 30 && playHp <= 60) {
            star = 2;
        }
        else if(playHp > 60 && playHp <= 100) {
            star = 3;
        }
        
        //using UserDefault to store the game levels' information.
        if( star > UserDefault::getInstance()->getIntegerForKey(instance->getCurrLevelFile().c_str())){
            UserDefault::getInstance()->setIntegerForKey(instance->getCurrLevelFile().c_str(), star);
            auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum") + 1;
            UserDefault::getInstance()->setIntegerForKey("levelNum", levelNum);
        }
        
        //set the "nextlevel" in UserDefault
        std::string nextlevel = instance->getNextLevelFile();
        UserDefault::getInstance()->setStringForKey("nextLevelFile", nextlevel);
        
        instance->clearGameManager();
        Director::getInstance()->replaceScene(TransitionFade::create(0.2f, WinScene::create()));
    }
    
    return ;
}

void GamePlayLayer::update(float dt){
    addTower();
    operateTower();
    collisionDetection();
    enemyIntoHome();
    isSuccessful();
    
    return;
};


GroupEnemy* GamePlayLayer::getCurrentGroup(){
    GroupEnemy* groupEnemy;
    
    if (!instance->groupEnemyVector.empty()) {
        groupEnemy = (GroupEnemy*)instance->groupEnemyVector.at(groupCounter);
    }
    else {
        groupEnemy = NULL;
    }
    
    return groupEnemy;
}

GroupEnemy* GamePlayLayer::getNextGroup(){
    if(instance->groupEnemyVector.empty()) {
        return NULL;
    }
    
    if (groupCounter < (instance->getGroupNum() - 1)) {
        groupCounter++;
    }
    else {
        successful = true;
    }
    GroupEnemy* groupEnemy = (GroupEnemy*)instance->groupEnemyVector.at(groupCounter);
    
    return groupEnemy;
}


void GamePlayLayer::gameLogic(float dt){
    GroupEnemy* groupEnemy = this->getCurrentGroup();
    if (groupEnemy == NULL) {
        return ;
    }
    bool isAddEnemyFinished = groupEnemy->getIsGroupAddFinished();
    if (isAddEnemyFinished == true && instance->enemyVector.size() == 0 && groupCounter < instance->getGroupNum()) {
        groupEnemy = this->getNextGroup();
    }
    this->addEnemy();
    
    return ;
}

void GamePlayLayer::addEnemy(){
    GroupEnemy* groupEnemy = this->getCurrentGroup();
    if (groupEnemy == NULL) {
        return ;
    }
    
    auto restEnemyNum = groupEnemy->getEnemyTotal();
    if (restEnemyNum <= 0) {
        groupEnemy->setIsGroupAddFinished(true);
        return ;
    }
    
    Enemy* enemy = NULL;
    if(groupEnemy->getType1Total() > 0){
        enemy = Enemy::create(pointVector, groupEnemy->getType1Hp(), enemyType::WAKING);
        groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
    }
    else if(groupEnemy->getType2Total() > 0){
        enemy = Enemy::create(pointVector, groupEnemy->getType2Hp(), enemyType::RUNNING);
        groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
    }
    else if(groupEnemy->getType3Total() > 0){
        enemy = Enemy::create(pointVector, groupEnemy->getType3Hp(), enemyType::SKATING);
        groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
    }
    
    this->addChild(enemy, 10);
    instance->enemyVector.pushBack(enemy);
    
    restEnemyNum--;
    groupEnemy->setEnemyTotal(restEnemyNum);
}



