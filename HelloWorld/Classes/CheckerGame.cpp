#include <stdio.h> 
#include <time.h> 
#include "resource.h"
#include "VisibleRect.h"
#include "CheckerGame.h"
#include "CheckerBoard.h"
#include "GameScene.h"
#include <algorithm>

USING_NS_CC;

const ccColor4F colors[]={
		ccc4f(1,0,0,0.5f),
		ccc4f(1,0.5f,0,0.5f),
		ccc4f(1,1,0,0.5f),
		ccc4f(0,1,0,0.5f),
		ccc4f(0,1,1,0.5f),
		ccc4f(0,0,1,0.5f),
		ccc4f(1,0,1,0.5f)
};

const float levels[]={	0.0f,	0.25f,	0.5f,
						1.5f,	1.7f,	1.9f,
						2.35f,	2.5f,	2.65f,
						3.0f,	3.1f,	3.2f,
						3.45f,	3.5f,	3.55f,
						3.85f,	3.9f,	3.95f,
						4.6f,	4.7f,	4.8f,
						10.0f,
};


bool CheckerGame::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }
	this->setTouchEnabled(true);
	return initilizeGame();
}

void CheckerGame::restart()
{
	this->removeAllChildren();
	initilizeGame();
	this->setTouchEnabled(true);
}

bool CheckerGame::initilizeGame()
{
	m_threhold			=	20;
	m_rockRate			=	0.0f;
	m_level				=	0;
	m_step				=	0;
	m_nextNum			=	0;
	m_nextIsRock		=	false;
	m_column			=	-1;
	m_canProp			=	true;
	m_killmode			=	false;
	srand((unsigned)time(NULL)); 
	m_preview = new CheckerPreview(this);
	m_content = new CheckerBoard(this);
	resetNext();
	m_preview->resetPreview(m_nextNum,m_nextIsRock);
	DrawBoard();

	mScore = Score::create();
	mScore->setPosition(ccp( 0, 0));
	addChild(mScore,10);

	m_Energy=Energy::create();
	m_Energy->setPosition(ccp( 0, 0));
	addChild(m_Energy,10);

	m_PropLayer = PropLayer::create(this);
	m_PropLayer->setPosition(ccp( 0, 0));
	addChild(m_PropLayer,10);
	Prop *p1=new BombProp(this,1);
	m_PropLayer->AddProp(0,p1);
	m_PropLayer->DisplayProp(s_pPathCloseNormal,s_pPathCloseSelect,s_pPathCloseNormal,0,p1);
	Prop *p2=new PrimeProp(this,1);
	m_PropLayer->AddProp(1,p2);
	m_PropLayer->DisplayProp(s_pPathCloseNormal,s_pPathCloseSelect,s_pPathCloseNormal,1,p2);
	Prop *p3=new KillProp(this,1);
	m_PropLayer->AddProp(2,p3);
	m_PropLayer->DisplayProp(s_pPathCloseNormal,s_pPathCloseSelect,s_pPathCloseNormal,2,p3);


	//initilize content
	for(int i=0;i!=25;++i)
	{
		int num=rand()%7+1;
		int col=rand()%7;
		while(m_content->getHeight(col)>5)
			col=rand()%7;
		int rock=rand()%2;
		m_content->addPiece(col,num,rock);
	}

	m_levelLabel = CCLabelBMFont::create("Level1", s_pPathScoreFont);
	m_levelLabel->setPosition(ccp( VisibleRect::right().x -150, VisibleRect::top().y - 40));
	addChild(m_levelLabel,2);


	char string[24] = {0};
	sprintf(string, "next level in %d drops", m_threhold);
	m_dropLabel = CCLabelBMFont::create(string, s_pPathScoreFont);
	m_dropLabel->setPosition(ccp( VisibleRect::left().x +100, VisibleRect::bottom().y + 40));
	addChild(m_dropLabel,2);
	m_dropLabel->setScale(0.5f);
	
	return true;
}

void CheckerGame::resetNext()
{
	m_nextNum=rand()%7+1;
	m_nextIsRock=float(rand()%10)<m_rockRate;
}

int CheckerGame::containsTouchColumnLocation(CCTouch* touch)
{
	for ( int i=0;i!=7;++i)
	{
		CCRect rect=CCRectMake(VisibleRect::unit()*i+VisibleRect::origin().x, VisibleRect::origin().y, VisibleRect::unit(), VisibleRect::unit()*8);
		if (rect.containsPoint(touch->getLocation()))
		{
			return i;
		}
	}
	return -1;
}

