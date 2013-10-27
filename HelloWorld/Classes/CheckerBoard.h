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
	~CheckerBoard();

	CheckerGame *m_parent;

	CheckerPiece* addPiece(const int column ,const int num,const bool isRock);
	CheckerPiece* getCheckerPiece(const Grid element); 
	CheckerPiece* getCheckerPiece(const int column,const int row);
	bool riseUp();
	int getHeight(const int column);
	void startLink(const Grid element);
	void onRemovedPieces(const Grid element);
	void onDropPieces();
	void onKillPiece(const Grid element);
	bool Decline();

private:
	
	CheckerPiece **content;
	
	vector<CheckerPiece*> removeList;

	int m_removedPieces;
	int m_dropedPieces;
	int m_preDropPieces;

	//check each checkerpiece number if it's equal to length of line.
	void checkColumnPiece(const int column);
	void checkRowPiece(const int row);
	void arrangePieceColumn(const int column);
	void breakRock(const Grid element);
	void removePieces();

	void guideView();
	vector<Grid> removeGrid;
	void DrawLink(bool horizontal);

#ifdef DEBUGVIEW
	void DebugView();
	
	vector<CCLabelTTF*> Debuglabels;
#endif
};

#endif //__CHECKERBOARD_H__