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

IMPLEMENT_JACKPOT(Jackpot)
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

bool Jackpot::function()
{
	CCLog("%s",GetType());
	return true;
}

IMPLEMENT_JACKPOT(LongLiveJackpot)

bool LongLiveJackpot::function()
{
	if(!Jackpot::function())
		return false;
	if (!m_game)
		return false;
	int num=rand()%10+1;
	char str[25] = {0};
	sprintf(str, "+%d drops to level up", num);
	m_game->riseBufferUI(str);
	m_game->DelayLevel(num);
	return true;
}

IMPLEMENT_JACKPOT(RockJackpot)

bool RockJackpot::function()
{
	if(!Jackpot::function())
		return false;
	if (!m_game)
		return false;
	m_game->riseBufferUI("Turn to Rock");
	m_game->InsertRock(*m_grid);
	return true;
}

IMPLEMENT_JACKPOT(BombJackpot)

bool BombJackpot::function()
{
	if(!Jackpot::function())
		return false;
	if (!m_game)
		return false;
	m_game->riseBufferUI("Turn to Bomb");
	m_game->InsertBomb(*m_grid);
	return true;
}

IMPLEMENT_JACKPOT(DoubleScoreJackpot)

bool DoubleScoreJackpot::function()
{
	if(!Jackpot::function())
		return false;
	if (!m_game)
		return false;

	GameData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	data->m_buf->m_period=5;
	data->m_buf->m_type=BufferType(DOUBLESCORE);
	data->m_buf->m_bufData=data->m_score;
	ScoreData *doublescore= new ScoreData("DoubleScoreData",data->m_score->m_dropScore*2,data->m_score->m_killScore*2,data->m_score->m_propScore);
	doublescore->m_total=data->m_score->m_total;
	data->m_score=doublescore;

	m_game->riseBufferUI("Double Score");
	return true;
}

IMPLEMENT_JACKPOT(PowerEnergyJackpot)

bool PowerEnergyJackpot::function()
{
	if(!Jackpot::function())
		return false;
	if (!m_game)
		return false;

	GameData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	data->m_buf->m_period=5;
	data->m_buf->m_type=BufferType(POWERENERGY);
	data->m_buf->m_bufData=data->m_energy;
	EnergyData *power=new EnergyData("PowerEnergyData",data->m_energy->m_spring);
	power->m_totalEnergy=data->m_energy->m_totalEnergy;
	data->m_energy=power;
	power->m_multi*=1.5;
	
	m_game->riseBufferUI("Power Energy");
	return true;
}

IMPLEMENT_JACKPOT(NoEnergyJackpot)

bool NoEnergyJackpot::function()
{
	if(!Jackpot::function())
		return false;
	if (!m_game)
		return false;

	GameData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"));
	data->m_buf->m_period=5;
	data->m_buf->m_type=BufferType(NOENERGY);
	data->m_buf->m_bufData=data->m_energy;
	EnergyData *power=new EnergyData("NoEnergyData",data->m_energy->m_spring);
	data->m_energy=power;
	power->m_multi*=0;
	power->m_totalEnergy=0;

	m_game->riseBufferUI("No Energy");
	m_game->LowEnergy();
	return true;
}

IMPLEMENT_JACKPOT(LevelUpJackpot)

bool LevelUpJackpot::function()
{
	if(!Jackpot::function())
		return false;
	if (!m_game)
		return false;

	m_game->levelUp();
	return true;
}