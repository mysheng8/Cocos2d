#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class TitleScene : public CCLayer
{
public:
	TitleScene();
    ~TitleScene();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* TitleScene::scene();


    void closeCallback(CCObject * pSender);
	void startGame(CCObject * pSender);



private:
	CCMenu* m_pItemMenu;

    

};


#endif // __TITLE_SCENE_H__