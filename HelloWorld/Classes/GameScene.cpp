#include "GameScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "CheckerBoard.h"
#include "MenuLayers.h"
#include "TitleScene.h"

USING_NS_CC;

GameScene::GameScene()
{
	CCScene::init();
	gameLayer = 0;
	menuLayer = 0;
	prevLayer = 0;
	propLayer = 0;

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathCloseNormal, s_pPathCloseSelect, this, menu_selector(GameScene::menuCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);
	pCloseItem->setPosition(ccp( VisibleRect::right().x -40, VisibleRect::top().y - 40));
    pMenu->setPosition( CCPointZero );
	addChild(pMenu, 1);
}

GameScene& GameScene::sharedGameScene()
{
	static GameScene _sharedGameScene;
	return _sharedGameScene;
}


void GameScene::menuCallback(CCObject* pSender)
{
	if(menuLayer)
		removeChild(menuLayer);
	menuLayer = new MenuLayer();
	addChild(menuLayer,1);
	menuLayer->release();
	menuLayer->jumpIn();
}

void GameScene::startGame()
{
	initGameData();
	gameLayer = GameLayer::create();
	addChild(gameLayer,0);

    CCDirector::sharedDirector()->replaceScene(this);
	propLayer = new PropsMenuLayer();
	addChild(propLayer,1);
	propLayer->release();
	propLayer->jumpIn();

}
void GameScene::restart()
{
	if(menuLayer)
		menuLayer->jumpOut(CCCallFunc::create(this, callfunc_selector(GameScene::onRestart)));
}

void GameScene::onRestart()
{
	//reset game data
	GameSettingData::sharedSettingData().Release();
	j_list.clear();
	vector<JackpotData*>().swap(j_list);
	initGameData();

	if(gameLayer)
		gameLayer->restart();
	if(propLayer)
		removeChild(propLayer);
	propLayer = new PropsMenuLayer();
	addChild(propLayer,1);
	propLayer->release();
	propLayer->jumpIn();
}


void GameScene::resumeGame()
{
	menuLayer->jumpOut();
}

void GameScene::gameOver()
{
	removeChild(menuLayer);
	gameLayer->setTouchEnabled(false);
	menuLayer = new GameOverLayer(this);
	addChild(menuLayer,1);
	menuLayer->jumpIn();
}

void GameScene::quitGame()
{
	menuLayer->jumpOut(CCCallFunc::create(this, callfunc_selector(GameScene::onQuit)));
}

void GameScene::onQuit()
{
	CCScene *nextScene =new TitleScene();
    // run
    CCDirector::sharedDirector()->replaceScene(nextScene);
	nextScene->release();
}

void GameScene::switchMenu()
{
	if(prevLayer&&prevLayer!=nextLayer)
		prevLayer->cleanup();
	prevLayer=menuLayer;
	menuLayer->jumpOut(CCCallFunc::create(this, callfunc_selector(GameScene::onSwitch)));
}

void GameScene::onSwitch()
{
	removeChild(menuLayer,false);
	menuLayer = nextLayer;
	addChild(menuLayer,1);
	menuLayer->jumpIn();
}

GameScene::~GameScene()
{
	GameSettingData::sharedSettingData().Release();
	j_list.clear();
	vector<JackpotData*>().swap(j_list);
}

