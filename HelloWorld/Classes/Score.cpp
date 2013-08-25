#include"Score.h"
#include"resource.h"



bool Score::init()
{
	if(!initWithString("0",s_pPathScoreFont))
	{
		return false;
	}
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
	runAction(action);
	setString(string);

}

void Score::reset()
{
	m_score = 0;
	m_multi = 1;
	setString("0");

}