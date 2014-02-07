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


CheckerPreview::CheckerPreview(GameLayer *parent)
{
	data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	m_column	=	0;
	needReset	=	false;
	m_parent	=	parent;
	isBomb		=	false;
	isRandom	=	false;
	SimpleAudioEngine::sharedEngine()->preloadEffect( s_pClick );
}

void CheckerPreview::resetPreview()
{
	int rock=data->m_nextIsRock?2:0;
	m_sp=m_parent->DrawPiece(Grid(m_column,7),data->m_nextNum,rock,false);
	needReset	=	false;
	isBomb		=	false;
	isRandom	=	false;
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
		m_sp=CCSprite::create(s_pPathPiece,CCRectMake(9*40,0,40,40));
		m_sp->setScale(0.99f);
		m_sp->setPosition(ccp(VisibleRect::unit()*m_column+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*7+0.5*VisibleRect::unit() +VisibleRect::origin().y));
		m_parent->addChild(m_sp,10);
	}
	isBomb=true;
}

void CheckerPreview::RandomMode()
{
	if(m_sp)
	{
		m_sp->removeFromParent();
		m_sp = CCSprite::createWithSpriteFrame(CCSpriteFrame::create(s_pPathPiece,CCRectMake(0*40,0,40,40)));
		CCArray* animFrames = CCArray::createWithCapacity(10);
		for(unsigned int i=0;i!=8;++i)
		{
			CCSpriteFrame *frame = CCSpriteFrame::create(s_pPathPiece,CCRectMake(i*40,0,40,40));
			animFrames->addObject(frame);
		}
		//m_sp->setScale(0.99f);
		CCAnimation *anim = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
		m_sp->runAction(CCRepeatForever::create( CCAnimate::create(anim) ) );
		m_sp->setPosition(ccp(VisibleRect::unit()*m_column+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*7+0.5*VisibleRect::unit() +VisibleRect::origin().y));
		m_parent->addChild(m_sp,10);
	}
	isRandom=true;
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
	if(isRandom)
	{
		CCRect ret=m_sp->getTextureRect();
		int k=ret.origin.x/40;
		//CCLog("%d",k);
		if(k!=7)
		{
			data->m_nextNum=k+1;
			data->m_nextIsRock=false;
		}
		else
			data->m_nextIsRock=true;
		m_sp->removeFromParent();
		m_sp=CCSprite::create(s_pPathPiece,CCRectMake(k*40,0,40,40));

		m_sp->setPosition(ccp(VisibleRect::unit()*m_column+0.5*VisibleRect::unit()+VisibleRect::origin().x, VisibleRect::unit()*7+0.5*VisibleRect::unit() +VisibleRect::origin().y));
		m_parent->addChild(m_sp,10);
	}
	if(column>=0&&column<7)
	{
		int row = m_parent->GetContent()->getHeight(column);
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
	m_parent->startLink(m_column,isBomb);
}