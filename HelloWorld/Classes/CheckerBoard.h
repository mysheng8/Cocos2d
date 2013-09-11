#ifndef __CHECKERBOARD_H__
#define __CHECKERBOARD_H__

#include "cocos2d.h"
#include "CheckerPiece.h"
#include "CheckerGame.h"
#include <stdio.h>
#include <vector>


using std::vector;

//#define DEBUGVIEW 

USING_NS_CC;

class CheckerPiece;
class CheckerGame;
struct Grid;


class CheckerBoard
{
public:
	CheckerBoard(CheckerGame *parent);  

	CheckerPiece* addPiece(const int column ,const int num,const bool isRock);

	void onRemovedPieces(const Grid element);
	void onDropPieces();

	bool levelUp();

	int getHeight(const int column);
	void startLink(const Grid element);

	CheckerGame *m_parent;

private:
	
	CheckerPiece **content;
	
	vector<CheckerPiece*> removeList;

	int m_removedPieces;
	int m_dropedPieces;
	int m_preDropPieces;

	//check each checkerpiece number if it's equal to length of line.
	void checkColumnPiece(const int column);
	void checkRowPiece(const int row);
	
	void removePieces();
	void arrangePieceColumn(const int column);
	void breakRock(const Grid element);

	void guideView();

#ifdef DEBUGVIEW
	void DebugView();
	
	vector<CCLabelTTF*> Debuglabels;
#endif
};

#endif