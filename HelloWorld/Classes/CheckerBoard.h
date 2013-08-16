#ifndef __CHECKERBOARD_H__
#define __CHECKERBOARD_H__

#include "cocos2d.h"
#include "CheckerPiece.h"
#include <stdio.h>
#include <vector>
#include <bitset>
using std::vector;
using std::bitset;


USING_NS_CC;

class CheckerPiece;
struct Grid;

class CheckerBoard: public CCLayer
{
public:
	virtual bool init();  

	CheckerPiece* addPiece(const int column ,const int num,const bool isRock);
	CCSprite* DrawPiece(const Grid element,const int num,const int rock);

	CREATE_FUNC(CheckerBoard);

	void onRemovedPieces();
	void onDropPieces();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void registerWithTouchDispatcher(void);

private:

	CheckerPiece **content;
	CCSprite* preview;
	vector<CheckerPiece*> removeList;

	int m_removedPieces;
	int m_dropedPieces;
	int m_preDropPieces;

	int m_nextNum;// the number of next ball
	bool m_nextIsRock;// if the next ball is a rock
	int m_column;//current touch column

	CCPoint m_origin;
	float m_delta;

	int containsTouchLocation(CCTouch* touch);
	int previewDropPos(const int column);

	void onPreviewDrop(CCNode* node);
	//check each checkerpiece number if it's equal to length of line.
	void checkColumnPiece(const int column);
	void checkRowPiece(const int row);
	
	void startLink(const Grid element);
	void removePieces();

	void arrangePieceColumn(int column);
	void DrawBoard();
	




};

#endif