#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public CCLayer
{
public:
	MenuScene(); 
	~MenuScene();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    void quitCallback(CCObject * pSender);
	void resumeCallback(CCObject * pSender);
	void newCallback(CCObject * pSender);



private:
	CCMenu* m_pItemMenu;
   

};


#endif // __TITLE_SCENE_H__