//
//  MultiDirTower.hpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/11.
//
//

#ifndef MultiDirTower_hpp
#define MultiDirTower_hpp

#include "Tower.hpp"


class MultiDirTower : public Tower{
public:
	//Initialize specificly all kinds of data of the 'MultiDirTower'; the shooting scope,tower value and so on; 
	virtual bool init() override;

	//Get the memory from the heep, and call the init function to initialize the date;
	CREATE_FUNC(MultiDirTower);

	//Move the bullet to enemy;
	//Calculate the distance,direction between the tower and the enemy;
	//calling a time of the shoot fountion will call dieTotal time of the 'Bullet' shoot fountion;
	//the param dt is delay time;
	void shoot(float dt);

	//Create the bullet by calling the creating function of class 'Bullet';
	//Record the parent node's position;
	Bullet* addMultiDirTowerBullet();

	//Upgrade the tower including the scope,shooting frequency;
    void upgrade() override;
    
	//Set the total shooting directions;
    CC_SYNTHESIZE(int, dirTotal, DirTotal);
private:
	//the data is used to record the parent position when remove the bullet;
    Sprite* multiDirTower;
};

#endif /* MultiDirTower_hpp */
