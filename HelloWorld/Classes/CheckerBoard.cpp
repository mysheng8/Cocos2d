
#include <stdio.h> 
#include <time.h> 
#include "resource.h"
#include "VisibleRect.h"
#include "CheckerBoard.h"


USING_NS_CC;

bool CheckerBoard::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }

	content=new CheckerPiece*[7];
	for(int i=0;i!=7;++i)
	{
		content[i]=new CheckerPiece[7];
	}
	for(int i=0;i!=7;++i)
	{
		for(int j=0;j!=7;++j)
		{
			content[i][j].init(this,Grid(i,j));
		}
	}

	this->setTouchEnabled(true);

	m_removedPieces=0;
	m_dropedPieces=0;
	m_preDropPieces=0;
	srand((unsigned)time(NULL)); 

	DrawBoard();
	
	addPiece(2,5,false);
	addPiece(1,1,false);
	addPiece(4,4,false);
	addPiece(6,3,true);
	addPiece(6,2,false);
	addPiece(1,5,false);
	addPiece(0,5,false);
	addPiece(0,5,false);
	addPiece(2,5,false);
	addPiece(2,2,false);
	addPiece(2,6,false);

	mScore = Score::create();
	mScore->setPosition(ccp( VisibleRect::right().x - 60, VisibleRect::top().y - 80));
	addChild(mScore,2);


	return true; 

}
int CheckerBoard::previewDropPos(const int column)
{
	unsigned int i(0);
	while(i!=7&&(!content[column][i].IsEmpty()))
		++i;
	return i;
}

CheckerPiece* CheckerBoard::addPiece(const int column,const int num,const bool isRock)
{
	int row = previewDropPos(column);
	if (row==7)
		return 0;
	content[column][row].AddContent(num,isRock);
	int rock=isRock?2:0;
	CCSprite *sp=DrawPiece(Grid(column,row),num,rock);
	content[column][row].SetSprite(sp);
	return &content[column][row];
}

void CheckerBoard::checkColumnPiece(const int column)
{
	CheckerPiece* cp;
	unsigned int j(0),n(0);
	while(j!=7&&!content[column][j].IsEmpty())
		++j;
	while(n!=7)
	{
		cp=&content[column][n];
		if(cp->IsNum()&&j==cp->GetNum())
			removeList.push_back(cp);
		++n;
	}
}
void CheckerBoard::checkRowPiece(const int row)
{
	CheckerPiece* cp;
	unsigned int i(0),sum(0),n(0);
	while(i!=7)
	{
		if(content[i][row].IsEmpty())
		{
			while(n!=i)
			{
				cp=&content[n][row];
				if(cp->IsNum()&&sum==cp->GetNum())
					removeList.push_back(cp);
				++n;
			}
			sum=0;
		}
		else
			++sum;
		++i;
	}
	while(n!=7)
	{
		cp=&content[n][row];
		if(cp->IsNum()&&sum==cp->GetNum())
			removeList.push_back(cp);
		++n;
	}
}

void CheckerBoard::onRemovedPieces(const Grid element)
{
	breakRock(element);

	//re-arrange pieces after all the checked pieces removed.
	++m_removedPieces;	
	if (m_removedPieces==removeList.size())
	{
		m_removedPieces=0;
		unsigned int i(0);
		m_preDropPieces=0;
		while(i!=7)
		{
			arrangePieceColumn(i);
			++i;
		}
	}
}

void CheckerBoard::breakRock(const Grid element)
{

	if(element.x!=6&&content[element.x+1][element.y].IsRock())
		content[element.x+1][element.y].BreakRock();
	if(element.x!=0&&content[element.x-1][element.y].IsRock())
		content[element.x-1][element.y].BreakRock();
	if(element.y!=6&&content[element.x][element.y+1].IsRock())
		content[element.x][element.y+1].BreakRock();
	if(element.y!=0&&content[element.x][element.y-1].IsRock())
		content[element.x][element.y-1].BreakRock();
}

void CheckerBoard::onDropPieces()
{
	++m_dropedPieces;	
	if (m_dropedPieces==m_preDropPieces)
	{
		m_dropedPieces=0;
		removePieces();
	}
}



void CheckerBoard::arrangePieceColumn(const int column)
{
	unsigned int j(0),k(0);
	while(j!=7)
	{
		if(!(content[column][j].IsEmpty()))
		{
			if(j!=k)
			{
				content[column][k]=content[column][j];
				content[column][j].Drop((j-k)*VisibleRect::unit());
				++m_preDropPieces;
			}
			++k;
		}
		++j;
	}
}


void CheckerBoard::startLink(const Grid element)
{
	removeList.clear();
	mScore->resetMulti();

	checkColumnPiece(element.x);
	checkRowPiece(element.y);
	for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
	{
		(*it)->Clear();
		mScore->scoreUp();
	}
}

void CheckerBoard::removePieces()
{
	removeList.clear();
	unsigned int i(0),j(0);
	while(i!=7)
	{
		checkColumnPiece(i);
		++i;
	}
	while(j!=7)
	{
		checkRowPiece(j);
		++j;
	}
	if(!removeList.empty())
		mScore->raiseMulti();
	for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
	{
		(*it)->Clear();
		mScore->scoreUp();
	}

}

void CheckerBoard::DrawBoard()
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

CCSprite* CheckerBoard::DrawPiece(const Grid element,const int num,const int rock)
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


int CheckerBoard::containsTouchLocation(CCTouch* touch)
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

bool CheckerBoard::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_column=containsTouchLocation(pTouch);
	if (m_column>=0&&m_column<7)
	{
		m_nextNum=rand()%7+1;
		m_nextIsRock=rand()%10>8;
		int rock=m_nextIsRock?2:0;
		preview=DrawPiece(Grid(m_column,7),m_nextNum,rock);
	}
	else
		
		preview=0;
	return true;
}

void CheckerBoard::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	int column=containsTouchLocation(pTouch);

	if (column>=0&&column<7)
	{
		if (column!=m_column)
		{
			m_column=column;
			if(preview)
			{
				preview->removeFromParent();
				preview=0;
			}
			int rock=m_nextIsRock?2:0;
			preview=DrawPiece(Grid(m_column,7),m_nextNum,rock);
		}
	}
	else
	{
		m_column=-1;
		if(preview)
		{
			preview->removeFromParent();
			preview=0;
		}
	}

}
void CheckerBoard::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_column>=0)
		{
		int row = previewDropPos(m_column);
		if (row!=7)
		{
			CCActionInterval*  drop = CCMoveTo::create(0.5f, ccp( VisibleRect::origin().x+ VisibleRect::unit()*m_column+0.5* VisibleRect::unit(),  VisibleRect::origin().y+ VisibleRect::unit()*row+0.5* VisibleRect::unit()));
			CCActionInterval* move_ease_out = CCEaseOut::create((CCActionInterval*)(drop->copy()->autorelease()) , 0.5f);
			
			preview->runAction( CCSequence::create(move_ease_out,CCCallFuncN::create(this, callfuncN_selector(CheckerBoard::onPreviewDrop)),NULL));
		}
	}
}

void CheckerBoard::onPreviewDrop(CCNode* node)
{
	CheckerBoard* parent=static_cast<CheckerBoard*>(node->getParent());
	node->removeFromParent();
	node=0;

	CheckerPiece* cp=parent->addPiece(m_column,m_nextNum,m_nextIsRock);
	if(cp)
		parent->startLink(cp->GetGrid());
}


void CheckerBoard::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0, true);
}
