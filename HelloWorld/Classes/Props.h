#ifndef __PROPS_H__
#define __PROPS_H__


#include "cocos2d.h"
#include "GameScene.h"
#include <stdio.h>
#include<map>
#include <string>

USING_NS_CC;
using namespace std;
class GameLayer;

typedef void*(*createProp)(void);
class PropFactory
{
public:
	PropFactory(){};
	virtual ~PropFactory(){};
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


#define DECLARE_PROP(propName)\
	virtual const char* GetType();\
	static RegistProp* m_##propName##dc ;\
	static void* createInstance(){return new propName;};\
	virtual const char* GetPropImage();
	
#define IMPLEMENT_PROP(propName)\
	RegistProp* propName::m_##propName##dc = new RegistProp(#propName, propName::createInstance) ;\
	const char* propName::GetPropImage()\
	{\
		return s_p##propName;\
	};\
	const char* propName::GetType()\
	{\
		return #propName;\
	};\

class Prop
{
public:
	DECLARE_PROP(Prop)
	Prop();
	virtual bool function(){return true;};
protected:
	GameLayer *m_game;
	
};

class RockBreakProp: public Prop
{
public:
	DECLARE_PROP(RockBreakProp)
	RockBreakProp();
private:
	virtual bool function();
};


class UpperProp: public Prop
{
public:
	UpperProp();
	DECLARE_PROP(UpperProp)
private:
	virtual bool function();
};


class AddScoreProp: public Prop
{
public:
	AddScoreProp();
	DECLARE_PROP(AddScoreProp)
private:
	virtual bool function();
};


class EnergyUpProp: public Prop
{
public:
	EnergyUpProp();
	DECLARE_PROP(EnergyUpProp)
private:
	virtual bool function();
};


class LevelDownProp: public Prop
{
public:
	LevelDownProp();
	DECLARE_PROP(LevelDownProp)
private:
	virtual bool function();
};


class KillProp: public Prop
{
public:
	KillProp();
	DECLARE_PROP(KillProp)
private:
	virtual bool function();
};


class PrimeProp: public Prop
{
public:
	PrimeProp();
	DECLARE_PROP(PrimeProp)
	bool static IsPrime(const int num);
private:
	virtual bool function();
};


class BombProp: public Prop
{
public:
	BombProp();
	DECLARE_PROP(BombProp)
private:
	virtual bool function();
};


class RandomProp: public Prop
{
public:
	RandomProp();
	DECLARE_PROP(RandomProp)
private:
	virtual bool function();
};


#endif //__PROPS_H__