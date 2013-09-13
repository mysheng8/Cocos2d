#ifndef __CHECKERGAME_H__
#define __CHECKERGAME_H__

#include "cocos2d.h"
#include "Score.h"
#include "CheckerBoard.h"
#include "CheckerPreview.h"


USING_NS_CC;

class CheckerPreview;
class CheckerBoard;
struct Grid;


class CheckerGame: public CCLayer
{
public:
	virtual bool init();  

	CREATE_FUNC(CheckerGame);

	void setRockRate(float rate){m_rockRate = rate;};
	void setThrehold(int threhold){m_threhold=threhold;};

	bool initilizeGame();
	void levelUp();
	void startLink(int column);
	void endLink();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void registerWithTouchDispatcher(void);

	CCSprite* DrawPiece(const Grid element,const int num,const int rock);

	CheckerBoard* m_content;

	Score* mScore;
	void gameOver();
	void DrawGuide(const Grid start,const Grid end);
	void DrawLink(const Grid *elements, const int count,bool horizontal);


private:
	CheckerPreview *m_preview;
	float m_rockRate;
	int m_threhold;
	int m_level;
	bool m_resetNext;

	int m_nextNum;// the number of next ball
	bool m_nextIsRock;// if the next ball is a rock
	int m_column;//current touch column

	int containsTouchLocation(CCTouch* touch);

	void resetNext();
	void DrawBoard();
	void onDrawGuide(CCNode* node);

	Grid initPoint(const Grid *elements, const int count);
	bool containPoint(const Grid point, const Grid *elements, const int count);
	CCPoint* createPoly(const Grid element,const CCPoint pnt);
	Grid nextPoint(const Grid current,const Grid *elements, const int count, bool horizontal);

};








#endif