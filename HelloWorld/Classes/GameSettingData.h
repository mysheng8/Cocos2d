#ifndef __GAMESETTINGDATA_H__
#define __GAMESETTINGDATA_H__

#include <stdio.h>
#include<map>
#include <string>

using namespace std;


class EntityData
{
public:
	EntityData(string name){m_name=name;};
	string m_name;
};

class GameSettingData
{
public:
	EntityData* GetData(string name);
	void registData(string name,EntityData* data);
	static GameSettingData& sharedSettingData();
	void DelData(string name);
	void Release();
private:
	map<string,EntityData*> m_settings;
};

class LevelData:public EntityData
{
public:
	LevelData(string name, const unsigned int current, const unsigned int next, const float rockRate,const unsigned int levelScore):
	  EntityData(name),m_current(current),m_next(next),m_rockRate(rockRate),m_levelScore(levelScore)
	  {GameSettingData::sharedSettingData().registData(name,this);};
	unsigned int m_current;
	unsigned int m_next;
	float m_rockRate;
	LevelData *m_nextlevel;
	unsigned int m_levelScore;
};

class PropData:public EntityData
{
public:
	PropData(string name,const unsigned int cost, const unsigned int num):
	  EntityData(name),m_cost(cost),m_num(num)
	  {GameSettingData::sharedSettingData().registData(name,this);};
	unsigned int m_cost;
	unsigned int m_num;
};

class ScoreData:public EntityData
{
public:
	ScoreData(string name, const unsigned int dropScore,const unsigned int killScore, const unsigned int propScore):
	  EntityData(name),m_dropScore(dropScore),m_killScore(killScore),m_propScore(propScore),m_total(0),m_multi(1)
	  {GameSettingData::sharedSettingData().registData(name,this);};
	unsigned int m_dropScore;
	unsigned int m_killScore;
	unsigned int m_total;
	unsigned int m_multi;
	unsigned int m_propScore;
};

class EnergyData:public EntityData
{
public:
	EnergyData(string name,const unsigned int spring):
	  EntityData(name),m_spring(spring),m_totalEnergy(0),m_multi(1.0)
	  {GameSettingData::sharedSettingData().registData(name,this);};
	unsigned int m_spring;
	unsigned int m_totalEnergy;
	float m_multi;
};

enum BufferType
{
NONE=0,
DOUBLESCORE=1,
POWERENERGY=2,
NOENERGY=3
};

class BufferData:public EntityData
{
public:
	unsigned int m_period;
	BufferType m_type;
	EntityData *m_bufData;
	BufferData():
		EntityData("BufferData"),
		m_period(0),
		m_type(NONE),
		m_bufData(NULL)
		{GameSettingData::sharedSettingData().registData("BufferData",this);};
};

class JackpotData:public EntityData
{
public:
	unsigned int m_rate;
	JackpotData(string name,const unsigned int rate):
		EntityData(name),
		m_rate(rate)
		{GameSettingData::sharedSettingData().registData(name,this);};

};

class JackpotRuntimeData:public EntityData
{
public:
	unsigned int m_appear;// next jackpot appear time. 
	unsigned int m_disappear;// jackpot disappear time. 
	unsigned int m_minAppear;
	unsigned int m_minDisappear;
	bool hasJackpot;
	JackpotData	*m_jackpot;
	JackpotRuntimeData(string name):
		m_appear(10),
		m_disappear(5),
		m_minAppear(10),
		m_minDisappear(5),
		m_jackpot(NULL),
		hasJackpot(false),
		EntityData(name)
		{GameSettingData::sharedSettingData().registData(name,this);};
};

class GameData:public EntityData
{
public:
	GameData():
	  EntityData("GameData"),
	  m_nextNum(0),
	  m_nextIsRock(false),
	  m_score(NULL),
	  m_energy(NULL),
	  m_level(NULL),
	  m_buf(NULL),
	  m_jackpotRuntime(NULL)
	  {
		  GameSettingData::sharedSettingData().registData("GameData",this);
	  };
	int m_nextNum;// the number of next ball
	bool m_nextIsRock;// if the next ball is a rock

	BufferData *m_buf;
	ScoreData *m_score;
	EnergyData *m_energy;
	LevelData *m_level;
	JackpotRuntimeData *m_jackpotRuntime;
	map<string,PropData*> m_props;
};





#endif //__GAMESETTINGDATA_H__