int CheckerGame::containsTouchRowLocation(CCTouch* touch)
{
	for ( int i=0;i!=7;++i)
	{
		CCRect rect=CCRectMake(VisibleRect::origin().x, VisibleRect::unit()*i+VisibleRect::origin().y, VisibleRect::unit()*7, VisibleRect::unit());
		if (rect.containsPoint(touch->getLocation()))
		{
			return i;
		}
	}
	return -1;
}

bool CheckerGame::canStart()
{
	for(unsigned int i =0;i!=7;++i)
	{
		if (m_content->getHeight(i)!=7)
			return true;
	}
	return false;
}

void CheckerGame::startLink(int column)
{
	mScore->tinyUp();
	CheckerPiece* cp = m_content->addPiece(column,m_nextNum,m_nextIsRock);
	if(cp)
		m_content->startLink(cp->GetGrid());

}


void CheckerGame::endLink()
{
	this->setTouchEnabled(true);
	if(m_preview->NeedReset())
	{
		CCLog("reset Preview");
		resetNext();
		m_preview->resetPreview(m_nextNum,m_nextIsRock);
	}
	m_canProp=true;
}

void CheckerGame::explose(int column)
{
	int k=m_content->getHeight(column);
	unsigned int left=(column-1<0)?0:(column-1);
	unsigned int right=(column+1>6)?6:(column+1);
	unsigned int bottom=(k-1<0)?0:(k-1);
	unsigned int top=(k+1>6)?6:(k+1);
	vector<Grid> list;
	for(unsigned int i=left;i!=right+1;++i)
	{
		for(unsigned int j=bottom;j!=top+1;++j)
		{
			list.push_back(Grid(i,j));
		}
	}
	m_content->KillPieces(list.begin(),list.end());
}

void CheckerGame::levelUp()
{
	if(m_step==(m_threhold-1))
	{
		if(!m_content->riseUp())
			gameOver();
		++m_level;
		if(m_level!=22)
			m_rockRate=levels[m_level];

		char string[12] = {0};
		sprintf(string, "Level%d", m_level);
		m_levelLabel->setString(string);
		m_step=0;

		mScore->levelUp();
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
	if(m_canProp)
	{
		if(m_killmode)
		{
			m_column=containsTouchColumnLocation(pTouch);
			m_row=containsTouchRowLocation(pTouch);
		}
		else
		{
			if(!canStart())
				gameOver();
			levelUp();
			m_column=containsTouchColumnLocation(pTouch);
			if(m_column>=0)
				m_preview->StartPreview(m_column);
			m_canProp=false;
		}
	}
	return true;
}

void CheckerGame::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_killmode)
	{
		m_column=containsTouchColumnLocation(pTouch);
		m_row=containsTouchRowLocation(pTouch);
	}
	else{
	m_column=containsTouchColumnLocation(pTouch);
	if(m_column>=0)
		m_preview->EditPreview(m_column);
	}
}

void CheckerGame::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_killmode)
	{
		vector<Grid> list;
		list.push_back(Grid(m_column,m_row));
		m_content->KillPieces(list.begin(),list.end());
		m_killmode=false;
	}
	else
	{
		if (m_column>=0)
		{
			m_preview->EndPreview(m_column);
			if(m_content->getHeight(m_column)!=7)
				this->setTouchEnabled(false);
			++m_step;
			char string[25] = {0};
			sprintf(string, "next level in %d drops", (m_threhold-m_step));
			m_dropLabel->setString(string);
		}
	}
	
}

CCSprite* CheckerGame::DrawPiece(const Grid element,const int num,const int rock)
{
	int n=0;
	if(rock!=0)
		n=9-rock;
	else
		n=num-1;
	CCSprite* pSprite = CCSprite::create(s_pPathPiece,CCRectMake(n*40,0,40,40));
	pSprite->setScale(0.99f);
	pSprite->setPosition(ccp(VisibleRect::unit()*element.x+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*element.y+0.5*VisibleRect::unit() +VisibleRect::origin().y));
	//pSprite->autorelease();
	addChild(pSprite,10);
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
	addChild(draw,12);
	
	int width=(end.x-start.x+1)*VisibleRect::unit();
	int height=(end.y-start.y+1)*VisibleRect::unit();
	CCPoint points[] = {CCPoint(VisibleRect::unit()*start.x+VisibleRect::origin().x, VisibleRect::unit()*start.y+VisibleRect::origin().y),
						CCPoint(VisibleRect::unit()*(end.x+1)+VisibleRect::origin().x, VisibleRect::unit()*start.y+VisibleRect::origin().y), 
						CCPoint(VisibleRect::unit()*(end.x+1)+VisibleRect::origin().x, VisibleRect::unit()*(end.y+1)+VisibleRect::origin().y),
						CCPoint(VisibleRect::unit()*start.x+VisibleRect::origin().x, VisibleRect::unit()*(end.y+1)+VisibleRect::origin().y)};
	draw->drawPolygon(points,4,ccc4f(1,1,1,0.5f), 0, ccc4f(0,0,0,0));
	
	CCFiniteTimeAction*  fadeOut = CCSequence::create(
		CCFadeOut::create(0.3),
		CCCallFuncN::create(this, callfuncN_selector(CheckerGame::onDrawGuide)),
        NULL);
	draw->runAction(fadeOut);
}

