
#include <stdio.h> 
#include <time.h> 

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

	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	m_delta=(winSize.width<winSize.height?winSize.width:winSize.height)/9.0;
	m_origin=CCPoint( origin.x+winSize.width/2-3.5*m_delta, origin.y+winSize.height/2-4*m_delta);



	srand((unsigned)time(NULL)); 

	DrawBoard();
	/*
	addPiece(2,3,false);
	addPiece(1,1,false);
	addPiece(4,4,false);
	addPiece(6,3,true);
	addPiece(6,2,false);
	addPiece(1,5,false);
	addPiece(0,5,false);
	*/
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

void  CheckerBoard::checkPiece(const Grid element)
{
	removeList.clear();
	CheckerPiece* cp;
	unsigned int i(0),sum(0),n(0);
	while(i!=7)
	{
		if(content[i][element.y].IsEmpty())
		{
			while(n!=i)
			{
				cp=&content[n][element.y];
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
		cp=&content[n][element.y];
		if(cp->IsNum()&&sum==cp->GetNum())
			removeList.push_back(cp);
		++n;
	}
	
	unsigned int j=0;
	while(j!=7&&!content[element.x][j].IsEmpty())
		++j;
	n=0;
	while(n!=7)
	{
		cp=&content[element.x][n];
		if(cp->IsNum()&&j==cp->GetNum())
			removeList.push_back(cp);
		++n;
	}
	
}


void CheckerBoard::reorginizePiece()
{
	unsigned int i(0);
	while(i!=7)
	{
		unsigned int j(0),k(0);
		while(j!=7)
		{
			if(!content[i][j].IsEmpty())
			{
				if(j!=k)
				{
					content[i][k]=content[i][j];
					content[i][j].Clear();
				}
				++k;
			}
			++j;
		}
		++i;
	}
}

void CheckerBoard::removePiece(const Grid element)
{
	checkPiece(element);
	for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
	{
		(*it)->Clear();
	}
	reorginizePiece();
}

void CheckerBoard::DrawBoard()
{
	for ( int i=0;i!=8;++i)
	{
		for ( int j=0;j!=8;++j)
		{
			CCSprite* pSprite = CCSprite::create("anchor.png");
			pSprite->setPosition(ccp(m_delta*i+m_origin.x, m_delta*j+m_origin.y));
			this->addChild(pSprite, 0);
		}
	
	}

}

CCSprite* CheckerBoard::DrawPiece(const Grid element,const int num,const int rock)
{
		int n=0;
		if(rock!=0)
			n=9-rock;
		else
			n=num-1;
		CCSprite* pSprite = CCSprite::create("piece.png",CCRectMake(n*34,0,34,34));
		pSprite->setPosition(ccp(m_delta*element.x+0.5*m_delta+m_origin.x, m_delta*element.y+0.5*m_delta +m_origin.y));
		this->addChild(pSprite, 0);
		return pSprite;
}


int CheckerBoard::containsTouchLocation(CCTouch* touch)
{
	for ( int i=0;i!=7;++i)
	{
		CCRect rect=CCRectMake(m_delta*i+m_origin.x, m_origin.y, m_delta, m_delta*7);
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
			CCActionInterval*  drop = CCMoveTo::create(0.5f, ccp(m_origin.x+m_delta*m_column+0.5*m_delta, m_origin.y+m_delta*row+0.5*m_delta));
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
		parent->removePiece(cp->GetGrid());
}


void CheckerBoard::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0, true);
}
