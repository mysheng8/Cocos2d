#include "CheckerPreview.h"
#include "VisibleRect.h"
USING_NS_CC;

void CheckerPreview::StartPreview(int column)
{
	if (column>=0&&column<7)
	{
		int rock=m_IsRock?2:0;
		m_sp=m_parent->DrawPiece(Grid(column,7),m_Num,rock);
		m_column=column;
	}
	else
		m_sp=0;

}

void CheckerPreview::EditPreview(int column)
{
	if (column>=0&&column<7)
	{
		if (column!=m_column)
		{
			m_column=column;
			if(m_sp)
			{
				m_sp->removeFromParent();
				m_sp=0;
			}
			int rock=m_IsRock?2:0;
			m_sp=m_parent->DrawPiece(Grid(m_column,7),m_Num,rock);
		}
	}
	else
	{
		m_column=-1;
		if(m_sp)
		{
			m_sp->removeFromParent();
			m_sp=0;
		}
	}
}

void CheckerPreview::EndPreview(int column)
{
	if (column>=0)
		{
		int row = m_parent->m_content->getHeight(column);
		if (row!=7)
		{
			CCActionInterval*  drop = CCMoveTo::create(sqrt((7-row)/20.0f), ccp( VisibleRect::origin().x+ VisibleRect::unit()*m_column+0.5* VisibleRect::unit(),  VisibleRect::origin().y+ VisibleRect::unit()*row+0.5* VisibleRect::unit()));
			CCActionInterval* move_ease_out = CCEaseOut::create((CCActionInterval*)(drop->copy()->autorelease()) , 0.5f);
			
			m_sp->runAction( CCSequence::create(move_ease_out,CCCallFuncN::create(this, callfuncN_selector(CheckerPreview::onPreviewDrop)),NULL));
		}
		else
		{
			m_sp->removeFromParent();
			m_sp=0;
		}
	}
}

void CheckerPreview::onPreviewDrop(CCNode* node)
{
	m_sp->removeFromParent();
	m_sp=0;
	m_parent->startLink(m_column);
}