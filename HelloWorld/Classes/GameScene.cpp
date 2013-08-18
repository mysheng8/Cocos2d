#include "GameScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "CheckerBoard.h"
#include "MenuScene.h"

USING_NS_CC;

GameScene::GameScene()
{
	CCScene::init();
	boardLayer = 0;
	menuLayer=0;

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathCloseNormal, s_pPathCloseSelect, this, menu_selector(GameScene::menuCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);
	pCloseItem->setPosition(ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 50));
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
	menuLayer->setVisible(false);

}

void GameScene::menuCallback(CCObject* pSender)
{
	menuLayer->setVisible(true);
}

void GameScene::startGame()
{
	boardLayer = CheckerBoard::create();
	addChild(boardLayer,0);
    CCDirector::sharedDirector()->replaceScene(this);

}

void GameScene::resumeGame()
{
	menuLayer->setVisible(false);
}

GameScene::~GameScene()
{
}