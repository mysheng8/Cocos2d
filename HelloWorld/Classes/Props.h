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
	static PropLayer* create(CheckerGame *game);
	bool initWithParent(CheckerGame *game);

	void AddProp(const int cur, Prop *prop);
	void DisplayProp(const char *normalImage, const char *selectedImage, const char *disabledImage,const int cur,Prop *prop);


private:
	CheckerGame *m_game;
	unsigned int m_max;
	CCMenu* m_pMenu;
	Prop** m_Props;
	

};

class RockBreakProp: public Prop
{
public:
	RockBreakProp(const CheckerGame* game,const int cost):Prop(game,cost){};
private:
	virtual bool function();
};

class UpperProp: public Prop
{
public:
	UpperProp(const CheckerGame* game,const int cost):Prop(game,cost){};
private:
	virtual bool function();
};

class AddScoreProp: public Prop
{
public:
	AddScoreProp(const CheckerGame* game,const int cost):Prop(game,cost){};
private:
	virtual bool function();
};

class EnergyUpProp: public Prop
{
public:
	EnergyUpProp(const CheckerGame* game,const int cost):Prop(game,cost){};
private:
	virtual bool function();
};

class LevelDownProp: public Prop
{
public:
	LevelDownProp(const CheckerGame* game,const int cost):Prop(game,cost){};
private:
	virtual bool function();
};

class KillProp: public Prop
{
public:
	KillProp(const CheckerGame* game,const int cost):Prop(game,cost){};
private:
	virtual bool function();
};


#endif //__PROPS_H__