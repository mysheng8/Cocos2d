#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public CCScene
{
public:
    GameScene();

	void runThisTest();

    void menuCallback(CCObject* pSender);
  
};

#endif // __HELLOWORLD_SCENE_H__
