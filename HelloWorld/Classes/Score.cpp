#include"Score.h"
#include"GameSettingData.h"
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


bool Score::init()
{
	CCLabelBMFont* label = CCLabelBMFont::create("Score", s_pPathScoreFont);
	label->setPosition(ccp( VisibleRect::left().x + 70, VisibleRect::top().y - 40));
	addChild(label,1);

	m_scoreL = CCLabelBMFont::create("0",s_pPathScoreFont);
	m_scoreL->setPosition(ccp( VisibleRect::left().x + 70, VisibleRect::top().y - 70));
	addChild(m_scoreL,1);

	m_multiL = CCLabelBMFont::create("x1",s_pPathScoreFont);
	m_multiL->setPosition(ccp( VisibleRect::left().x + 70, VisibleRect::top().y - 100));
	addChild(m_multiL,1);
	m_multiL->setVisible(false);
	return true;
}

void Score::score()
{
	ScoreData *sdata=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"))->m_score;
	addScoreUI();
	riseBonusUI(g_Bonus[(sdata->m_multi-1)%15].c_str());
}

void Score::tinyUp()
{
	addScoreUI();
}


void Score::levelUp()
{
	LevelData *ldata=(static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData")))->m_level;
	addScoreUI();
	char string[25] = {0};
    sprintf(string, "Level Up!\n+%d", ldata->m_levelScore);
	riseBonusUI(string,2.0f);
}

void Score::PropUp()
{
	addScoreUI();
	ScoreData *sdata=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"))->m_score;
	char string[25] = {0};
    sprintf(string, "+%d", sdata->m_propScore);
	riseBonusUI(string,2.0f);
}


void Score::addScoreUI()
{
	ScoreData *sdata=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"))->m_score;
	char string[12] = {0};
    sprintf(string, "%d", sdata->m_total);
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
void Score::riseBonusUI(const char* str,const float delay)
{
	ScoreData *sdata=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"))->m_score;
	CCLabelBMFont*	bonus = CCLabelBMFont::create(str,s_pPathScoreFont);
	bonus->setPosition(ccp( VisibleRect::center().x, VisibleRect::center().y-10));
	bonus->setScale(1.3f);
	bonus->setColor(bcolors[(sdata->m_multi)%6]);
	addChild(bonus,1);
	CCFiniteTimeAction*  rise = CCSequence::create(
		CCJumpBy::create(0.3f,ccp(0,0),70,1),
		CCFadeOut::create(delay),
		CCCallFuncN::create(this, callfuncN_selector(Score::onDisappear)),
        NULL);
	bonus->runAction(rise);
}

void Score::raiseMulti()
{
	ScoreData *sdata=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"))->m_score;
	char string[5] = {0};
    sprintf(string, "x%d", sdata->m_multi);
	m_multiL->setVisible(true);
	CCFiniteTimeAction*  scale = CCSequence::create(
        CCScaleBy::create(0.01f,4.0f,4.0f),
        CCScaleBy::create(0.5f,0.25f,0.25f),
		CCFadeOut::create(3.0f),
		CCCallFunc::create(this, callfunc_selector(Score::onRise)),
        NULL);
	m_multiL->runAction(scale);
	m_multiL->setString(string);
	m_multiL->setColor(bcolors[(sdata->m_multi)%6]);
};

void Score::onRise()
{
	m_multiL->setVisible(false);
}

void Score::onDisappear(CCNode* node)
{
	node->removeFromParent();
}