#ifndef __ENERGY_H__
#define __ENERGY_H__

#include"cocos2d.h";

USING_NS_CC;

class Energy:public CCLayer
{
public:
	bool init();

	CREATE_FUNC(Energy);

	int GetValue(){return m_value;};
	void SetValue(int value){m_value=value;};
	void ChargeEnergy(int multi);
	void ReleaseEnergy(int value);

private:
	int m_base;
	int m_value;
	bool m_vertical;
	CCNode *m_shape;
};



#endif //__ENERGY_H__