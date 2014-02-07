#include <stdio.h> 
#include <time.h> 
#include "resource.h"
#include "VisibleRect.h"
#include "GameLayer.h"
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

bool GameLayer::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }
	this->setTouchEnabled(false);
	return initilizeGame();
}

void GameLayer::restart()
{
	this->removeAllChildren();
	initilizeGame();
	this->setTouchEnabled(false);
	
}

bool GameLayer::initilizeGame()
{
	data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
//	m_nextNum			=	0;
//	m_nextIsRock		=	false;
	m_column			=	-1;
	m_canProp			=	true;
	m_killmode			=	false;
	
	m_preview = new CheckerPreview(this);
	m_content = new CheckerBoard(this);
	resetNext();
	m_preview->resetPreview();
	DrawBoard();

	mScore = Score::create();
	mScore->setPosition(ccp( 0, 0));
	addChild(mScore,20);

	m_Energy=Energy::create();
	m_Energy->setPosition(ccp( 0, 0));
	addChild(m_Energy,20);

	m_PropLayer = PropLayer::create(this);
	m_PropLayer->setPosition(ccp( 0, 0));
	addChild(m_PropLayer,20);

	//initilize content
	for(int i=0;i!=25;++i)
	{
		int num=rand()%7+1;
		int col=rand()%7;
		while(m_content->getHeight(col)>5)
			col=rand()%7;
		int rock=rand()%2;
		m_content->addPiece(col,num,rock,false);
	}

	m_levelLabel = CCLabelBMFont::create("Level1", s_pPathScoreFont);
	m_levelLabel->setPosition(ccp( VisibleRect::right().x -150, VisibleRect::top().y - 40));
	addChild(m_levelLabel,2);


	char string[24] = {0};
	sprintf(string, "next level in %d drops", data->m_level->m_next);
	m_dropLabel = CCLabelBMFont::create(string, s_pPathScoreFont);
	m_dropLabel->setPosition(ccp( VisibleRect::left().x +100, VisibleRect::bottom().y + 40));
	addChild(m_dropLabel,2);
	m_dropLabel->setScale(0.5f);

	return true;
}

void GameLayer::resetNext()
{
	data->m_nextNum=rand()%7+1;
	data->m_nextIsRock=float(rand()%10)<data->m_level->m_rockRate;
}

int GameLayer::containsTouchColumnLocation(CCTouch* touch)
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

int GameLayer::containsTouchRowLocation(CCTouch* touch)
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

bool GameLayer::canStart()
{
	for(unsigned int i =0;i!=7;++i)
	{
		if (m_content->getHeight(i)!=7)
			return true;
	}
	return false;
}

void GameLayer::checkBuffer()
{
	if(data->m_buf->m_type==BufferType(NONE))
		return;
	if(data->m_buf->m_period==0)
	{
		if(data->m_buf->m_type==BufferType(DOUBLESCORE))
		{
			int t=data->m_score->m_total;
			data->m_score=static_cast<ScoreData*>(data->m_buf->m_bufData);
			data->m_score->m_total=t;
		}
		else if(data->m_buf->m_type==BufferType(POWERENERGY)||data->m_buf->m_type==BufferType(NOENERGY))
		{
			int t=data->m_energy->m_totalEnergy;
			data->m_energy=static_cast<EnergyData*>(data->m_buf->m_bufData);
			data->m_energy->m_totalEnergy = t;
		}
		data->m_buf->m_type=BufferType(NONE);
	}
	else
		--data->m_buf->m_period;
}

void GameLayer::riseBufferUI(const char* str)
{
	CCLabelBMFont*	bufUI = CCLabelBMFont::create(str,s_pPathScoreFont);
	bufUI->setPosition(ccp( VisibleRect::center().x, VisibleRect::center().y+10));
	bufUI->setScale(1.3f);
	//bonus->setColor(bcolors[(sdata->m_multi)%6]);
	addChild(bufUI,1);
	CCFiniteTimeAction*  rise = CCSequence::create(
		CCJumpBy::create(0.3f,ccp(0,0),70,1),
		CCFadeOut::create(1),
		CCCallFuncN::create(this, callfuncN_selector(GameLayer::onDisappear)),
        NULL);
	bufUI->runAction(rise);
}

