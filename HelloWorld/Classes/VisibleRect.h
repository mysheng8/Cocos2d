#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"
USING_NS_CC;

class VisibleRect
{
public:
    static CCRect getVisibleRect();
	static float layerScale();

    static CCPoint left();
    static CCPoint right();
    static CCPoint top();
    static CCPoint bottom();
    static CCPoint center();
    static CCPoint leftTop();
    static CCPoint rightTop();
    static CCPoint leftBottom();
    static CCPoint rightBottom();

	static float width();
	static float height();
	static float unit();
	static float lineSpace();
	static CCPoint origin();
	static CCPoint propOrigin();
	static CCPoint propUnit();
private:
    static void lazyInit();
    static CCRect s_visibleRect;
	static CCRect s_sourceRect;
};

#endif /* __VISIBLERECT_H__ */