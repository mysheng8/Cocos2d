#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CheckerBoard.h"
#include "MenuScene.h"

USING_NS_CC;



class GameScene : public CCScene
{
public:
	GameScene();
	~GameScene();

	virtual void onEnter();

	void menuCallback(CCObject* pSender);

	void startGame();

	void resumeGame();

	CheckerBoard *boardLayer;

	MenuScene* menuLayer;
};

#endif // __GAME_SCENE_H__
