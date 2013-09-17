#include"Score.h"
#include"resource.h"
#include"VisibleRect.h"
#include <stdio.h>
#include <string>

USING_NS_CC;

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

const ccColor3B bcolors[] = {		ccc3(185,11,60),
		ccc3(255,108,0),
		ccc3(100,183,39),
		ccc3(117,172,255),
		ccc3(179,117,255),
		ccc3(205,69,171)};


const int g_levelScore[] =	{100,150,200,300,500,1000,1500,2000,3000,5000,10000,15000,20000,30000,50000,100000,150000,200000,300000,500000,1000000};


#define BASESCORE 20;
#define DROPSCORE 5;


bool Score::init()
{
	
	CCLabelBMFont* label = CCLabelBMFont::create("Score", s_pPathScoreFont);
	label->setPosition(ccp( VisibleRect::right().x - 70, VisibleRect::top().y - 40));
	addChild(label,1);

	m_scoreL = CCLabelBMFont::create("0",s_pPathScoreFont);
	m_scoreL->setPosition(ccp( VisibleRect::right().x - 70, VisibleRect::top().y - 70));
	addChild(m_scoreL,1);

	m_multiL = CCLabelBMFont::create("x1",s_pPathScoreFont);
	m_multiL->setPosition(ccp( VisibleRect::right().x - 70, VisibleRect::top().y - 100));
	addChild(m_multiL,1);
	m_multiL->setVisible(false);
	m_score = 0;
	m_multi = 1;
	m_level	= 0;
	return true;
}

void Score::score()
{
	m_score+=m_multi*BASESCORE;
	addScore(m_score);
	riseBonus(g_Bonus[(m_multi-1)%15].c_str());
}

void Score::tinyUp()
{
	m_score+=DROPSCORE;
	addScore(m_score);
}


void Score::levelUp()
{
	m_score+=g_levelScore[m_level];
	addScore(m_score);

	char string[25] = {0};
    sprintf(string, "Level Up!\n+%d", g_levelScore[m_level]);
	riseBonus(string,2.0f);
	++m_level;
}

void Score::addScore(const int score)
{
	char string[12] = {0};
    sprintf(string, "%d", score);
	CCFiniteTimeAction*  scale = CCSequence::create(
        CCScaleTo::create(0.01f,2.0f,2.0f),
        CCScaleTo::create(0.5f,1.0f,1.0f),
        NULL);
	CCAction*  action = CCSpawn::create(
        CCJumpBy::create(0.2f,ccp(0,0),40,1),
        scale,
        NULL);
	//action->autorelease();
	m_scoreL->runAction(action);
	m_scoreL->setString(string);
}
void Score::riseBonus(const char* str,const float delay)
{
	CCLabelBMFont*	bonus = CCLabelBMFont::create(str,s_pPathScoreFont);
	bonus->setPosition(ccp( VisibleRect::center().x, VisibleRect::center().y-10));
	bonus->setScale(1.3f);
	bonus->setColor(bcolors[m_multi%6]);
	addChild(bonus,1);
	CCFiniteTimeAction*  rise = CCSequence::create(
		CCJumpBy::create(0.3f,ccp(0,0),70,1),
		CCFadeOut::create(delay),
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
        CCScaleBy::create(0.01f,4.0f,4.0f),
        CCScaleBy::create(0.5f,0.25f,0.25f),
		CCFadeOut::create(3.0f),
		CCCallFunc::create(this, callfunc_selector(Score::onRise)),
        NULL);
	m_multiL->runAction(scale);
	m_multiL->setString(string);
	m_multiL->setColor(bcolors[m_multi%6]);
};

void Score::onRise()
{
	m_multiL->setVisible(false);
}

void Score::onDisappear(CCNode* node)
{
	node->removeFromParent();
}