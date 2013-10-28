#include "CheckerPreview.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"
#include "resource.h"

USING_NS_CC;
using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#else
const char s_pClick[] = "audio/click.wav";
#endif


CheckerPreview::CheckerPreview(CheckerGame *parent)
{
	m_Num		=	-1;
	m_IsRock	=	false;
	m_column	=	0;
	needReset	=	false;
	m_parent	=	parent;
	isBomb		=	false;
	SimpleAudioEngine::sharedEngine()->preloadEffect( s_pClick );
}

void CheckerPreview::resetPreview(int num,bool isRock)
{
	m_Num=num;
	m_IsRock=isRock;
	int rock=m_IsRock?2:0;
	m_sp=m_parent->DrawPiece(Grid(m_column,7),m_Num,rock);
	needReset	=	false;
	isBomb		=	false;
}

void CheckerPreview::movePreview(int column)
{
	if(column!=m_column)
	{
		CCActionInterval*  move = CCMoveBy::create(0.1f, ccp( VisibleRect::unit()*(column-m_column),  0));
		CCActionInterval*  move_ease_in = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()) , 0.5f);
		m_sp->runAction(move_ease_in);
		m_column=column;
		
	}
}

void CheckerPreview::BombMode()
{
	if(m_sp)
	{
		m_sp->removeFromParent();
		m_sp= CCSprite::create(s_pPathPiece,CCRectMake(9*40,0,40,40));
		m_sp->setScale(0.99f);
		m_sp->setPosition(ccp(VisibleRect::unit()*m_column+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*7+0.5*VisibleRect::unit() +VisibleRect::origin().y));
		m_parent->addChild(m_sp,10);
	}
	isBomb=true;
}

void CheckerPreview::StartPreview(int column)
{
	movePreview(column);
}

void CheckerPreview::EditPreview(int column)
{
	movePreview(column);
}

void CheckerPreview::EndPreview(int column)
{
	movePreview(column);
	if(column>=0&&column<7)
	{
		int row = m_parent->m_content->getHeight(column);
		if (row!=7)
		{
			CCActionInterval*  drop = CCMoveTo::create(sqrt((7-row)/20.0f), ccp( VisibleRect::origin().x+ VisibleRect::unit()*m_column+0.5* VisibleRect::unit(),  VisibleRect::origin().y+ VisibleRect::unit()*row+0.5* VisibleRect::unit()));
			CCActionInterval* move_ease_out = CCEaseOut::create((CCActionInterval*)(drop->copy()->autorelease()) , 0.5f);
			m_sp->runAction( CCSequence::create(move_ease_out,CCCallFuncN::create(this, callfuncN_selector(CheckerPreview::onPreviewDrop)),NULL));
			needReset	=	true;
		}
	}
}

void CheckerPreview::onPreviewDrop(CCNode* node)
{
	m_sp->removeFromParent();
	SimpleAudioEngine::sharedEngine()->playEffect(s_pClick);
	if(isBomb)
		m_parent->explose(m_column);
	else
		m_parent->startLink(m_column);
}