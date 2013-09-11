#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"


USING_NS_CC;

class GameOver : public CCLayer
{
public:
	GameOver(); 
	~GameOver();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    void quitCallback(CCObject * pSender);
	void newCallback(CCObject * pSender);



private:
	CCMenu* m_pItemMenu;
   

};

#endif // __GAME_SCENE_H__
