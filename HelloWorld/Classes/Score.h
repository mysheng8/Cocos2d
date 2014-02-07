#ifndef __SCORE_H__
#define __SCORE_H__

#include "cocos2d.h"
#include "GameSettingData.h"

USING_NS_CC;

class Score:public CCLayer
{
public:
	bool init();

	CREATE_FUNC(Score);

	void raiseMulti();
	void score();
	void levelUp();
	void tinyUp();
	void PropUp();

private:
	CCLabelBMFont* m_scoreL;
	CCLabelBMFont*	m_multiL;
	void onRise();
	void onDisappear(CCNode* node);
	void addScoreUI();
	void riseBonusUI(const char* str,const float delay = 1.0f);

};


#endif //__SCORE_H__