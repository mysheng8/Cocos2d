#ifndef __SCORE_H__
#define __SCORE_H__

#include "cocos2d.h"

USING_NS_CC;

class Score:public CCLayer
{
public:
	bool init();

	CREATE_FUNC(Score);

	int getScore(){return m_score;};
	void raiseMulti();
	void reset();
	void score();
	void levelUp();
	void tinyUp();
	void resetMulti(){m_multi = 1;};
	int getMulti(){return m_multi;};
	void PropUp(const int score);

private:
	int m_score;
	int m_multi;
	int m_level;
	CCLabelBMFont* m_scoreL;
	CCLabelBMFont*	m_multiL;
	void onRise();
	void onDisappear(CCNode* node);
	void addScore(const int score);
	void riseBonus(const char* str,const float delay = 1.0f);

};


#endif //__SCORE_H__