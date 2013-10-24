#include"Energy.h";
#include"resource.h";
#include"VisibleRect.h";

bool Energy::init()
{
	if (!CCLayer::init())
		return false;

	m_value=0;
	m_base=2;
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
}

void Energy::Charge(const int multi)
{
	m_value+=multi*m_base;
	if (m_value > 100)
		m_value = 100;
	CCScaleTo *scale = CCScaleTo::create(0.5f,1,m_value/100.0f);
	CCActionInterval*  scale_ease_in = CCEaseElasticOut::create((CCActionInterval*)(scale->copy()->autorelease()) , 0.5f);
	m_shape->runAction(scale);
	char string[5]= {0};
	sprintf(string,"%d",multi);
	CCLog(string);
}

void Energy::Release(const int value)
{
	m_value-=value;
	CCScaleTo *scale = CCScaleTo::create(0.5f,1,m_value/100.0f);
	CCActionInterval*  scale_ease_in = CCEaseElasticOut::create((CCActionInterval*)(scale->copy()->autorelease()) , 0.5f);
	m_shape->runAction(scale);
}

bool Energy::CanRelease(const int value)
{
	return m_value>value;
}