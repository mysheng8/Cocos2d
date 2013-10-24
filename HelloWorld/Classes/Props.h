#ifndef __PROPS_H__
#define __PROPS_H__


#include "cocos2d.h"
#include "CheckerGame.h"
#include <stdio.h>

USING_NS_CC;

class CheckerGame;

class Prop
{
private:
	unsigned int m_cost;
	unsigned int m_num;
public:
	Prop(const CheckerGame* game,const int cost);
	void addNum(const int k);
	void DoIt();
protected:
	const CheckerGame *m_game;
	virtual bool function() = 0;
};

class PropSprite:public CCMenuItemImage
{
public:
	PropSprite(const char *normalImage, const char *selectedImage, const char *disabledImage,Prop *prop);
	void ClickCallback(CCObject* pSender){m_Prop->DoIt();};
private:
	Prop *m_Prop;
};

class PropLayer:public CCLayer
{
public:
	Prop** m_Props;
private:
	CheckerGame *m_game;
	unsigned int m_max;
	CCMenu* m_pMenu;

	virtual bool init();

	CREATE_FUNC(PropLayer);

	void AddProp(const int cur, Prop *prop);
	void DisplayProp(const char *normalImage, const char *selectedImage, const char *disabledImage,const int cur,Prop *prop);
};

class RockBreakProp: public Prop
{
private:
	virtual bool function();
};

class RotationProp: public Prop
{
private:
	virtual bool function();
};


#endif //__PROPS_H__