#include"Energy.h";
#include"GameSettingData.h"
#include"resource.h";
#include"VisibleRect.h";

bool Energy::init()
{
	if (!CCLayer::init())
		return false;

	data=static_cast<EnergyData*>(GameSettingData::sharedSettingData().GetData("EnergyData"));
	m_vertical= true;

	CCSprite* stack = CCSprite::create(s_pPathEnergyStack);
	stack->setPosition(ccp(VisibleRect::right().x-0.5*VisibleRect::unit(), VisibleRect::bottom().y+4.7*VisibleRect::unit()));
	this->addChild(stack, 1);

	CCSprite *energy= CCSprite::create(s_pPathEnergy);
	energy->setPosition(ccp(VisibleRect::right().x-0.5*VisibleRect::unit(), VisibleRect::bottom().y+4.7*VisibleRect::unit()));
	

	CCRect box=energy->boundingBox();
	
	CCDrawNode *shape = CCDrawNode::create();
    static CCPoint triangle[4];
	triangle[0] = ccp(box.getMinX(), box.getMinY());
    triangle[1] = ccp(box.getMaxX(), box.getMinY());
    triangle[2] = ccp(box.getMaxX(), box.getMaxY());
	triangle[3] = ccp(box.getMinX(), box.getMaxY());
	shape->setAnchorPoint(ccp(box.getMinX(), box.getMinY()));
    static ccColor4F green = {0, 1, 0, 1};
    shape->drawPolygon(triangle, 4, green, 0, green);
	m_shape=shape;


	CCClippingNode* clipper = CCClippingNode::create();
	clipper->setPosition(0,0);
	clipper->setStencil(m_shape);
	clipper->addChild(energy);
	this->addChild(clipper, 2);
	m_shape->setScale(0);
	return true;
}

void Energy::Change()
{
	CCScaleTo *scale = CCScaleTo::create(0.5f,1,data->m_totalEnergy/100.0f);
	CCActionInterval*  scale_ease_in = CCEaseElasticOut::create((CCActionInterval*)(scale->copy()->autorelease()) , 0.5f);
	m_shape->runAction(scale);
}

