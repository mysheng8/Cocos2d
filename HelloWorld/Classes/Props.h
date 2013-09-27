#ifndef __PROPS_H__
#define __PROPS_H__

#include "cocos2d.h"
#include "CheckerGame.h"

class CheckerGame;

class IProp
{
public:
	void DoIt(const CheckerGame *game, const int custume);
	const CheckerGame *m_game;

	virtual bool function() = 0;

};

class RockBreakProp: public IProp
{
private:
	virtual bool function();
};

class RotationProp: public IProp
{
private:
	virtual bool function();
};


#endif //__PROPS_H__