#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PopoutMenu: public CCLayer
{
public:
	PopoutMenu();
	~PopoutMenu();
	void  jumpIn();
	void jumpOut();

};


class MenuScene : public PopoutMenu
{
public:
	MenuScene(); 
	~MenuScene();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    void quitCallback(CCObject * pSender);
	void resumeCallback(CCObject * pSender);
	void newCallback(CCObject * pSender);

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

class RankScene: public PopoutMenu
{
public:
	RankScene();
	~RankScene();

	void rank(int inScore);

	void inputName();


};


#endif // __TITLE_SCENE_H__