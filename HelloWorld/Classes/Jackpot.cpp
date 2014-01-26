#include "Jackpot.h"
#include "CheckerPiece.h"
#include "resource.h"
#include <stdio.h>
#include <stack>
using namespace std;

USING_NS_CC;

void* JackpotFactory::GetJackpotByName(string jackpotName)
{
	map<string,createJackpot>::const_iterator iter;

	iter=m_jackpotMap.find(jackpotName);
	if(iter==m_jackpotMap.end())
		return NULL;
	else
		return iter->second();
}

void JackpotFactory::registJackpot(string name,createJackpot method)
{
	m_jackpotMap.insert(pair<string,createJackpot>(name,method));
}

JackpotFactory& JackpotFactory::sharedClassFactory()
{
	static JackpotFactory _sharedClassFactory;
	return _sharedClassFactory;
}

IMPLEMENT_PROP(Jackpot)
void Jackpot::setGrid( Grid *grid)
{
	m_grid = grid;
}


Jackpot::Jackpot()
{
	//init( 0,0);
	if(GameScene::sharedGameScene().gameLayer)
	{
		m_game=GameScene::sharedGameScene().gameLayer;
	}
	//m_game=0;
}

IMPLEMENT_PROP(LongLiveJackpot)

bool LongLiveJackpot::function()
{
	if (!m_game)
		return false;
	m_game->DelayLevel(5);
	return true;
}

IMPLEMENT_PROP(RockJackpot)

bool RockJackpot::function()
{
	if (!m_game)
		return false;
	m_game->InsertRock(*m_grid);
	return true;
}

IMPLEMENT_PROP(BombJackpot)

bool BombJackpot::function()
{
	if (!m_game)
		return false;
	m_game->InsertBomb(*m_grid);
	return true;
}

IMPLEMENT_PROP(DoubleScoreJackpot)

bool DoubleScoreJackpot::function()
{
	if (!m_game)
		return false;

	GameData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	data->m_buf->m_period=5;
	data->m_buf->m_type=BufferType(DOUBLESCORE);
	data->m_buf->m_bufData=data->m_score;
	ScoreData *doublescore=&ScoreData(*(data->m_score));
	doublescore->m_name="DoubleScoreData";
	data->m_score=doublescore;
	doublescore->m_dropScore*=2;
	doublescore->m_killScore*=2;

	return true;
}

IMPLEMENT_PROP(PowerEnergyJackpot)

bool PowerEnergyJackpot::function()
{
	if (!m_game)
		return false;

	GameData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	data->m_buf->m_period=5;
	data->m_buf->m_type=BufferType(POWERENERGY);
	data->m_buf->m_bufData=data->m_energy;
	EnergyData *power=&EnergyData(*(data->m_energy));
	power->m_name="PowerEnergy";
	data->m_energy=power;
	power->m_multi*=1.5;

	return true;
}

IMPLEMENT_PROP(NoEnergyJackpot)

bool NoEnergyJackpot::function()
{
	if (!m_game)
		return false;

	GameData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	data->m_buf->m_period=5;
	data->m_buf->m_type=BufferType(NOENERGY);
	data->m_buf->m_bufData=data->m_energy;
	EnergyData *power=&EnergyData(*(data->m_energy));
	power->m_name="NoEnergy";
	data->m_energy=power;
	power->m_multi*=0;
	power->m_totalEnergy=0;
	return true;
}

IMPLEMENT_PROP(LevelUpJackpot)

bool LevelUpJackpot::function()
{
	if (!m_game)
		return false;
	m_game->levelUp();
	return true;
}