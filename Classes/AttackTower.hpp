//
//  AttackTower.hpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/11.
//
//

#ifndef AttackTower_hpp
#define AttackTower_hpp

#include "Tower.hpp"

class AttackTower: public Tower{
public:
	//Initialize specificly all kinds of data of the tower like 'AttackTower';
	virtual bool init() override;

	//Get the memory from the heep,and call the init function to initialize the date;
	CREATE_FUNC(AttackTower);

	//Rotate the berrel to the enemies when the enemy is coming;
	void rotateAndShoot(float dt);

	//Create the bullet by calling the creating function of class 'Bullet'; 
	Bullet* addAttackTowerBullet();

	//Move the bullet to enemy;
	//Calculate the distance,direction between the tower and the enemy;
	void shoot();

	//Spend money to upgrade the tower including scope,rate;
    void upgrade() override;
    
private:
	//The data is used to record the parent position when remove the bullet;
    Sprite* baseplate;
	//must be a data to replace another sprite;
    Sprite* rotateArrow;
    
};
#endif /* AttackTower_hpp */
