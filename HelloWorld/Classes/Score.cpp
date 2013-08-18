#include"Score.h"
#include"resource.h"



bool Score::init()
{
	if(!initWithString("Score\r\n 0",s_pPathScoreFont))
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
    sprintf(string, "Score\r\n %d", m_score);
	setString(string);
}

void Score::reset()
{
	m_score = 0;
	m_multi = 1;
	setString("Score\r\n 0");

}