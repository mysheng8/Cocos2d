#ifndef __SCORE_H__
#define __SCORE_H__

#include "cocos2d.h"

USING_NS_CC;

class Score:public CCLabelBMFont
{
public:
	bool init();

	CREATE_FUNC(Score);

	int getScore(){return m_score;};
	void raiseMulti(){++m_multi;};
	void reset();
	void scoreUp();
	void resetMulti(){m_multi = 1;};


private:
	int m_score;
	int m_multi;
	int m_base;


};


#endif