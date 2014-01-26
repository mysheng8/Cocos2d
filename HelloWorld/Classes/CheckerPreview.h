#ifndef __CHECKERPREVIEW_H__
#define __CHECKERPREVIEW_H__

#include "cocos2d.h"
#include "CheckerBoard.h"
#include "GameLayer.h"

USING_NS_CC;
class GameLayer;

class CheckerPreview: public CCNode
{
public:
	CheckerPreview(GameLayer *parent);
	void resetPreview();
	void StartPreview(int column);
	void EditPreview(int column);
	void EndPreview(int column);
	bool NeedReset(){return needReset;}
	void BombMode();
	void RandomMode();
	
private:
	GameData *data;
	CCSprite* DrawBomb();
	GameLayer *m_parent;
	CCSprite* m_sp;
	int m_column;
	bool isBomb;
	bool isRandom;
	bool needReset;
	void onPreviewDrop(CCNode* node);
	void movePreview(int column);
};

#endif //__CHECKERPREVIEW_H__