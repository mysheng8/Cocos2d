#include "Props.h"
#include "CheckerPiece.h"
#include "resource.h"
#include "VisibleRect.h"
#include <stdio.h>
#include <stack>
using namespace std;

USING_NS_CC;

Prop::Prop( CheckerGame* game,const int cost)
{
	m_game=game;
	m_cost=cost;
	m_num=100;
}

void Prop::addNum(const int k)
{
	m_num+=k;
}

void Prop::DoIt()
{
	if(m_game->m_Energy->CanRelease(m_cost)&&m_num>0&&m_game->CanUseProp())
	{
		if (function())
		{
			m_game->m_Energy->Release(m_cost);
			--m_num;
		}
	}
}

PropSprite::PropSprite(const char *normalImage, const char *selectedImage, const char *disabledImage,Prop *prop)
{
	initWithNormalImage(normalImage,selectedImage,disabledImage,this,menu_selector(PropSprite::ClickCallback) );
	m_Prop=prop;
}


bool PropLayer::initWithParent(CheckerGame *game)
{
	if(!CCLayer::init())
		return false;
	m_game=game;
	m_max=3;
	m_Props=new Prop*[m_max];
	m_pMenu=CCMenu::create();
	m_pMenu->setPosition( CCPointZero );
	addChild(m_pMenu, 1);
	return true;
}
PropLayer* PropLayer::create(CheckerGame *game)
{
	PropLayer *pl=new PropLayer();
	pl->initWithParent(game);
	return pl;
}
void PropLayer::AddProp(const int cur, Prop *prop)
{
	if(cur<m_max)
	{
		m_Props[cur]=prop;
	}
	else
		CCLog("failed to add more props ");
}

void PropLayer::DisplayProp(const char *normalImage, const char *selectedImage, const char *disabledImage,const int cur,Prop *prop)
{
	PropSprite *sp_Prop = new PropSprite(normalImage, selectedImage, disabledImage,prop);
	m_pMenu->addChild(sp_Prop);
	sp_Prop->setPosition(ccp( (VisibleRect::propOrigin().x + cur*VisibleRect::propUnit().x), VisibleRect::propOrigin().y));
}

bool RockBreakProp::function()
{
	if (!m_game)
		return false;
	for(unsigned int i=0;i!=7;++i)
	{
		for(unsigned int j=0;j!=7;++j)
		{
			CheckerPiece* cp = m_game->m_content->getCheckerPiece(i,j);
			if(cp->IsRock())
			{
				cp->BreakRock();
			}
		}
	}
	return true;
}

bool UpperProp::function()
{
	if (!m_game)
		return false;
	for(unsigned int i=0;i!=7;++i)
	{
		for(unsigned int j=0;j!=7;++j)
		{
			CheckerPiece* cp = m_game->m_content->getCheckerPiece(i,j);
			if(cp->IsNum())
			{
				int n=cp->GetNum();
				if (n<7)
					cp->SetNum(n+1);
			}
		}
	}
	return true;
}

bool AddScoreProp::function()
{
	if (!m_game)
		return false;
	m_game->mScore->PropUp(2000);
	return true;
}

bool EnergyUpProp::function()
{
	if (!m_game)
		return false;
	int base=m_game->m_Energy->GetBase();
	m_game->m_Energy->SetBase(1.2*base);
	return true;
}

bool LevelDownProp::function()
{
	if (!m_game)
		return false;
	m_game->m_content->Decline();
	return true;
}

bool KillProp::function()
{
	if (!m_game)
		return false;
	m_game->toggleKillMode();
	return true;
}

bool PrimeProp::function()
{
	if (!m_game)
		return false;
	typedef pair<int,int> KV;
	stack<KV> nums;
	vector<Grid> list;
	for(unsigned int i=0;i!=7;++i)
	{
		for(unsigned int j=0;j!=7;++j)
		{
			CheckerPiece *cp=m_game->m_content->getCheckerPiece(j,i);
			if(cp->IsNum())
				nums.push(KV(cp->GetNum(),j));
			else
			{
				if(nums.empty())
					continue;
				int k=0;
				int	sum=0;
				while(!nums.empty())
				{
					sum+=((int)pow(10.,k))*nums.top().first;
					list.push_back(Grid(nums.top().second,i));
					nums.pop();
					++k;
				}
				char string1[15] = {0};
				sprintf(string1, "justify %d", sum);
				CCLog(string1);
				if(IsPrime(sum))
				{
					char string2[15] = {0};
					sprintf(string2, "%d is prime", sum);
					CCLog(string2);
					
					m_game->m_content->KillPieces(list.begin(),list.end());
				}
				list.clear();
			}
		}
		if(nums.empty())
			continue;
		int k=0;
		int	sum=0;
		while(!nums.empty())
		{
			sum+=((int)pow(10.,k))*nums.top().first;
			list.push_back(Grid(nums.top().second,i));
			nums.pop();
			++k;
		}
		char string1[20] = {0};
		sprintf(string1, "justify %d", sum);
		CCLog(string1);
		if(IsPrime(sum))
		{
			char string2[20] = {0};
			sprintf(string2, "%d is prime", sum);
			CCLog(string2);
					
			m_game->m_content->KillPieces(list.begin(),list.end());
		}
		list.clear();
	}
	return true;
}

bool PrimeProp::IsPrime(const int num)
{
	int q=floor(sqrt((float)num));
	for(unsigned int i=2;i<=q;++i)
	{
		if(num%i==0)return false;
	}
	return true;
}

bool BombProp::function()
{
	if (!m_game)
		return false;
	m_game->m_preview->BombMode();
	return true;
}

bool RandomProp::function()
{
	if (!m_game)
		return false;
	return true;
}