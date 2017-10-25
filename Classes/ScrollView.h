#ifndef __SCROLLVIEW_SCENE_H__
#define __SCROLLVIEW_SCENE_H__

#include "cocos2d.h"  

USING_NS_CC;

#define SHORTEST_SLIDE_LENGTH (5)

//the container for LevelSelectedPage nodes
class ScrollView : public Layer{
private:

	//total nodes 
	int pageNode;

	//current node 
	int curPageNode;

	//to record the position of your touchdownpoint,touchuppoint and your current touchpoint
	Vec2 touchDownPoint;
	Vec2 touchUpPoint;
	Vec2 touchCurPoint;

	//the constant length and height of the layer
	float WINDOW_WIDTH;
	float WINDOW_HEIGHT;

	//go to certain node according to the distance and direction you move
	void goToCurrNode();

public:
	ScrollView();
	~ScrollView();

	virtual bool init();
	CREATE_FUNC(ScrollView);

	//to record whether you have began to touch 
	//and record the touchDownPoint and touchCurPoint
	bool onTouchBegan(Touch *touch, Event  *event);
	
	//to record the touchCurPoint and calculate the move distance
	//if the move distance > SHORTEST_SLIDE_LENGTH,set the position of layer at the position you moved to
	//in order to get the effect of slide
	void onTouchMoved(Touch *touch, Event  *event);

	//to record your touchEndPoint and calculate the move distance
	//if the move distance > SHORTEST_SLIDE_LENGTH , go to the certain node and move the mark of current page
	void onTouchEnded(Touch *touch, Event  *event);

	//add nodes to the layer
	void addNode(Node *level);
};
#endif // __SCROLLVIEW_SCENE_H__