void GameLayer::onDisappear(CCNode* node)
{
	node->removeFromParent();
}


void GameLayer::startLink(int column,const bool isBomb)
{
	data->m_score->m_total+=data->m_score->m_dropScore;
	mScore->tinyUp();
	CheckerPiece* cp = m_content->addPiece(column,data->m_nextNum,data->m_nextIsRock,isBomb);
	if(cp)
		m_content->startLink(cp->GetGrid(),isBomb);
}


void GameLayer::endLink()
{
	this->setTouchEnabled(true);
	if(m_preview->NeedReset())
	{
		//CCLog("reset Preview");
		resetNext();
		m_preview->resetPreview();
	}
	m_canProp=true;
	checkBuffer();
#ifdef JACKPOT
	m_content->setJackpot();
#endif
}

void GameLayer::levelUp()
{
	if(!m_content->riseUp())
		gameOver();

	char string[12] = {0};
	sprintf(string, "Level%d", data->m_level->m_current);
	m_levelLabel->setString(string);
	mScore->levelUp();
	data->m_level=data->m_level->m_nextlevel;
	
}

void GameLayer::gameOver()
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);
    // game over
	pScene->gameOver();
}

void GameLayer::BombMode()
{
	m_preview->BombMode();
}

void GameLayer::RandomMode()
{
	m_preview->RandomMode();
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
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
			if(data->m_level->m_next==0)
				levelUp();
			m_column=containsTouchColumnLocation(pTouch);
			if(m_column>=0)
				m_preview->StartPreview(m_column);
			m_canProp=false;
		}
	}
	return true;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
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
			--data->m_level->m_next;
			char string[25] = {0};
			sprintf(string, "next level in %d drops", (data->m_level->m_next));
			m_dropLabel->setString(string);
		}
	}
	
}

CCSprite* GameLayer::DrawPiece(const Grid element,const int num,const int rock,const bool isBomb)
{
	CCSprite* pSprite;
	if(isBomb)
	{
		pSprite=CCSprite::create(s_pPathPiece,CCRectMake(9*40,0,40,40));
	}
	else
	{
		int n=0;
		if(rock!=0)
			n=9-rock;
		else
			n=num-1;
		pSprite = CCSprite::create(s_pPathPiece,CCRectMake(n*40,0,40,40));
	}
	pSprite->setScale(0.99f);
	pSprite->setPosition(ccp(VisibleRect::unit()*element.x+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*element.y+0.5*VisibleRect::unit() +VisibleRect::origin().y));
	//pSprite->autorelease();
	addChild(pSprite,10);
	return pSprite;
}

void GameLayer::DrawBoard()
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

void GameLayer::DrawGuide(const Grid start,const Grid end)
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
		CCCallFuncN::create(this, callfuncN_selector(GameLayer::onDrawGuide)),
        NULL);
	draw->runAction(fadeOut);
}

void GameLayer::DrawLink(const Grid *elements, const int count,bool horizontal)
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
		CCCallFuncN::create(this, callfuncN_selector(GameLayer::onDrawGuide)),
		NULL);
	draw->runAction(fadeOut);
}

Grid GameLayer::initPoint(const Grid *elements, const int count)
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

bool GameLayer::containPoint(const Grid point,const Grid *elements, const int count)
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

CCPoint* GameLayer::createPoly(const Grid element,const CCPoint pnt)
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

Grid GameLayer::nextPoint(const Grid current,const Grid *elements, const int count,bool horizontal)
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

void GameLayer::onDrawGuide(CCNode* node)
{
	node->removeFromParent();
}

void GameLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0, true);
}

void GameLayer::InitProps(vector<string>::iterator begin,vector<string>::iterator end)
{
	unsigned int cur=0;
	for(vector<string>::iterator it=begin;it!=end;++it)
	{
		Prop *p=static_cast<Prop*>(PropFactory::sharedClassFactory().GetPropByName(*it));
		PropData *pdata=static_cast<PropData*>(GameSettingData::sharedSettingData().GetData(*it));
		data->m_props.insert(pair<string,PropData*>(pdata->m_name,pdata));
		//p->init(pdata->m_cost,pdata->m_num);
		m_PropLayer->AddProp(cur,p);
		++cur;
	}
}