void GameScene::initGameData()
{
	LevelData *level26=new LevelData("level26",20,5,0.5,10000);
	LevelData *level25=new LevelData("level25",20,5,0.5,10000);
	LevelData *level24=new LevelData("level24",20,5,0.5,5000);
	LevelData *level23=new LevelData("level23",20,5,0.5,5000);
	LevelData *level22=new LevelData("level22",20,5,0.5,5000);
	LevelData *level21=new LevelData("level21",20,5,0.5,5000);
	LevelData *level20=new LevelData("level20",20,5,0.5,5000);
	LevelData *level19=new LevelData("level19",19,8,0.5,2000);
	LevelData *level18=new LevelData("level18",18,8,0.5,2000);
	LevelData *level17=new LevelData("level17",17,8,0.5,2000);
	LevelData *level16=new LevelData("level16",16,10,0.5,1000);
	LevelData *level15=new LevelData("level15",15,10,0.5,1000);
	LevelData *level14=new LevelData("level14",14,10,0.5,1000);
	LevelData *level13=new LevelData("level13",13,10,0.5,1000);
	LevelData *level12=new LevelData("level12",12,10,0.5,1000);
	LevelData *level11=new LevelData("level11",11,12,0.5,500);
	LevelData *level10=new LevelData("level10",10,12,0.5,500);
	LevelData *level9=new LevelData("level9",9,12,0.5,500);
	LevelData *level8=new LevelData("level8",8,12,0.5,500);
	LevelData *level7=new LevelData("level7",7,15,0.5,300);
	LevelData *level6=new LevelData("level6",6,15,0.5,300);
	LevelData *level5=new LevelData("level5",5,15,0.5,300);
	LevelData *level4=new LevelData("level4",4,18,0.5,200);
	LevelData *level3=new LevelData("level3",3,18,0.5,200);
	LevelData *level2=new LevelData("level2",2,20,0.5,100);
	LevelData *level1=new LevelData("Level1",1,20,0.5,100);


	level1->m_nextlevel=level2;
	level2->m_nextlevel=level3;
	level3->m_nextlevel=level4;
	level4->m_nextlevel=level5;
	level5->m_nextlevel=level6;
	level6->m_nextlevel=level7;
	level7->m_nextlevel=level8;
	level8->m_nextlevel=level9;
	level9->m_nextlevel=level10;
	level10->m_nextlevel=level11;
	level11->m_nextlevel=level12;
	level12->m_nextlevel=level13;
	level13->m_nextlevel=level14;
	level14->m_nextlevel=level15;
	level15->m_nextlevel=level16;
	level16->m_nextlevel=level17;
	level17->m_nextlevel=level18;
	level18->m_nextlevel=level19;
	level19->m_nextlevel=level20;
	level20->m_nextlevel=level21;
	level21->m_nextlevel=level22;
	level22->m_nextlevel=level23;
	level23->m_nextlevel=level24;
	level24->m_nextlevel=level25;
	level25->m_nextlevel=level26;

	ScoreData *score= new ScoreData("ScoreData",5,20,2000);
	EnergyData *energy=new EnergyData("EnergyData",5);
	JackpotRuntimeData *jackpot=new JackpotRuntimeData("JackpotRuntimeData");
	GameData *data=new GameData();
	data->m_buf=new BufferData();
	data->m_level=level1;
	data->m_score=score;
	data->m_energy=energy;
	data->m_jackpotRuntime=jackpot;


	PropData *RockBreakProp=new PropData("RockBreakProp",60,4);
	PropData *UpperProp=new PropData("UpperProp",50,4);
	PropData *AddScoreProp=new PropData("AddScoreProp",20,6);
	PropData *EnergyUpProp=new PropData("EnergyUpProp",30,4);
	PropData *LevelDownProp=new PropData("LevelDownProp",70,3);
	PropData *KillProp=new PropData("KillProp",40,4);
	PropData *PrimeProp=new PropData("PrimeProp",30,4);
	PropData *BombProp=new PropData("BombProp",30,4);
	PropData *RandomProp=new PropData("RandomProp",30,4);


	
	j_list.push_back(new JackpotData("LongLiveJackpot",8));
	j_list.push_back(new JackpotData("RockJackpot",10));
	j_list.push_back(new JackpotData("BombJackpot",6));
	j_list.push_back(new JackpotData("DoubleScoreJackpot",10));
	j_list.push_back(new JackpotData("PowerEnergyJackpot",7));
	j_list.push_back(new JackpotData("NoEnergyJackpot",6));
	j_list.push_back(new JackpotData("LevelUpJackpot",4));

	randomJackpot();

}

void GameScene::randomJackpot()
{
	JackpotRuntimeData *data=static_cast<JackpotRuntimeData*>(GameSettingData::sharedSettingData().GetData("JackpotRuntimeData"));
	data->m_jackpot=*RandomJackpot::getRandomJackpot(j_list.begin(),j_list.end());
}

vector<JackpotData*>::iterator RandomJackpot::getRandomJackpot(vector<JackpotData*>::iterator begin,vector<JackpotData*>::iterator end)
{
	int sum=0;
	for(vector<JackpotData*>::iterator it=begin;it!=end;++it)
	{
		sum+=(*it)->m_rate;
	}
	int r=rand()%sum;

	int i=0;
	vector<JackpotData*>::iterator it=begin;
	while(r>10)
	{
		r-=(*it)->m_rate;
		++it;
	}
	return it;
}

