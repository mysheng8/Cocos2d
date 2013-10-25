#ifndef __CHECKERGAME_H__
#define __CHECKERGAME_H__

#include "cocos2d.h"
#include "Score.h"
#include "CheckerBoard.h"
#include "CheckerPreview.h"
#include "Energy.h"
#include "Props.h"

USING_NS_CC;

class CheckerPreview;
class CheckerBoard;
struct Grid;
class PropLayer;


class CheckerGame: public CCLayer
{
public:
	virtual bool init();  

	CREATE_FUNC(CheckerGame);

	void setRockRate(float rate){m_rockRate = rate;};
	void setThrehold(int threhold){m_threhold=threhold;};
	void restart();
	bool initilizeGame();
	void levelUp();
	void startLink(int column);
	void endLink();
	bool toggleKillMode(){m_killmode=!m_killmode;return m_killmode;};
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void registerWithTouchDispatcher(void);

	CCSprite* DrawPiece(const Grid element,const int num,const int rock);

	CheckerBoard* m_content;
	Score* mScore;
	Energy* m_Energy;
	PropLayer* m_PropLayer;

	void gameOver();
	void DrawGuide(const Grid start,const Grid end);
	void DrawLink(const Grid *elements, const int count,bool horizontal);

private:
	CheckerPreview *m_preview;
	float m_rockRate;
	int m_threhold;
	int m_level;
	int m_step;
	bool m_resetNext;
	CCLabelBMFont* m_levelLabel;
	CCLabelBMFont* m_dropLabel;
	bool m_killmode;

	int m_nextNum;// the number of next ball
	bool m_nextIsRock;// if the next ball is a rock
	int m_column;//current touch column

	int containsTouchLocation(CCTouch* touch);
	bool canStart();
	void resetNext();
	void DrawBoard();
	void onDrawGuide(CCNode* node);

	Grid initPoint(const Grid *elements, const int count);
	bool containPoint(const Grid point, const Grid *elements, const int count);
	CCPoint* createPoly(const Grid element,const CCPoint pnt);
	Grid nextPoint(const Grid current,const Grid *elements, const int count, bool horizontal);

};

#endif	//__CHECKERBOARD_H__