#include "LevelScene.h"
#include "ScrollView.h"
USING_NS_CC;

ScrollView::ScrollView()
	:pageNode(0)
	, curPageNode(0)
{
}

ScrollView::~ScrollView()
{
}

void ScrollView::goToCurrNode(){
	this->runAction(MoveTo::create(0.4f, Point::Vec2(-curPageNode * WINDOW_WIDTH, 0)));
}

void ScrollView::addNode(Node *level){
	if (level){
		level->setContentSize(Size::Size(WINDOW_WIDTH, WINDOW_HEIGHT));
		level->setPosition(Vec2(WINDOW_WIDTH * pageNode, 0));
		this->addChild(level);
		pageNode++;
	}
}

bool ScrollView::onTouchBegan(Touch *touch, Event  *event){
	touchDownPoint = touch->getLocation();
	touchCurPoint = touchDownPoint;
	return true;
}

void ScrollView::onTouchMoved(Touch *touch, Event  *event){
	Vec2 touchPoint = touch->getLocation();
	auto currX = this->getPositionX() + touchPoint.x - touchCurPoint.x;
	Vec2 posPoint = Point::Vec2(currX, getPositionY());
	auto dis = fabsf(touchPoint.x - touchCurPoint.x);
	if (dis >= SHORTEST_SLIDE_LENGTH) {
		setPosition(posPoint);
	}
	touchCurPoint = touchPoint;
}

void ScrollView::onTouchEnded(Touch *touch, Event  *event){
	touchUpPoint = touch->getLocation();
	auto dis = touchUpPoint.getDistance(touchDownPoint);
	// mark of current node
	auto sprite1 = Sprite::create("currentPage.png");
	auto width = sprite1->getContentSize().width;
	if (dis >= SHORTEST_SLIDE_LENGTH){
		//mark the end of slide and judge the direction of your move
		int offset = getPositionX() - curPageNode * (-WINDOW_WIDTH);
		if (offset > width) {
			//last page
			if (curPageNode > 0) {
				--curPageNode;
				//set the position of the mark of current page
				Sprite *sprite = (Sprite *)LevelScene::getInstance()->getChildByTag(666);
				sprite->setPosition(Vec2(sprite->getPositionX() - width, sprite->getPositionY()));
			}
		}
		else if (offset < -width) {
			//next page
			if (curPageNode < (pageNode - 1)) {
				++curPageNode;
				Sprite *sprite = (Sprite *)LevelScene::getInstance()->getChildByTag(666);
				sprite->setPosition(Vec2(sprite->getPositionX() + width, sprite->getPositionY()));
			}
		}
		//change to certain node
		goToCurrNode();
	}
}

bool ScrollView::init(){
	if (!Layer::init()){
		return false;
	}

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(ScrollView::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ScrollView::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ScrollView::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	WINDOW_WIDTH = Director::getInstance()->getWinSize().width;
	WINDOW_HEIGHT = Director::getInstance()->getWinSize().height;

	return true;
}
