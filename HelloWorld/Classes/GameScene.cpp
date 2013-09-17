#include "GameScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "CheckerBoard.h"
#include "MenuScene.h"

USING_NS_CC;

GameScene::GameScene()
{
	CCScene::init();
	gameLayer = 0;
	menuLayer = 0;
	prevLayer = 0;

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathCloseNormal, s_pPathCloseSelect, this, menu_selector(GameScene::menuCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);
	pCloseItem->setPosition(ccp( VisibleRect::left().x + 50, VisibleRect::top().y - 40));
    pMenu->setPosition( CCPointZero );
	addChild(pMenu, 1);
}

void GameScene::menuCallback(CCObject* pSender)
{
	if(menuLayer)
		removeChild(menuLayer);
	menuLayer = new MenuScene();
	addChild(menuLayer,1);
	menuLayer->release();
	menuLayer->jumpIn();
}

void GameScene::startGame()
{
	if(gameLayer)
		gameLayer->removeFromParent();
	gameLayer = CheckerGame::create();
	addChild(gameLayer,0);
    CCDirector::sharedDirector()->replaceScene(this);

}
void GameScene::restart()
{
	if(menuLayer)
		menuLayer->jumpOut();
	if(gameLayer)
		gameLayer->restart();
}


void GameScene::resumeGame()
{
	menuLayer->jumpOut();
}

void GameScene::gameOver()
{
	removeChild(menuLayer);
	gameLayer->setTouchEnabled(false);
	menuLayer = new GameOverLayer(this);
	addChild(menuLayer,1);
	menuLayer->jumpIn();
}

void GameScene::switchMenu(PopoutMenu *next)
{
	if(prevLayer&&prevLayer!=next)
		prevLayer->cleanup();
	prevLayer=menuLayer;
	menuLayer->jumpOut();
	removeChild(menuLayer,false);



	menuLayer = next;
	addChild(menuLayer,1);
	menuLayer->jumpIn();
}

GameScene::~GameScene()
{
}

int GameScene::getScore()
{
	return gameLayer->mScore->getScore();
}