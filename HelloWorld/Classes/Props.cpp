#include "Props.h"
#include "CheckerPiece.h"
#include "resource.h"
#include <stdio.h>
#include <stack>
using namespace std;

USING_NS_CC;

void* PropFactory::GetPropByName(string propName)
{
	map<string,createProp>::const_iterator iter;

	iter=m_propMap.find(propName);
	if(iter==m_propMap.end())
		return NULL;
	else
		return iter->second();
}

void PropFactory::registProp(string name,createProp method)
{
	m_propMap.insert(pair<string,createProp>(name,method));
}

PropFactory& PropFactory::sharedClassFactory()
{
	static PropFactory _sharedClassFactory;
	return _sharedClassFactory;
}

IMPLEMENT_PROP(Prop)
Prop::Prop()
{
	//init( 0,0);
	if(GameScene::sharedGameScene().gameLayer)
	{
		m_game=GameScene::sharedGameScene().gameLayer;
	}
	//m_game=0;
}


RockBreakProp::RockBreakProp()
{
	
}

IMPLEMENT_PROP(RockBreakProp)

bool RockBreakProp::function()
{
	if (!m_game)
		return false;
	for(unsigned int i=0;i!=7;++i)
	{
		for(unsigned int j=0;j!=7;++j)
		{
			CheckerPiece* cp = m_game->GetCheckerPiece(i,j);
			if(cp->IsRock())
			{
				cp->BreakRock();
			}
		}
	}
	return true;
}

UpperProp::UpperProp()
{
}

IMPLEMENT_PROP(UpperProp)
bool UpperProp::function()
{
	if (!m_game)
		return false;
	for(unsigned int i=0;i!=7;++i)
	{
		for(unsigned int j=0;j!=7;++j)
		{
			CheckerPiece* cp = m_game->GetCheckerPiece(i,j);
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

AddScoreProp::AddScoreProp()
{
	
}

IMPLEMENT_PROP(AddScoreProp)
bool AddScoreProp::function()
{
	if (!m_game)
		return false;
	m_game->PropUp();
	return true;
}

EnergyUpProp::EnergyUpProp()
{
	
}

IMPLEMENT_PROP(EnergyUpProp)
bool EnergyUpProp::function()
{
	if (!m_game)
		return false;
	m_game->EnergyUp();
	return true;
}

LevelDownProp::LevelDownProp()
{
	
}

IMPLEMENT_PROP(LevelDownProp)
bool LevelDownProp::function()
{
	if (!m_game)
		return false;
	m_game->GetContent()->Decline();
	return true;
}

KillProp::KillProp()
{
	
}

IMPLEMENT_PROP(KillProp)
bool KillProp::function()
{
	if (!m_game)
		return false;
	m_game->ToggleKillMode();
	return true;
}

PrimeProp::PrimeProp()
{
	
}

IMPLEMENT_PROP(PrimeProp)
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
			CheckerPiece *cp=m_game->GetCheckerPiece(j,i);
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
					
					m_game->GetContent()->KillPieces(list.begin(),list.end());
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
					
			m_game->GetContent()->KillPieces(list.begin(),list.end());
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

BombProp::BombProp()
{
	
}

IMPLEMENT_PROP(BombProp)
bool BombProp::function()
{
	if (!m_game)
		return false;
	m_game->BombMode();
	return true;
}

RandomProp::RandomProp()
{
	
}

IMPLEMENT_PROP(RandomProp)
bool RandomProp::function()
{
	if (!m_game)
		return false;
	m_game->RandomMode();
	return true;
}