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
	void scoreUp();
	void resetMulti(){m_multi = 1;};


private:
	int m_score;
	int m_multi;
	int m_base;
	CCLabelBMFont* m_scoreL;
	CCLabelBMFont*	m_multiL;
	void onRise();
	void onDisappear(CCNode* node);


};


#endif