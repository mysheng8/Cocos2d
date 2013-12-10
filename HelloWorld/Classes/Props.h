#ifndef __PROPS_H__
#define __PROPS_H__


#include "cocos2d.h"
#include "CheckerGame.h"
#include <stdio.h>
#include<map>
#include <string>

USING_NS_CC;
using namespace std;
class CheckerGame;

typedef void*(*createProp)(void);
class PropFactory
{
public:
	PropFactory();
	virtual ~PropFactory();
	void* GetPropByName(string propName);
	void registProp(string name,createProp method);
	static PropFactory& sharedClassFactory();
private:
	map<string,createProp> m_propMap;
};

class RegistProp
{
public:
	RegistProp(string name,createProp method)
	{
		PropFactory::sharedClassFactory().registProp(name,method);
	}
};


#define DECLARE_PROP(propName)static RegistProp* m_propName##dc ;

#define IMPLEMENT_PROP(propName)RegistProp* propName::m_propName##dc = new RegistProp(#propName, propName::createInstance) ;

class Prop
{
private:
	unsigned int m_cost;
	unsigned int m_num;
public:
	DECLARE_PROP(Prop)
	Prop();
	virtual ~Prop();
	void init(CheckerGame* game,const int cost);
	void addNum(const int k);
	void DoIt();
protected:
	CheckerGame *m_game;
	virtual bool function();
	static void* createInstance(){return new Prop();};
};
IMPLEMENT_PROP(Prop)

#define CREATE_PROP(propName)static void* createInstance(){return new propName;};

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
	int GetPropNum(){return m_max;};


private:
	CheckerGame *m_game;
	unsigned int m_max;
	CCMenu* m_pMenu;
	Prop** m_Props;
	

};

class RockBreakProp: public Prop
{
public:
	RockBreakProp();
	CREATE_PROP(RockBreakProp)
private:
	virtual bool function();
};


class UpperProp: public Prop
{
public:
	UpperProp();
	CREATE_PROP(UpperProp)
private:
	virtual bool function();
};

class AddScoreProp: public Prop
{
public:
	AddScoreProp();
	CREATE_PROP(AddScoreProp)
private:
	virtual bool function();
};

class EnergyUpProp: public Prop
{
public:
	EnergyUpProp();
	CREATE_PROP(EnergyUpProp)
private:
	virtual bool function();
};

class LevelDownProp: public Prop
{
public:
	LevelDownProp();
	CREATE_PROP(LevelDownProp)
private:
	virtual bool function();
};

class KillProp: public Prop
{
public:
	KillProp();
	CREATE_PROP(KillProp)
private:
	virtual bool function();
};

class PrimeProp: public Prop
{
public:
	PrimeProp();
	CREATE_PROP(PrimeProp)
	bool static IsPrime(const int num);
private:
	virtual bool function();
	
};

class BombProp: public Prop
{
public:
	BombProp();
	CREATE_PROP(BombProp)
private:
	virtual bool function();
};

class RandomProp: public Prop
{
public:
	RandomProp();
	CREATE_PROP(RandomProp)
private:
	virtual bool function();
};

#endif //__PROPS_H__