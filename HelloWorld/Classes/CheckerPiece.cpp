#include"CheckerPiece.h"
#include"CheckerBoard.h"
#include<stdexcept>
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
		m_type=PieceType(1);
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
	m_type=PieceType(0);
	CCActionInterval*  fadeOut = CCFadeOut::create(1.0f);
	m_sp->runAction(CCSequence::create(fadeOut,CCCallFunc::create(this, callfunc_selector(CheckerPiece::onRemoveSprite)),NULL));
};

void CheckerPiece::onRemoveSprite()
{
	m_sp->removeFromParent();
	m_parent->onRemovedPieces();
}

void CheckerPiece::Drop(float dis)
{
	m_type=PieceType(0);
	CCActionInterval*  drop = CCMoveBy::create(0.001f*dis, ccp(0,-dis));
	CCActionInterval* move_ease_out = CCEaseOut::create((CCActionInterval*)(drop->copy()->autorelease()) , 0.5f);
	m_sp->runAction( CCSequence::create(move_ease_out,CCCallFunc::create(this, callfunc_selector(CheckerPiece::onDropSprite)),NULL));
//	m_sp->runAction(move_ease_out);

	
}
void CheckerPiece::onDropSprite()
{
	//m_sp=NULL;
	m_parent->onDropPieces();
}
