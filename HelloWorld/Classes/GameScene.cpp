#include "GameScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "CheckerBoard.h"
#include "MenuScene.h"
#include "GameOver.h"

USING_NS_CC;

GameScene::GameScene()
{
	CCScene::init();
	gameLayer = 0;
	menuLayer=0;
	overLayer=0;

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathCloseNormal, s_pPathCloseSelect, this, menu_selector(GameScene::menuCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);
	pCloseItem->setPosition(ccp( VisibleRect::left().x + 50, VisibleRect::top().y - 40));
    pMenu->setPosition( CCPointZero );
	addChild(pMenu, 1);
}

void GameScene::onEnter()
{
	CCScene::onEnter();
	if(!menuLayer){
		menuLayer = new MenuScene();
		addChild(menuLayer,1);
		menuLayer->release();
	}


	if(!overLayer){
		overLayer = new GameOver();
		addChild(overLayer,1);
		overLayer->release();
	}
	overLayer->setVisible(false);

}

void GameScene::menuCallback(CCObject* pSender)
{
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
	if(gameLayer)
		gameLayer->restart();
}


void GameScene::resumeGame()
{
	menuLayer->jumpOut();
}

void GameScene::gameOver()
{
	overLayer->setVisible(true);
}

GameScene::~GameScene()
{
}