void GameLayer::UseProp(Prop *p)
{
	PropData *pdata=(data->m_props.find(p->GetType()))->second;
	if(((pdata->m_cost)<=(data->m_energy->m_totalEnergy))&&m_canProp&&pdata->m_num>0)
	{
		if (p->function())
		{
			data->m_energy->m_totalEnergy-=pdata->m_cost;
			m_Energy->Change();
			--pdata->m_num;
		}
	}
	for(map<string ,PropData*>::iterator it=data->m_props.begin();it!=data->m_props.end();++it)
	{
		if (data->m_energy->m_totalEnergy<it->second->m_cost)
		{
			PropSprite *pSp=m_PropLayer->GetPropSprite(it->first);
			pSp->setEnabled(false);
		}
	}
}

void GameLayer::EnergyUp()
{
	data->m_energy->m_multi=1.2;
}

void GameLayer::EnergyCharge()
{
	data->m_energy->m_totalEnergy+=data->m_energy->m_spring*data->m_energy->m_multi;
	if (data->m_energy->m_totalEnergy>100)
		data->m_energy->m_totalEnergy=100;
	m_Energy->Change();
	for(map<string ,PropData*>::iterator it=data->m_props.begin();it!=data->m_props.end();++it)
	{
		if (data->m_energy->m_totalEnergy>=it->second->m_cost)
		{
			PropSprite *pSp=m_PropLayer->GetPropSprite(it->first);
			if(!pSp->isEnabled())
				pSp->Active();
		}
	}
}

void GameLayer::LowEnergy()
{
	m_Energy->LowEnergy();
}

void GameLayer::ScoreUp()
{
	data->m_score->m_total+=data->m_score->m_killScore;
	mScore->score();
}

void GameLayer::PropUp()
{
	data->m_score->m_total+=data->m_score->m_propScore;
	mScore->PropUp();
}

void GameLayer::ScoreRiseMulti()
{
	++data->m_score->m_multi;
	mScore->raiseMulti();
}

void GameLayer::ResetMulti()
{
	data->m_score->m_multi=1;
}

int GameLayer::GetMulti()
{
	return data->m_score->m_multi;
}

int GameLayer::GetScore()
{
	return data->m_score->m_total;
}

void GameLayer::DelayLevel(const unsigned int num)
{
	data->m_level->m_next+=num;
	char string[25] = {0};
	sprintf(string, "next level in %d drops", (data->m_level->m_next));
	m_dropLabel->setString(string);
}

void GameLayer::InsertRock(const Grid grid)
{
	int num=rand()%7+1;
	m_content->InsertPiece(grid,num,true,false);
}

void GameLayer::InsertBomb(const Grid grid)
{
	m_content->InsertPiece(grid,0,false,true);

}

CheckerBoard* GameLayer::GetContent()
{
	return m_content;
}

CheckerPiece* GameLayer::GetCheckerPiece(unsigned int column, unsigned int row)
{
	return m_content->getCheckerPiece(column,row);
}

CCSprite* GameLayer::DrawJackpot(const Grid grid)
{
	CCSprite *sp=CCSprite::createWithSpriteFrame(CCSpriteFrame::create(s_pPathJackpot,CCRectMake(0,0,40,40)));
	CCArray *animFrame=CCArray::create();
	for(unsigned int i = 0;i!=8;++i)
	{
		CCSpriteFrame *spf=CCSpriteFrame::create(s_pPathJackpot,CCRectMake(40*(i),0,40,40));
		animFrame->addObject(spf);
	}
	CCAnimation *anim=CCAnimation::createWithSpriteFrames(animFrame,0.05f);
	sp->runAction(CCRepeatForever::create(CCAnimate::create(anim)));
	sp->setPosition(ccp(VisibleRect::unit()*grid.x+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*grid.y+0.5*VisibleRect::unit() +VisibleRect::origin().y));
	addChild(sp,10);
	return sp;
}

