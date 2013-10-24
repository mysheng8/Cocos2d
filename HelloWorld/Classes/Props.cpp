#include "Props.h"
#include "CheckerPiece.h"
#include "resource.h"
#include "VisibleRect.h"

USING_NS_CC;

Prop::Prop(const CheckerGame* game,const int cost)
{
	m_game=game;
	m_cost=cost;
	m_num=5;
}

void Prop::addNum(const int k)
{
	m_num+=k;
}

void Prop::DoIt()
{
	if(m_game->m_Energy->CanRelease(m_cost)&&m_num>0)
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


bool PropLayer::init()
{
	m_max=3;
	m_Props=new Prop*[m_max];
	m_pMenu=CCMenu::create();
	m_pMenu->setPosition( CCPointZero );
	addChild(m_pMenu, 1);
	return true;
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

bool RotationProp::function()
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