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
	void resetPreview(int num,bool isRock){m_Num=num;m_IsRock=isRock;};
	void StartPreview(int column);
	void EditPreview(int column);
	void EndPreview(int column);
	
private:
	CheckerGame *m_parent;
	CCSprite* m_sp;
	int m_Num;
	bool m_IsRock;
	int m_column;
	void onPreviewDrop(CCNode* node);
};

#endif