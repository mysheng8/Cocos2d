#include"CheckerPiece.h"
#include"CheckerBoard.h"
#include"VisibleRect.h"

USING_NS_CC;

void CheckerPiece::SetNum(const int num)
{
	m_num=num;
	m_rock=0;
	m_sp->removeFromParent();
	m_sp=m_parent->m_parent->DrawPiece(m_grid,m_num,m_rock,false);
}


void CheckerPiece::AddContent(const int num,const bool isRock, const bool isBomb)
{
	m_num=num;
	if(isBomb)
	{
		m_type=PieceType(3);
	}
	else
	{
		if(isRock)
		{
			m_rock=2;
			m_type=PieceType(2);
		}
		else
		{
			m_type=PieceType(1);
		}
	}

}

void CheckerPiece::BreakRock()
{
	if(m_rock>0)
		--m_rock;
	if(m_rock==0)
	{
		m_type=PieceType(1);
	}
	m_sp->removeFromParent();
	m_sp=m_parent->m_parent->DrawPiece(m_grid,m_num,m_rock,false);
}

CheckerPiece& CheckerPiece::operator=(const CheckerPiece& rhs)
{
	m_type=rhs.m_type;
	m_num=rhs.m_num;
	m_rock=rhs.m_rock;
	//m_sp=m_parent->DrawPiece(m_grid,m_num,m_rock);
	m_sp=rhs.m_sp;
	jackpot_sp=rhs.jackpot_sp;
	return *this;
};
void CheckerPiece::Clear()
{
	Empty();
	CCFiniteTimeAction*  empty = CCSequence::create(
		CCScaleBy::create(0.02,2.0,2.0),
		CCScaleBy::create(0.03,0.7,0.7),
		CCScaleBy::create(0.6,0.2,0.2),
		CCCallFunc::create(this, callfunc_selector(CheckerPiece::onRemoveSprite)),
		NULL);
	CCAction*  action = CCSpawn::create(
		CCFadeOut::create(1),
		empty,
		NULL);
	m_sp->runAction(action);
};

void CheckerPiece::Explose()
{
	Empty();
	CCFiniteTimeAction*  action = CCSequence::create(
		CCTintTo::create(0.5, 255, 0, 0),
		CCFadeOut::create(0.2),
		CCCallFunc::create(this, callfunc_selector(CheckerPiece::onExplose)),
		NULL);

	m_sp->runAction(action);
}

void CheckerPiece::onExplose()
{
	m_sp->removeFromParent();

	m_parent->Explosion(m_grid);
}

void CheckerPiece::onRemoveSprite()
{
	m_sp->removeFromParent();
	if(m_parent->hasJackpot(this))
		m_parent->ApplyJackpot();
	if(IsBomb())
	{
		Explose();
	}
	else
	{
		m_parent->breakRock(m_grid);
		m_parent->onRemovedPieces();
	}
}

void CheckerPiece::Drop(const int dis)
{
	float i=dis*VisibleRect::unit();
	CCActionInterval*  move = CCMoveBy::create(0.001f, ccp(0,-i));
	CCActionInterval* move_ease_out = CCEaseOut::create((CCActionInterval*)(move->copy()->autorelease()) , 0.5f);
	m_sp->runAction( CCSequence::create(move_ease_out,CCCallFunc::create(this, callfunc_selector(CheckerPiece::onDropSprite)),NULL));
	if(m_parent->hasJackpot(this))
		jackpot_sp->runAction( CCSequence::create(move_ease_out,NULL));
//	m_sp->runAction(move_ease_out);
}

void CheckerPiece::Rise(const int dis)
{
	float i=dis*VisibleRect::unit();
	CCActionInterval*  move = CCMoveBy::create(0.001f, ccp(0,i));
	m_sp->runAction( move);
	if(m_parent->hasJackpot(this))
		jackpot_sp->runAction( move);
//	m_sp->runAction(move_ease_out);
}

void CheckerPiece::onDropSprite()
{

	//m_sp=NULL;
	m_parent->onDropPieces();
}

void CheckerPiece::initJackpot()
{
	jackpot_sp=m_parent->m_parent->DrawJackpot(m_grid);
}

void CheckerPiece::clearJackpot()
{
	jackpot_sp->removeFromParent();
}

