#ifndef __ENERGY_H__
#define __ENERGY_H__

#include"cocos2d.h";
#include"GameSettingData.h"

USING_NS_CC;

class Energy:public CCLayer
{
public:
	bool init();

	CREATE_FUNC(Energy);

	void Change();

private:
	EnergyData *data;
	bool m_vertical;
	CCNode *m_shape;
};



#endif //__ENERGY_H__