#include "resource.h"
#include "VisibleRect.h"
#include "CheckerBoard.h"
#include <algorithm>

USING_NS_CC;

CheckerBoard::CheckerBoard(CheckerGame *parent)
{
	m_parent	=	parent;

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

	m_removedPieces		=	0;
	m_dropedPieces		=	0;
	m_preDropPieces		=	0;





#ifdef DEBUGVIEW
	DebugView();
#endif
}
int CheckerBoard::getHeight(const int column)
{
	unsigned int i(0);
	while(i!=7&&(!content[column][i].IsEmpty()))
		++i;
	return i;
}

CheckerPiece* CheckerBoard::addPiece(const int column,const int num,const bool isRock)
{
	int row = getHeight(column);
	if (row==7)
		return 0;
	content[column][row].AddContent(num,isRock);
	int rock=isRock?2:0;
	CCSprite *sp=m_parent->DrawPiece(Grid(column,row),num,rock);
	content[column][row].SetSprite(sp);
	return &content[column][row];
}

void CheckerBoard::checkColumnPiece(const int column)
{
	bool hasRemoved(false);
	CheckerPiece* cp;
	unsigned int j(0),n(0);
	while(j!=7&&!content[column][j].IsEmpty())
		++j;
	while(n!=7)
	{
		cp=&content[column][n];
		if(cp->IsNum()&&j == cp->GetNum())
		{
			vector<CheckerPiece*>::size_type wc =count(removeList.begin(), removeList.end(), cp); 
			if(!wc)
				removeList.push_back(cp);
			hasRemoved=true;
		}
		++n;
	}
	if(hasRemoved)
		m_parent->DrawGuide(Grid(column,0),Grid(column,j-1));
}
void CheckerBoard::checkRowPiece(const int row)
{
	bool hasRemoved(false);
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
				{
					vector<CheckerPiece*>::size_type wc =count(removeList.begin(), removeList.end(), cp); 
					if(!wc)
					{
						removeList.push_back(cp);
					}
					hasRemoved=true;
				}
				++n;
			}
			if(hasRemoved)
			{
				m_parent->DrawGuide(Grid(i-sum,row),Grid(i-1,row));
				hasRemoved=false;
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
		{
			vector<CheckerPiece*>::size_type wc =count(removeList.begin(), removeList.end(), cp); 
			if(!wc)
			{
				removeList.push_back(cp);
				char string[20] = {0};
				sprintf(string, "remove column:%d", n);
				CCLog(string);
			}
			hasRemoved=true;
		}
		++n;
	}
	if(hasRemoved)
		m_parent->DrawGuide(Grid(7-sum,row),Grid(6,row));
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
		if (m_preDropPieces==0)
			removePieces();
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

bool CheckerBoard::levelUp()
{
	for(unsigned int i=0;i!=7;++i)
	{
		int j = 6;
		if (!content[i][j].IsEmpty())
			return false;
		while(j!=0)
		{
			if(!content[i][j-1].IsEmpty())
			{
				content[i][j]=content[i][j-1];
				content[i][j].Rise(VisibleRect::unit());
			}
			int t2=content[i][j].GetNum();
			--j;
		}
		int num=rand()%7+1;
		content[i][0].AddContent(num,true);
		CCSprite *sp=m_parent->DrawPiece(Grid(i,0),num,2);
		content[i][0].SetSprite(sp);
	}
	return true;
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
				content[column][j].Empty();
				++m_preDropPieces;
			}
			++k;
		}
		++j;
	}
#ifdef DEBUGVIEW
	DebugView();
#endif
}
bool Comp(const CheckerPiece* a, const CheckerPiece* b)
{
	return a > b ;
}

void CheckerBoard::startLink(const Grid element)
{
	removeList.clear();
	m_parent->mScore->resetMulti();

	
	checkRowPiece(element.y);
	checkColumnPiece(element.x);
	if(removeList.empty())
		m_parent->endLink();
	else
	{
		for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
		{
			(*it)->Clear();
			m_parent->mScore->scoreUp();
		}
	}
#ifdef DEBUGVIEW
	DebugView();
#endif
}

void CheckerBoard::removePieces()
{
	removeList.clear();
	unsigned int i(0),j(0);

	while(j!=7)
	{
		checkRowPiece(j);
		++j;
	}
	while(i!=7)
	{
		checkColumnPiece(i);
		++i;
	}
	if(!removeList.empty())
	{
		m_parent->mScore->raiseMulti();
		for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
		{
			(*it)->Clear();
			m_parent->mScore->scoreUp();
		}
	}
	else
		m_parent->endLink();
#ifdef DEBUGVIEW
	DebugView();
#endif
}



#ifdef DEBUGVIEW
void CheckerBoard::DebugView()
{
	for (int i=0;i!=7;++i)
	{
		for(int j=0;j!=7;++j)
		{
			int num=content[i][j].GetNum();
			int rock=content[i][j].GetRock();
			int type=content[i][j].GetType();
			char string[30] = {0};
			sprintf(string, "num:%d\r\nrock:%d\r\ntype:%d", num, rock,type);
			CCLabelTTF* label = CCLabelTTF::create(string, "Marker Felt",9); 
			label->setColor(ccc3(0,0,0));
			label->setPosition(ccp(VisibleRect::unit()*i+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*j+0.5*VisibleRect::unit() +VisibleRect::origin().y));
			m_parent->addChild(label,100);
			
			if((7*i+j)<Debuglabels.size()&&Debuglabels[7*i+j])
			{
				Debuglabels[7*i+j]->removeFromParent();
				Debuglabels[7*i+j]=label;
			}
			else
				Debuglabels.push_back(label);
		}
	}
}
#endif