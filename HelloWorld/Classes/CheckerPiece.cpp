#include"CheckerPiece.h"
#include"CheckerBoard.h"

USING_NS_CC;

void CheckerPiece::AddContent(int num,bool isRock)
{
	m_num=num;
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

void CheckerPiece::BreakRock()
{
	if(m_rock>0)
		--m_rock;
	if(m_rock==0)
	{
		m_type=PieceType(1);
	}
	m_sp->removeFromParent();
	m_sp=m_parent->m_parent->DrawPiece(m_grid,m_num,m_rock);
}

CheckerPiece& CheckerPiece::operator=(const CheckerPiece& rhs)
{
	m_type=rhs.m_type;
	m_num=rhs.m_num;
	m_rock=rhs.m_rock;
	//m_sp=m_parent->DrawPiece(m_grid,m_num,m_rock);
	m_sp=rhs.m_sp;
	return *this;
};
void CheckerPiece::Clear()
{
	Empty();
	CCFiniteTimeAction*  empty = CCSequence::create(
		CCScaleBy::create(0.01,1.5,1.5),
        CCScaleBy::create(0.6,0.2,0.2),
		CCCallFunc::create(this, callfunc_selector(CheckerPiece::onRemoveSprite)),
        NULL);
	CCAction*  action = CCSpawn::create(
        CCFadeOut::create(1),
        empty,
        NULL);
	m_sp->runAction(action);
};

void CheckerPiece::onRemoveSprite()
{
	m_sp->removeFromParent();
	m_parent->onRemovedPieces(m_grid);
}

void CheckerPiece::Drop(float dis)
{
	CCActionInterval*  move = CCMoveBy::create(0.001f, ccp(0,-dis));
	CCActionInterval* move_ease_out = CCEaseOut::create((CCActionInterval*)(move->copy()->autorelease()) , 0.5f);
	m_sp->runAction( CCSequence::create(move_ease_out,CCCallFunc::create(this, callfunc_selector(CheckerPiece::onDropSprite)),NULL));
//	m_sp->runAction(move_ease_out);
}

void CheckerPiece::Rise(float dis)
{
	CCActionInterval*  move = CCMoveBy::create(0.001f, ccp(0,dis));
	m_sp->runAction( move);
//	m_sp->runAction(move_ease_out);
}

void CheckerPiece::onDropSprite()
{
	//m_sp=NULL;
	m_parent->onDropPieces();
}

