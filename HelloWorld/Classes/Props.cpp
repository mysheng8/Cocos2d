#include "Props.h"
#include "CheckerPiece.h"

void IProp::DoIt(const CheckerGame *game, const int custume)
{
	m_game	=	game;
	if (function())
		m_game->m_Energy->ReleaseEnergy(custume);
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
