#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CheckerBoard.h"
#include "MenuScene.h"


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

#endif // __GAME_SCENE_H__
