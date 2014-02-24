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



CheckerBoard::CheckerBoard(GameLayer *parent)
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

	jackpot_p = 0;

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

CheckerPiece* CheckerBoard::addPiece(const int column,const int num,const bool isRock, const bool isBomb)
{
	int row = getHeight(column);
	if (row==7)
		return 0;
	content[column][row].AddContent(num,isRock,isBomb);
	int rock=isRock?2:0;
	CCSprite *sp=m_parent->DrawPiece(Grid(column,row),num,rock,isBomb);
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

void CheckerBoard::onRemovedPieces()
{
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
				if(hasJackpot(&content[i][j-1]))
					jackpot_p=&content[i][j];
				content[i][j].Rise(1);

			}
			--j;
		}
		int num=rand()%7+1;
		content[i][0].AddContent(num,true,false);
		CCSprite *sp=m_parent->DrawPiece(Grid(i,0),num,2,false);
		content[i][0].SetSprite(sp);
	}
	return true;
}

bool CheckerBoard::Decline()
{
	for(unsigned int i=0;i!=7;++i)
	{
		int j = 0;
		if(content[i][j].IsEmpty())
			continue;
		content[i][j].clearSprite();
		content[i][j].Empty();
		while(j!=7)
		{
			if(!content[i][j+1].IsEmpty())
			{
				content[i][j]=content[i][j+1];
				content[i][j].Rise(-1);
				content[i][j+1].Empty();
			}
			++j;
		}
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
				if(hasJackpot(&content[column][j]))
					jackpot_p=&content[column][k];
				content[column][j].Drop((j-k));
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

void CheckerBoard::startLink(const Grid element,const bool isBomb)
{
	removeList.clear();

	if(isBomb)
		content[element.x][element.y].Explose();
	else{
		m_parent->ResetMulti();

		checkRowPiece(element.y);
		checkColumnPiece(element.x);

		if(removeList.empty())
			m_parent->endLink();
		else
		{
			for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
			{
				(*it)->Clear();
				m_parent->ScoreUp();
			}
			SimpleAudioEngine::sharedEngine()->playEffect(s_pRemove);
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
		m_parent->ScoreRiseMulti();
		for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
		{
			(*it)->Clear();
			m_parent->ScoreUp();
			m_parent->EnergyCharge();
			SimpleAudioEngine::sharedEngine()->playEffect(effect[(*it)->GetNum()-1].c_str());
		}
		int e_id=m_parent->GetMulti()*2;
		SimpleAudioEngine::sharedEngine()->playEffect(effect[e_id].c_str());
	}
	else
		m_parent->endLink();
#ifdef DEBUGVIEW
	DebugView();
#endif
}

void CheckerBoard::KillPieces(vector<Grid>::iterator begin, vector<Grid>::iterator end)
{
	for(vector<Grid>::iterator it=begin;it!=end;++it)
	{
		CheckerPiece *cp=getCheckerPiece(*it);
		if(!cp->IsEmpty())
			removeList.push_back(cp);
	}
	if(!removeList.empty())
	{
		for(vector<CheckerPiece*>::iterator it=removeList.begin();it!=removeList.end();++it)
		{
			(*it)->Clear();
			SimpleAudioEngine::sharedEngine()->playEffect(effect[(*it)->GetNum()-1].c_str());
		}
	}

}

void CheckerBoard::Explosion(const Grid element)
{
	
	//++m_removedPieces;//count +1 for bomb piece removed

	unsigned int left=(element.x-1<0)?0:(element.x-1);
	unsigned int right=(element.x+1>6)?6:(element.x+1);
	unsigned int bottom=(element.y-1<0)?0:(element.y-1);
	unsigned int top=(element.y+1>6)?6:(element.y+1);
	vector<Grid> list;
	for(unsigned int i=left;i!=right+1;++i)
	{
		for(unsigned int j=bottom;j!=top+1;++j)
		{
			list.push_back(Grid(i,j));
		}
	}
	KillPieces(list.begin(),list.end());
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

CheckerPiece* CheckerBoard::InsertPiece(const Grid element, const int num, const bool isRock, const bool isBomb)
{
	CheckerPiece *piece = &content[element.x][element.y];
	piece->AddContent(num,isRock,isBomb);
	int rock = isRock?2:0;
	CCSprite *sp=m_parent->DrawPiece(element,num,rock,isBomb);
	piece->SetSprite(sp);
	return piece;
}

void CheckerBoard::initJackpot()
{
	int num = 0;
	int col = 0;
	int row = 0;
	while(num==0)
	{
		col=rand()%7;
		num=getHeight(col);
	}
	row=rand()%num;
	content[col][row].initJackpot();

	jackpot_p=&content[col][row];
}

void CheckerBoard::setJackpot()
{
	GameData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	JackpotRuntimeData *jdata=data->m_jackpotRuntime;

	if(!jdata->hasJackpot)
	{
		if(jdata->m_appear==0)
		{
			initJackpot();
			jdata->m_appear=jdata->m_minAppear;
			jdata->hasJackpot=true;
			
		}
		else
			--jdata->m_appear;
	
	}
	else
	{
		if(jdata->m_disappear==0)
		{
			clearJackpot();
			jdata->m_disappear=jdata->m_minDisappear;
			jdata->hasJackpot=false;
		}
		else
			--jdata->m_disappear;	
	
	}
}

void CheckerBoard::ApplyJackpot()
{
	GameData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	if(data->m_jackpotRuntime->hasJackpot)
	{
		Jackpot *j=static_cast<Jackpot*>(JackpotFactory::sharedClassFactory().GetJackpotByName(data->m_jackpotRuntime->m_jackpot->m_name));
		j->setGrid(&(jackpot_p->GetGrid()));
		j->function();
		GameScene::sharedGameScene().randomJackpot();
		//clear jackpot
		clearJackpot();
	}
}

void CheckerBoard::clearJackpot()
{
	if(jackpot_p)
	{
		jackpot_p->clearJackpot();
		jackpot_p=0;
	}
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