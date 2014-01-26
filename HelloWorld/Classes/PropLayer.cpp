#include "PropLayer.h"
#include "VisibleRect.h"
#include "resource.h"

PropSprite::PropSprite(Prop *prop)
{
	CCSprite *spriteNormal   = CCSprite::create(prop->GetPropImage(),  CCRectMake(PROP_SPACE*2,0,PROP_SPACE,PROP_SPACE));
	CCSprite *spriteSelected = CCSprite::create(prop->GetPropImage(),  CCRectMake(PROP_SPACE*1,0,PROP_SPACE,PROP_SPACE));
	CCSprite *spriteDisabled = CCSprite::create(prop->GetPropImage(),  CCRectMake(PROP_SPACE*0,0,PROP_SPACE,PROP_SPACE));

	initWithNormalSprite(spriteNormal,spriteSelected,spriteDisabled,this,menu_selector(PropSprite::ClickCallback) );
	m_Prop=prop;
	data=static_cast<PropData*>(GameSettingData::sharedSettingData().GetData(m_Prop->GetType()));
	char string[5] = {0};
    sprintf(string, "%d", data->m_num);
	m_numL= CCLabelBMFont::create(string, s_pPathScoreFont);
	m_numL->setScale(0.4f);
	m_numL->setPosition(ccp( PROP_SPACE-10,10));
	addChild(m_numL,1);
	setEnabled(false);
}

void PropSprite::Active()
{
	CCSprite *active_sp=CCSprite::createWithSpriteFrame(CCSpriteFrame::create(s_pPropActive,CCRectMake(0,0,PROP_SPACE,PROP_SPACE)));
	CCArray *animFrame=CCArray::create();
	for(unsigned int i = 0;i!=8;++i)
	{
		CCSpriteFrame *spf=CCSpriteFrame::create(s_pPropActive,CCRectMake(PROP_SPACE*(i),0,PROP_SPACE,PROP_SPACE));
		animFrame->addObject(spf);
	}
	CCAnimation *anim=CCAnimation::createWithSpriteFrames(animFrame,0.05f);
	active_sp->runAction(CCSequence::create(CCAnimate::create(anim),CCCallFuncN::create(this, callfuncN_selector(PropSprite::onRemoveSprite)),NULL));
	active_sp->setPosition(ccp(PROP_SPACE/2,PROP_SPACE/2));
	addChild(active_sp);
	
}

void PropSprite::onRemoveSprite(CCNode *pSender)
{
	pSender->removeFromParent();
	setEnabled(true);
}

void PropSprite::ClickCallback(CCObject* pSender)
{
	GameLayer *game=GameScene::sharedGameScene().gameLayer;
	if(game)
	{
		game->UseProp(m_Prop);
		char string[5] = {0};
		sprintf(string, "%d", data->m_num);
		m_numL->setString(string);
		if(data->m_num==0)
		{
			setEnabled(false);
			m_numL->setColor(ccRED);
		}
	}
};

bool PropLayer::initWithParent(GameLayer *game)
{
	if(!CCLayer::init())
		return false;
	m_game=game;
	m_max=3;
	m_Props=new Prop*[m_max];
	m_pMenu=CCMenu::create();
	m_pMenu->setPosition( CCPointZero );
	addChild(m_pMenu, 1);
	spmap = map<string,PropSprite*>();
	return true;
}
PropLayer* PropLayer::create(GameLayer *game)
{
	PropLayer *pl=new PropLayer();
	pl->initWithParent(game);
	return pl;
}

PropSprite* PropLayer::GetPropSprite(string name)
{
	map<string,PropSprite*>::const_iterator iter;

	iter = spmap.find(name);
	if(iter==spmap.end())
		return NULL;
	else
		return iter->second;
}

void PropLayer::AddProp(const int cur, Prop *prop)
{
	if(cur<m_max)
	{
		m_Props[cur]=prop;
		PropSprite *sp_Prop = new PropSprite(prop);
		m_pMenu->addChild(sp_Prop);
		sp_Prop->setPosition(ccp( (VisibleRect::propOrigin().x + cur*VisibleRect::propUnit().x), VisibleRect::propOrigin().y));
		sp_Prop->setScale(0.85f);
		spmap.insert(pair<string,PropSprite*>(prop->GetType(),sp_Prop));
	}
	else
		CCLog("failed to add more props ");
}