#include <stdio.h> 
#include <time.h> 
#include "resource.h"
#include "VisibleRect.h"
#include "CheckerGame.h"
#include "CheckerBoard.h"
#include "GameScene.h"
#include <algorithm>


USING_NS_CC;

bool CheckerGame::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }
	initilizeGame();
	this->setTouchEnabled(true);
}

bool CheckerGame::initilizeGame()
{
	m_threhold			=	20;
	m_rockRate			=	6.0f;
	m_level				=	0;
	m_nextNum			=	0;
	m_nextIsRock		=	false;
	m_column			=	-1;
	m_resetNext			=	true;
	srand((unsigned)time(NULL)); 
	m_preview = new CheckerPreview(this);
	m_content = new CheckerBoard(this);

	
	DrawBoard();

	mScore = Score::create();
	mScore->setPosition(ccp( 0, 0));
	addChild(mScore,2);


	m_content->addPiece(0,1,false);
	m_content->addPiece(0,7,true);
	m_content->addPiece(1,2,false);
	m_content->addPiece(2,3,false);
	m_content->addPiece(3,4,false);
	m_content->addPiece(4,5,false);
	m_content->addPiece(5,6,false);
	m_content->addPiece(6,7,true);



	return true;
}

void CheckerGame::resetNext()
{
	m_nextNum=rand()%7+1;
	m_nextIsRock=rand()%10>m_rockRate;
	m_resetNext=false;
}

int CheckerGame::containsTouchLocation(CCTouch* touch)
{
	for ( int i=0;i!=7;++i)
	{
		CCRect rect=CCRectMake(VisibleRect::unit()*i+VisibleRect::origin().x, VisibleRect::origin().y, VisibleRect::unit(), VisibleRect::unit()*7);
		if (rect.containsPoint(touch->getLocation()))
		{
			return i;
		}
	}
	return -1;
}



void CheckerGame::startLink(int column)
{
	CheckerPiece* cp = m_content->addPiece(column,m_nextNum,m_nextIsRock);
	if(cp)
		m_content->startLink(cp->GetGrid());
	m_resetNext=true;
}

void CheckerGame::endLink()
{
	this->setTouchEnabled(true);
}

void CheckerGame::levelUp()
{
	if(m_level%m_threhold==(m_threhold-1))
	{
		if(!m_content->levelUp())
			gameOver();
	}
}
void CheckerGame::gameOver()
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);
    // game over
	pScene->gameOver();

}

bool CheckerGame::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	levelUp();
	m_column=containsTouchLocation(pTouch);
	if(m_resetNext)
		resetNext();
	m_preview->resetPreview(m_nextNum,m_nextIsRock);
	m_preview->StartPreview(m_column);
	return true;
}

void CheckerGame::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	m_column=containsTouchLocation(pTouch);
	m_preview->EditPreview(m_column);
}

void CheckerGame::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_column>=0)
		m_preview->EndPreview(m_column);
	++m_level;
	this->setTouchEnabled(false);
}

CCSprite* CheckerGame::DrawPiece(const Grid element,const int num,const int rock)
{
		int n=0;
		if(rock!=0)
			n=9-rock;
		else
			n=num-1;
		CCSprite* pSprite = CCSprite::create(s_pPathPiece,CCRectMake(n*34,0,34,34));
		pSprite->setPosition(ccp(VisibleRect::unit()*element.x+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*element.y+0.5*VisibleRect::unit() +VisibleRect::origin().y));
		//pSprite->autorelease();
		addChild(pSprite);
		return pSprite;
}

void CheckerGame::DrawBoard()
{
	for ( int i=0;i!=8;++i)
	{
		for ( int j=0;j!=8;++j)
		{
			CCSprite* pSprite = CCSprite::create(s_pPathAnchor);
			pSprite->setPosition(ccp(VisibleRect::unit()*i+VisibleRect::origin().x, VisibleRect::unit()*j+VisibleRect::origin().y));
			this->addChild(pSprite, 1);
		}
	}
	CCSprite* pSprite = CCSprite::create(s_pPathBG);

    pSprite->setPosition(ccp(VisibleRect::center().x,  VisibleRect::center().y));

    addChild(pSprite, 0);
}

void CheckerGame::DrawGuide(const Grid start,const Grid end)
{
	CCDrawNode *draw = CCDrawNode::create();
    addChild(draw, 10);
	int width=(end.x-start.x+1)*VisibleRect::unit();
	int height=(end.y-start.y+1)*VisibleRect::unit();
	CCPoint points[] = {CCPoint(VisibleRect::unit()*start.x+VisibleRect::origin().x, VisibleRect::unit()*start.y+VisibleRect::origin().y),
						CCPoint(VisibleRect::unit()*(end.x+1)+VisibleRect::origin().x, VisibleRect::unit()*start.y+VisibleRect::origin().y), 
						CCPoint(VisibleRect::unit()*(end.x+1)+VisibleRect::origin().x, VisibleRect::unit()*(end.y+1)+VisibleRect::origin().y),
						CCPoint(VisibleRect::unit()*start.x+VisibleRect::origin().x, VisibleRect::unit()*(end.y+1)+VisibleRect::origin().y)};
	draw->drawPolygon(points,4,ccc4f(1,1,1,0.3), 0, ccc4f(0,0,0,0));
	CCFiniteTimeAction*  fadeOut = CCSequence::create(
		CCFadeOut::create(0.5),
		CCCallFuncN::create(this, callfuncN_selector(CheckerGame::onDrawGuide)),
        NULL);
	draw->runAction(fadeOut);
}

void CheckerGame::onDrawGuide(CCNode* node)
{
	node->removeFromParent();
}

void CheckerGame::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0, true);
}
