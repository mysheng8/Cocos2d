#include"Energy.h";
#include"GameSettingData.h"
#include"resource.h";
#include"VisibleRect.h";

bool Energy::init()
{
	if (!CCLayer::init())
		return false;

	m_vertical= true;

	CCSprite* stack = CCSprite::create(s_pPathEnergyStack);
	stack->setPosition(ccp(VisibleRect::right().x-0.5*VisibleRect::unit(), VisibleRect::bottom().y+4.7*VisibleRect::unit()));
	this->addChild(stack, 1);

	CCSprite *energy= CCSprite::create(s_pPathEnergy);
	energy->setPosition(ccp(VisibleRect::right().x-0.5*VisibleRect::unit(), VisibleRect::bottom().y+4.7*VisibleRect::unit()));
	

	CCRect box=energy->boundingBox();
	
	CCDrawNode *shape = CCDrawNode::create();
    static CCPoint poly[4];
	poly[0] = ccp(box.getMinX(), box.getMinY());
    poly[1] = ccp(box.getMaxX(), box.getMinY());
    poly[2] = ccp(box.getMaxX(), box.getMaxY());
	poly[3] = ccp(box.getMinX(), box.getMaxY());
	shape->setAnchorPoint(ccp(box.getMinX(), box.getMinY()));
    static ccColor4F green = {0, 1, 0, 1};
    shape->drawPolygon(poly, 4, green, 0, green);
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
	EnergyData *data=static_cast<GameData*>(GameSettingData::sharedSettingData().GetData("GameData"))->m_energy;
	CCScaleTo *scale = CCScaleTo::create(0.5f,1,data->m_totalEnergy/100.0f);
	CCActionInterval*  scale_ease_in = CCEaseElasticOut::create((CCActionInterval*)(scale->copy()->autorelease()) , 0.5f);
	m_shape->runAction(scale);
}

void Energy::LowEnergy()
{
	Change();
}

