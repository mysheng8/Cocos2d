#ifndef __JACKPOT_H__
#define __JACKPOT_H__

#include "cocos2d.h"
#include "GameScene.h"
#include <stdio.h>
#include<map>
#include <string>

typedef void*(*createJackpot)(void);

struct Grid;

class JackpotFactory
{
public:
	JackpotFactory(){};
	virtual ~JackpotFactory(){};
	void* GetJackpotByName(string jackpotName);
	void registJackpot(string name,createJackpot method);
	static JackpotFactory& sharedClassFactory();
private:
	map<string,createJackpot> m_jackpotMap;
};

class RegistJackpot
{
public:
	RegistJackpot(string name,createJackpot method)
	{
		JackpotFactory::sharedClassFactory().registJackpot(name,method);
	}
};

#define DECLARE_JACKPOT(jackpotName)\
	virtual const char* GetType();\
	static RegistJackpot* m_##jackpotName##dc ;\
	static void* createInstance(){return new jackpotName;};\

#define IMPLEMENT_PROP(jackpotName)\
	RegistJackpot* jackpotName::m_##jackpotName##dc = new RegistJackpot(#jackpotName, jackpotName::createInstance) ;\
	const char* jackpotName::GetType()\
	{\
		return #jackpotName;\
	};\


class Jackpot
{
public:
	DECLARE_JACKPOT(Jackpot)
	Jackpot();
	void setGrid(Grid *grid);
	virtual bool function(){return true;};
protected:
	GameLayer	*m_game;
	Grid		*m_grid;
	
};

class LongLiveJackpot:public Jackpot
{
public:
	DECLARE_JACKPOT(LongLiveJackpot)
	virtual bool function();
};

class RockJackpot:public Jackpot
{
public:
	DECLARE_JACKPOT(RockJackpot)
	virtual bool function();
};

class BombJackpot:public Jackpot
{
public:
	DECLARE_JACKPOT(BombJackpot)
	virtual bool function();
};

class DoubleScoreJackpot:public Jackpot
{
public:
	DECLARE_JACKPOT(DoubleScoreJackpot)
	virtual bool function();
};

class PowerEnergyJackpot:public Jackpot
{
public:
	DECLARE_JACKPOT(PowerEnergyJackpot)
	virtual bool function();
};

class NoEnergyJackpot:public Jackpot
{
public:
	DECLARE_JACKPOT(NoEnergyJackpot)
	virtual bool function();
};

class LevelUpJackpot:public Jackpot
{
public:
	DECLARE_JACKPOT(LevelUpJackpot)
	virtual bool function();
};

#endif // __JACKPOT_H__