#include "resource.h"
#include "VisibleRect.h"
#include "CheckerBoard.h"
#include <algorithm>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	const std::string effect[] = {
		"audio/1.ogg",
		"audio/2.ogg",
		"audio/3.ogg",
		"audio/4.ogg",
		"audio/5.ogg",
		"audio/6.ogg",
		"audio/7.ogg"

	};
#else
	const std::string effect[] = {
		"audio/1.wav",
		"audio/2.wav",
		"audio/3.wav",
		"audio/4.wav",
		"audio/5.wav",
		"audio/6.wav",
		"audio/7.wav",
		"audio/8.wav",
		"audio/9.wav",
		"audio/10.wav",
		"audio/11.wav",
		"audio/12.wav",
		"audio/13.wav",
		"audio/14.wav",
		"audio/15.wav",
		"audio/16.wav",
		"audio/17.wav",
		"audio/18.wav",
		"audio/19.wav",
	};

	const char s_pRemove[] = "audio/remove.wav";
	const char s_pBreak[] = "audio/break.wav";
#endif



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

	for(int j=0;j!=18;++j)
		SimpleAudioEngine::sharedEngine()->preloadEffect( effect[j].c_str() );
	SimpleAudioEngine::sharedEngine()->preloadEffect(s_pRemove);
	SimpleAudioEngine::sharedEngine()->preloadEffect(s_pBreak);
#ifdef DEBUGVIEW
	DebugView();
#endif
}



CheckerBoard::~CheckerBoard()
{
	SimpleAudioEngine::sharedEngine()->end();
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

CheckerPiece* CheckerBoard::getCheckerPiece(const Grid element)
{
	return &content[element.x][element.y];
}

CheckerPiece* CheckerBoard::getCheckerPiece(const int column,const int row)
{
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
			{
				removeList.push_back(cp);
				removeGrid.push_back(cp->GetGrid());
			}
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
						removeGrid.push_back(cp->GetGrid());
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
				removeGrid.push_back(cp->GetGrid());
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
	bool play(false);
	if(element.x!=6&&content[element.x+1][element.y].IsRock())
	{
		content[element.x+1][element.y].BreakRock();
		play=true;
	}
	if(element.x!=0&&content[element.x-1][element.y].IsRock())
	{
		content[element.x-1][element.y].BreakRock();
		play=true;
	}
	if(element.y!=6&&content[element.x][element.y+1].IsRock())
	{
		content[element.x][element.y+1].BreakRock();
		play=true;
	}
	if(element.y!=0&&content[element.x][element.y-1].IsRock())
	{
		content[element.x][element.y-1].BreakRock();
		play=true;
	}
	if(play)
		SimpleAudioEngine::sharedEngine()->playEffect(s_pBreak);
}

bool CheckerBoard::riseUp()
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
			m_parent->mScore->score();
		}
		SimpleAudioEngine::sharedEngine()->playEffect(s_pRemove);
	}
#ifdef DEBUGVIEW
	DebugView();
#endif
}

void CheckerBoard::removePieces()
{
	removeList.clear();
	unsigned int i(0),j(0);

	removeGrid.clear();
	while(j!=7)
	{
		checkRowPiece(j);
		++j;
	}
	if(!removeGrid.empty())
		DrawLink(true);

	removeGrid.clear();
	while(i!=7)
	{
		checkColumnPiece(i);
		++i;
	}
	if(!removeGrid.empty())
		DrawLink(true);
	if(!removeList.empty())
	{
		m_parent->mScore->raiseMulti();
		for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
		{
			(*it)->Clear();
			m_parent->mScore->score();
			m_parent->m_Energy->Charge(m_parent->mScore->getMulti());
			SimpleAudioEngine::sharedEngine()->playEffect(effect[(*it)->GetNum()-1].c_str());
		}
		int e_id=m_parent->mScore->getMulti()*2;
		SimpleAudioEngine::sharedEngine()->playEffect(effect[e_id].c_str());
	}
	else
		m_parent->endLink();
#ifdef DEBUGVIEW
	DebugView();
#endif
}

void CheckerBoard::DrawLink(bool horizontal)
{
	const unsigned int n = removeGrid.size();
	Grid *r_grid = new Grid[n];
	for(unsigned int i = 0;i!=n;++i)
	{
		r_grid[i]=removeGrid[i];
	}
	m_parent->DrawLink(r_grid, n,horizontal);
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