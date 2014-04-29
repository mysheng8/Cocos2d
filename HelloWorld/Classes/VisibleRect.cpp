#include "VisibleRect.h"

CCRect VisibleRect::s_visibleRect;
CCRect VisibleRect::s_sourceRect;

void VisibleRect::lazyInit()
{
    if (s_visibleRect.size.width == 0.0f && s_visibleRect.size.height == 0.0f)
    {
        CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
        s_visibleRect.origin = pEGLView->getVisibleOrigin();
        s_visibleRect.size = pEGLView->getVisibleSize();
		s_sourceRect = CCRect(0,0,320,480);
    }
}



CCRect VisibleRect::getVisibleRect()
{
    lazyInit();
    return CCRectMake(s_visibleRect.origin.x, s_visibleRect.origin.y, s_visibleRect.size.width, s_visibleRect.size.height);
}

float VisibleRect::layerScale()
{
	lazyInit();
	float scaleX=s_visibleRect.size.width/s_sourceRect.size.width;
	float scaleY=s_visibleRect.size.height/s_sourceRect.size.height;
	float scale=scaleX<scaleY?scaleX:scaleY;
	return scale;
}

CCPoint VisibleRect::left()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x, s_sourceRect.origin.y+s_sourceRect.size.height/2);
}

CCPoint VisibleRect::right()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x+s_sourceRect.size.width, s_sourceRect.origin.y+s_sourceRect.size.height/2);
}

CCPoint VisibleRect::top()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x+s_sourceRect.size.width/2, s_sourceRect.origin.y+s_sourceRect.size.height);
}

CCPoint VisibleRect::bottom()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x+s_sourceRect.size.width/2, s_sourceRect.origin.y);
}

CCPoint VisibleRect::center()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x+s_sourceRect.size.width/2, s_sourceRect.origin.y+s_sourceRect.size.height/2);
}

CCPoint VisibleRect::leftTop()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x, s_sourceRect.origin.y+s_sourceRect.size.height);
}

CCPoint VisibleRect::rightTop()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x+s_sourceRect.size.width, s_sourceRect.origin.y+s_sourceRect.size.height);
}

CCPoint VisibleRect::leftBottom()
{
    lazyInit();
    return s_sourceRect.origin;
}

CCPoint VisibleRect::rightBottom()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x+s_sourceRect.size.width, s_sourceRect.origin.y);
}

float VisibleRect::width()
{
    lazyInit();
    return s_sourceRect.size.width;
}

float VisibleRect::height()
{
    lazyInit();
    return s_sourceRect.size.height;
}

float VisibleRect::unit()
{
    lazyInit();
    return (s_sourceRect.size.width<s_sourceRect.size.height?s_sourceRect.size.width:s_sourceRect.size.height)/9.0;
}

float VisibleRect::lineSpace()
{
    lazyInit();
    return 70;//*layerScale();
}

CCPoint VisibleRect::origin()
{
    lazyInit();
    return ccp(s_sourceRect.origin.x+s_sourceRect.size.width/2-3.5*unit(), s_sourceRect.origin.y+s_sourceRect.size.height/2-5*unit());
}

CCPoint VisibleRect::propOrigin()
{
    lazyInit();
    return ccp(VisibleRect::left().x+200, VisibleRect::bottom().x-120);
}

CCPoint VisibleRect::propUnit()
{
    lazyInit();
    return ccp(35, 35);
}