//
//  GamePlayLayer.hpp
//  MyGame
//
//  Created by 陈晖 on 16/5/24.
//
//

#ifndef GamePlayLayer_hpp
#define GamePlayLayer_hpp


#include "cocos2d.h"
#include "TowerPanleLayer.hpp"
#include "GameManager.hpp"
#include "Enemy.hpp"
#include "TowerOperateLayer.hpp"


class GamePlayLayer: public cocos2d::Layer{
public:
    
    GamePlayLayer();
    ~GamePlayLayer();
    
    //init the game layer
    virtual bool init() override;
    
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(GamePlayLayer);
    
    //override the callback function for touch began.
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    
    //call back function for the return button.
    void menuBackCallback(Ref* pSender);
    
    //call back function for the music button.
    void menuMusicStop(Ref* psender);
    void menuMusicStart(Ref* psender);
    
	//override the update function.
    void update(float dt) override;

private:
    //init the tool layer, which contains the money, current playerHp and some button.
    void initToolLayer();
    
    //init the pointVector in current map.
    void initPointVector();
    
    //check the touch type and handle it.
    void checkAndHandleTouch(cocos2d::Vec2 position);
    
    //add towerChoosePanle in the touch position
    void addTowerChoosePanle(cocos2d::Vec2 position);
    
    //add towerOperaPanle in the touch position
    void addTowerOperatePanle(cocos2d::Vec2 position);
    
    //convert the OpenGL coord into tile coord.
    cocos2d::Vec2 convertToTileCoord(cocos2d::Vec2 position);

	//convert the OpenGL coord into the matrix coord, which using to record the panles have tower.
    cocos2d::Vec2 convertToMatrixCoord(cocos2d::Vec2 position);

	//checking the collisions between enemy and bullet.
    void collisionDetection();

	//checking whether the game is successful or not.
	//if the game is successful, update the level information and replace scene to WinScene.
    void isSuccessful();

	//checking whether the enemy arrived home or not
	//if the enemy arrived home, remove the enemy and reduce the playerHp.
    void enemyIntoHome();

	//add enemy according to the information storing in each group.
    void gameLogic(float dt);

    void addEnemy();

    void addTower();

	//operate tower that player chose.
	//delete the tower or upgrade the tower.
    void operateTower();
    
	//get the current group of enemy from GameManager.
    GroupEnemy* getCurrentGroup();

	//get the next group of enemy from GameManager.
    GroupEnemy* getNextGroup();




	//instance get from GameManager.
    GameManager* instance;
	//record the points enemy need to run.
    cocos2d::Vector<cocos2d::Node*> pointVector;
    
	/*the datas about the TMXTileMap*/
    cocos2d::TMXTiledMap* map;
    cocos2d::TMXObjectGroup* objects;
    cocos2d::TMXLayer* backgroundLayer;
    cocos2d::TMXLayer* roadLayer;
    int mapWidth;
    int mapHeight;

    TowerPanleLayer* choseTowerpanle;
    TowerOperateLayer* choseTowerOperatepanle;
    
    Layer* toolLayer;
    cocos2d::Label* moneyLabel;
    CC_SYNTHESIZE(float, playHpPercentage, PlayHpPercentage);
    CC_SYNTHESIZE_READONLY(cocos2d::ProgressTimer*, playHpBar, PlayHpBar);
    
    int money;

	//count the group that had be added.
    int groupCounter;

    bool successful;
    
    int choseTowerInMatrix;

	//the position need to be put tower on.
    cocos2d::Vec2 towerPos;

	//a two-dimension array using to record the panles that have been put tower.
    Tower **towerMatrix;
};


#endif /* GamePlayLayer_hpp */
