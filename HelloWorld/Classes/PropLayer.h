#ifndef __PROPLAYER_H__
#define __PROPLAYER_H__

#include "cocos2d.h"
#include "Props.h"
#include "GameLayer.h"


USING_NS_CC;
class Prop;

class PropSprite:public CCMenuItemImage
{
public:
	PropSprite(Prop *prop);
	void ClickCallback(CCObject* pSender);
	void Active();
	
private:
	PropData *data;
	Prop *m_Prop;
	CCLabelBMFont* m_numL; 
	void onRemoveSprite(CCNode *pSender);
};


class PropLayer:public CCLayer
{
public:
	static PropLayer* create(GameLayer *game);
	bool initWithParent(GameLayer *game);
	void AddProp(const int cur, Prop *prop);
	int GetPropNum(){return m_max;};
	PropSprite* GetPropSprite(string name);

private:
	GameLayer *m_game;
	unsigned int m_max;
	CCMenu* m_pMenu;
	Prop** m_Props;
	map<string, PropSprite*> spmap;
};

#endif