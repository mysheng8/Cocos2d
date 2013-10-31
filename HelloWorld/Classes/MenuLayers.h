#ifndef __MENULAYERS_H__
#define __MENULAYERS_H__

#include "cocos2d.h"
#include "GameScene.h"
#include <stdio.h>
#include <string>
#include <map>

USING_NS_CC;

using namespace std;
class PopoutMenu: public CCLayer
{
public:
	PopoutMenu();
	~PopoutMenu();
	virtual void  jumpIn();
	virtual void jumpOut();

	virtual void restartCallback(CCObject * pSender);
	virtual void resumeCallback(CCObject * pSender);
	virtual void quitCallback(CCObject * pSender);

};

class MenuLayer : public PopoutMenu
{
public:
	MenuLayer(); 
	~MenuLayer();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer

	void optionCallback(CCObject * pSender);
	void backCallback(CCObject * pSender);
	void setSoundCallback(CCObject * pSender);
	void setMusicCallback(CCObject * pSender);

private:
	CCMenu* m_pMainMenu;
	CCMenu* m_pSubMenu;

	int m_sound;
	int m_music;

};

class GameScene;

class GameOverLayer:public PopoutMenu
{
public:
	GameOverLayer(GameScene *parent = 0); 
	~GameOverLayer();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    void submitCallback(CCObject * pSender);
	void setSubmitEnable(bool canSubmit);

private:
	CCMenu* m_pItemMenu;
	CCMenuItemLabel *pSubmitItem;
	GameScene *pScene;
};

class InputLayer:public PopoutMenu, public CCIMEDelegate
{
public:
	InputLayer();

    virtual void onClickTrackNode(bool bClicked);

	virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);


    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void backCallback(CCObject * pSender);
	void nextCallback(CCObject * pSender);

protected:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
};

struct Rank
{
public:
	string name;
	int score;
	Rank(const string inName = " ",  const int inScore = 0):name(inName),score(inScore){};
};

class RankLayer: public PopoutMenu
{
public:
	RankLayer();
	~RankLayer();

	virtual void onEnter();

	void backCallback(CCObject * pSender);
	void nextCallback(CCObject * pSender);
	void quitCallback(CCObject * pSender);
	void addButtons(bool isGameOver);
	void rank(const Rank input);

	void rank();


private:
	list<Rank> *scoreList;

};

class PropsMenuLayer: public PopoutMenu
{

public:
	PropsMenuLayer();
	~PropsMenuLayer();

	void selectCallback(CCObject * pSender);
	void startGameCallback(CCObject * pSender);
private:
	unsigned int m_max;
	CCMenu *pMenu;
	vector<string> list;
	map<CCMenuItemSprite*,string> sp_Map;
	void AddButton(const char* imageProp,const string propName,const int row, const int column);  
};


#endif // __MENULAYERS_H__