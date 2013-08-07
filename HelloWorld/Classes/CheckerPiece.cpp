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
		m_type=PieceType(1);
}

CheckerPiece& CheckerPiece::operator=(const CheckerPiece& rhs)
{
	m_type=rhs.m_type;
	m_num=rhs.m_num;
	m_rock=rhs.m_rock;
	m_sp=m_parent->DrawPiece(m_grid,m_num,m_rock);
	return *this;
};
void CheckerPiece::Clear()
{
	m_type=PieceType(0);
	CCActionInterval*  fadeIn = CCFadeOut::create(1.0f);
	m_sp->runAction(CCSequence::create(fadeIn,CCCallFuncN::create(this, callfuncN_selector(CheckerPiece::onRemoveSprite)),NULL));
};

void CheckerPiece::onRemoveSprite(CCNode* node)
{
	node->removeFromParent();
}