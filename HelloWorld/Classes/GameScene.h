#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "CheckerBoard.h"
#include "MenuLayers.h"


USING_NS_CC;

class PopoutMenu;

class GameScene : public CCScene
{
public:
	GameScene();
	~GameScene();

	void menuCallback(CCObject* pSender);

	void startGame();

	void resumeGame();

	void gameOver();

	void restart();

	void switchMenu(PopoutMenu *next);

	int getScore();

	CheckerGame *gameLayer;

	PopoutMenu* menuLayer;

	PopoutMenu* prevLayer;
};

#endif // __GAMESCENE_H__
