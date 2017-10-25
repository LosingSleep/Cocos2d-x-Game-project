//
//  ColdTower.hpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/11.
//
//

#ifndef ColdTower_hpp
#define ColdTower_hpp

#include "Tower.hpp"

class ColdTower: public Tower{
public:
	//Initialize specificly all kinds of data of the 'ColdTower',and the shooting frequency; 
	virtual bool init() override;

	//Get the memory from the heep,and call the init function to initialize the date;
	CREATE_FUNC(ColdTower);

	//Add the bullet by calling the creating function of class 'Bullet'; 
	Bullet* addColdTowerBullet();

	//Move the bullet to enemy;
	//Calculate the distance,direction between the tower and the enemy;
	void shoot(float dt);

	//Upgrade the tower;
    void upgrade() override;
    
private:
	//the data is used to record the parent position when remove the bullet;
    Sprite* baseplate;
};

#endif /* ColdTower_hpp */
