#ifndef __CHECKERBOARD_H__
#define __CHECKERBOARD_H__

#include "cocos2d.h"
#include "CheckerPiece.h"
#include "GameLayer.h"
#include "GameSettingData.h"
#include <stdio.h>
#include <vector>


using std::vector;

//#define DEBUGVIEW 

USING_NS_CC;

class CheckerPiece;
class GameLayer;
struct Grid;


class CheckerBoard
{
public:
	CheckerBoard(GameLayer *parent);  
	~CheckerBoard();

	GameLayer *m_parent;

	CheckerPiece* addPiece(const int column ,const int num,const bool isRock, const bool isBomb);
	CheckerPiece* getCheckerPiece(const Grid element); 
	CheckerPiece* getCheckerPiece(const int column,const int row);
	CheckerPiece* InsertPiece(const Grid element, const int num, const bool isRock, const bool isBomb);
	bool riseUp();
	int getHeight(const int column);
	void startLink(const Grid element,const bool isBomb);
	void onRemovedPieces(const Grid element);
	void onDropPieces();
	bool Decline();
	void KillPieces(vector<Grid>::iterator begin, vector<Grid>::iterator end);
	void Explosion(const Grid element);

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