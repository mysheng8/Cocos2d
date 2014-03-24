#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"
#include "Score.h"
#include "CheckerBoard.h"
#include "CheckerPiece.h"
#include "CheckerPreview.h"
#include "GameSettingData.h"
#include "Energy.h"
#include "PropLayer.h"
#include "Props.h"
#include "Jackpot.h"
#include<string>

using namespace std;
USING_NS_CC;

#define JACKPOT

class CheckerPreview;
class CheckerBoard;
class CheckerPiece;
struct Grid;
class PropLayer;
class Prop;

class GameLayer: public CCLayer
{
public:
	virtual bool init();  

	CREATE_FUNC(GameLayer);

	//Game function
	void restart();
	bool initilizeGame();
	void gameOver();
	void levelUp();
	void startLink(int column,const bool isBomb);
	void endLink();

	//Game mode
	void ToggleKillMode(){m_killmode=!m_killmode;};
	void BombMode();
	void RandomMode();

	//Touch 
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	//register Touch
	virtual void registerWithTouchDispatcher(void);

	//Draw UI
	CCSprite* DrawPiece(const Grid element,const int num,const int rock,const bool isBomb);
	void DrawGuide(const Grid start,const Grid end);
	void DrawLink(const Grid *elements, const int count,bool horizontal);
	CCSprite* DrawJackpot(const Grid grid);// draw jackpot
	
	//Prop function
	void InitProps(vector<string>::iterator begin,vector<string>::iterator end);
	void UseProp(Prop* p);

	//Energy function
	void EnergyUp();
	void EnergyCharge();
	void LowEnergy();

	//Score function
	void ScoreUp();
	void PropUp();
	void ScoreRiseMulti();
	void ResetMulti();
	int GetMulti();
	int GetScore();

	//jackpot function
	void DelayLevel(const unsigned int num);
	void InsertRock(const Grid grid);
	void InsertBomb(const Grid grid);
	void riseBufferUI(const char* str);
	void onDisappear(CCNode* node);
	//global object
	CheckerBoard* GetContent();
	CheckerPiece* GetCheckerPiece(unsigned int column, unsigned int row);

private:
	GameData *data;
	CheckerBoard* m_content;
	Score* mScore;
	Energy* m_Energy;
	PropLayer* m_PropLayer;
	CheckerPreview *m_preview;


	bool m_resetNext;
	bool m_canProp;
	bool m_killmode;
	CCLabelBMFont* m_levelLabel;
	CCLabelBMFont* m_dropLabel;

//	int m_nextNum;// the number of next ball
//	bool m_nextIsRock;// if the next ball is a rock

	//current touch grid
	int m_column;
	int m_row;

	void onRemoveSprite(CCNode* sender);

	int containsTouchColumnLocation(CCTouch* touch);
	int containsTouchRowLocation(CCTouch* touch);

	bool canStart();
	void checkBuffer();
	
	void resetNext();
	void DrawBoard();
	void onDrawGuide(CCNode* node);

	Grid initPoint(const Grid *elements, const int count);
	bool containPoint(const Grid point, const Grid *elements, const int count);
	CCPoint* createPoly(const Grid element,const CCPoint pnt);
	Grid nextPoint(const Grid current,const Grid *elements, const int count, bool horizontal);

};

#endif	//__CHECKERBOARD_H__