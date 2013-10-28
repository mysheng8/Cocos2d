#ifndef __CHECKERPREVIEW_H__
#define __CHECKERPREVIEW_H__

#include "cocos2d.h"
#include "CheckerBoard.h"
#include "CheckerGame.h"

USING_NS_CC;
class CheckerGame;

class CheckerPreview: public CCNode
{
public:
	CheckerPreview(CheckerGame *parent);
	void resetPreview(int num,bool isRock);
	void StartPreview(int column);
	void EditPreview(int column);
	void EndPreview(int column);
	bool NeedReset(){return needReset;}
	void BombMode();
	
private:
	CCSprite* DrawBomb();
	CheckerGame *m_parent;
	CCSprite* m_sp;
	int m_Num;
	bool m_IsRock;
	int m_column;
	bool isBomb;
	bool needReset;
	void onPreviewDrop(CCNode* node);
	void movePreview(int column);
};

#endif //__CHECKERPREVIEW_H__