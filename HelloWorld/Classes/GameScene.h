#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "MenuLayers.h"


USING_NS_CC;




class PopoutMenu;
class GameLayer;

class GameScene : public CCScene
{
private:
	GameScene();

	void initGameData();

	vector<JackpotData*> j_list;

	void onRestart();

	void onSwitch();

	void onQuit();

public:
	~GameScene();
	
	static GameScene& sharedGameScene();

	void menuCallback(CCObject* pSender);

	void startGame();

	void resumeGame();

	void gameOver();

	void restart();

	void switchMenu();

	void quitGame();

	GameLayer* gameLayer;

	PopoutMenu* menuLayer;

	PopoutMenu* prevLayer;

	PopoutMenu* nextLayer;

	PopoutMenu* propLayer;

	void randomJackpot();

	//Android function
	virtual void keyMenuClicked();

};


class RandomJackpot
{
public:
	static vector<JackpotData*>::iterator getRandomJackpot(vector<JackpotData*>::iterator begin,vector<JackpotData*>::iterator end);

};

#endif // __GAMESCENE_H__
