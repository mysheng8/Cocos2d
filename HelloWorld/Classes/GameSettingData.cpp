#include "GameSettingData.h"
#include <stdio.h>
using namespace std;

EntityData* GameSettingData::GetData(string name)
{
	map<string,EntityData*>::const_iterator iter;

	iter=m_settings.find(name);
	if(iter==m_settings.end())
		return NULL;
	else
		return iter->second;
}

void GameSettingData::registData(string name, EntityData* data)
{
	m_settings.insert(pair<string,EntityData*>(name,data));
}

GameSettingData& GameSettingData::sharedSettingData()
{
	static GameSettingData _sharedSettingData;
	return _sharedSettingData;
}

void GameSettingData::DelData(string name)
{
	map<string,EntityData*>::const_iterator iter;
	iter=m_settings.find(name);
	if(iter==m_settings.end())
		return;
	else
	{
		delete(iter->second);
		m_settings.erase(iter);
	}
	return;
}

void GameSettingData::Release()
{
	if (m_settings.size()!=0)
	{
		for(map<string,EntityData*>::const_iterator iter=m_settings.begin();iter!=m_settings.end();++iter)
		{
			delete(iter->second);
		}
		m_settings.clear();
	}
}