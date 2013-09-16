#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include <stdio.h>
#include <string>

USING_NS_CC;


struct rank
{
	std::string name;
	int score;
	rank(std::string inName, int inScore):name(inName),score(inScore){};
};


class GameOver : public CCLayer
{
public:
	GameOver(); 
	~GameOver();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    void quitCallback(CCObject * pSender);
	void newCallback(CCObject * pSender);

	void Rank(rank input);



private:
	CCMenu* m_pItemMenu;


   

};

#endif // __GAME_SCENE_H__
