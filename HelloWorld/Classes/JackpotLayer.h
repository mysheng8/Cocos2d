#ifndef __JACKPOTPLAYER_H__
#define __JACKPOTLAYER_H__

#include "cocos2d.h"
#include "Jackpot.h"
#include "GameLayer.h"

USING_NS_CC;
class Jackpot;

class JackpotLayer:public CCLayer
{
public:
	static PropLayer* create(GameLayer *game);
	bool initWithParent(GameLayer *game);
	void ResetJackpot();
private:
	GameLayer *m_game;
	
}

#endif