void CheckerGame::DrawLink(const Grid *elements, const int count,bool horizontal)
{
	CCDrawNode *draw = CCDrawNode::create();
	addChild(draw, 2);
	int k(0);
	Grid target = initPoint(elements,count);
	while(k!=count)
	{
		CCPoint pnt=CCPoint(VisibleRect::unit()*target.x+VisibleRect::origin().x, VisibleRect::unit()*target.y+VisibleRect::origin().y);
		CCPoint *points = createPoly(elements[k],pnt);

		draw->drawPolygon(points,4,colors[k], 0, colors[k]);
		target=nextPoint(target,elements,count,horizontal);
		++k;
	}
	CCFiniteTimeAction*  fadeOut = CCSequence::create(
		CCFadeOut::create(0.3),
		CCCallFuncN::create(this, callfuncN_selector(CheckerGame::onDrawGuide)),
		NULL);
	draw->runAction(fadeOut);
}

Grid CheckerGame::initPoint(const Grid *elements, const int count)
{
	int x= rand()%8;
	int y= rand()%8;
	while(containPoint(Grid(x,y),elements,count))
	{
		x= rand()%8;
		y= rand()%8;
	}
	return Grid(x,y);
}

bool CheckerGame::containPoint(const Grid point,const Grid *elements, const int count)
{
	for(int i = 0; i!=count;++i)
	{
		if (elements[i].x==point.x)
			return true;
		if (elements[i].x+1==point.x)
			return true;
		if (elements[i].y+1==point.y)
			return true;
		if (elements[i].y==point.y)
			return true;
	}
	return false;
}

CCPoint* CheckerGame::createPoly(const Grid element,const CCPoint pnt)
{
	CCPoint points[] = {
			CCPoint(VisibleRect::unit()*element.x+VisibleRect::origin().x, VisibleRect::unit()*element.y+VisibleRect::origin().y),
			CCPoint(VisibleRect::unit()*element.x+VisibleRect::origin().x, VisibleRect::unit()*(element.y+1)+VisibleRect::origin().y),
			CCPoint(VisibleRect::unit()*(element.x+1)+VisibleRect::origin().x, VisibleRect::unit()*(element.y+1)+VisibleRect::origin().y),
			CCPoint(VisibleRect::unit()*(element.x+1)+VisibleRect::origin().x, VisibleRect::unit()*element.y+VisibleRect::origin().y)};	
	CCPoint *out;
	out= new CCPoint[4];
	float tan=(points[0].x-pnt.x)/(points[0].y-pnt.y);
	unsigned int i(0),j(0);
	while(i!=4)
	{
		float t=(points[i].x-pnt.x)/(points[i].y-pnt.y);
		if (t<tan)
		{
			tan=(points[i].x-pnt.x)/(points[i].y-pnt.y);
			j=i;
		}
		++i;
	}
	for(unsigned int k = 0;k!=3;++k)
	{
		out[k]=points[j%4];
		++j;
	}
	out[3]=pnt;
	return out;
}

Grid CheckerGame::nextPoint(const Grid current,const Grid *elements, const int count,bool horizontal)
{
	Grid next=current;
	if(horizontal)
		next.x=(next.x+1)%8;
	else
		next.y=(next.y+1)%8;
	while(containPoint(next,elements,count))
	{
		if(horizontal)
			next.x=(next.x+1)%8;
		else
			next.y=(next.y+1)%8;
	}
	return next;
}

void CheckerGame::onDrawGuide(CCNode* node)
{
	node->removeFromParent();
}

void CheckerGame::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0, true);
}
