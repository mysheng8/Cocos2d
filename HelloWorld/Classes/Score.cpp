#include"Score.h"
#include"resource.h"
#include"VisibleRect.h"
#include <stdio.h>
#include <string>

const std::string g_Bonus[15] = {
    "Good",
    "Wow",
	"Cool",
	"Nice",
	"Sweet",
	"Great",
	"Amazing",
	"Wonderful",
	"Excellent",
	"Awesome",
	"Super",
	"Fantastic",
	"Perfect",
	"Miracle",
	"Godlike"
};
bool Score::init()
{
	
	CCLabelBMFont* label = CCLabelBMFont::create("Score", s_pPathScoreFont);
	label->setPosition(ccp( VisibleRect::right().x - 60, VisibleRect::top().y - 50));
	addChild(label,1);

	m_scoreL = CCLabelBMFont::create("0",s_pPathScoreFont);
	m_scoreL->setPosition(ccp( VisibleRect::right().x - 60, VisibleRect::top().y - 80));
	addChild(m_scoreL,1);

	m_multiL = CCLabelBMFont::create("x1",s_pPathScoreFont);
	m_multiL->setPosition(ccp( VisibleRect::right().x - 60, VisibleRect::top().y - 140));
	addChild(m_multiL,1);
	m_multiL->setVisible(false);
	m_score = 0;
	m_multi = 1;
	m_base  = 10; 

	return true;
}

void Score::scoreUp()
{
	m_score+=m_multi*m_base;
	char string[12] = {0};
    sprintf(string, "%d", m_score);
	CCFiniteTimeAction*  scale = CCSequence::create(
        CCScaleBy::create(0.01,2.0,2.0),
        CCScaleBy::create(0.5,0.5,0.5),
        NULL);
	CCAction*  action = CCSpawn::create(
        CCJumpBy::create(0.2,ccp(0,0),40,1),
        scale,
        NULL);
	//action->autorelease();
	m_scoreL->runAction(action);
	m_scoreL->setString(string);
	CCLabelBMFont*	bonus = CCLabelBMFont::create(g_Bonus[(m_multi-1)%15].c_str(),s_pPathScoreFont);
	bonus->setPosition(ccp( VisibleRect::center().x, VisibleRect::center().y-40));
	bonus->setScale(1.3);
	addChild(bonus,1);
	CCFiniteTimeAction*  rise = CCSequence::create(
		CCJumpBy::create(0.3,ccp(0,0),70,1),
		CCFadeOut::create(1),
		CCCallFuncN::create(this, callfuncN_selector(Score::onDisappear)),
        NULL);
	bonus->runAction(rise);
}

void Score::reset()
{
	m_score = 0;
	m_multi = 1;
	m_scoreL->setString("0");

}

void Score::raiseMulti()
{
	++m_multi;
	char string[5] = {0};
    sprintf(string, "x%d", m_multi);
	m_multiL->setVisible(true);
	CCFiniteTimeAction*  scale = CCSequence::create(
        CCScaleBy::create(0.01,4.0,4.0),
        CCScaleBy::create(0.5,0.25,0.25),
		CCFadeOut::create(3.0f),
		CCCallFunc::create(this, callfunc_selector(Score::onRise)),
        NULL);
	m_multiL->runAction(scale);
	m_multiL->setString(string);
};

void Score::onRise()
{
	m_multiL->setVisible(false);
}

void Score::onDisappear(CCNode* node)
{
	node->removeFromParent();
}