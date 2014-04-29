#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class TitleScene : public CCScene
{
public:
	TitleScene();
    ~TitleScene();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer

    void closeCallback(CCObject * pSender);
	void startGame(CCObject * pSender);
	void rankCallback(CCObject * pSender);

	//Android function
	virtual void keyBackClicked();


private:
	CCMenu* m_pItemMenu;

};


#endif // __TITLESCENE_H__