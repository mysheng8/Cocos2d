#ifndef __CHECKERBOARD_H__
#define __CHECKERBOARD_H__

#include "cocos2d.h"
#include "CheckerPiece.h"
#include "GameLayer.h"
#include "GameSettingData.h"
#include <stdio.h>
#include <vector>
#include <list>


using namespace std;

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
	void breakRock(const Grid element);
	void onRemovedPieces(const Grid element,bool isBreakRock);
	void onDropPieces();
	bool Decline();
	void KillPieces(vector<Grid>::iterator begin, vector<Grid>::iterator end);
	void DestoryPieces(vector<Grid>::iterator begin, vector<Grid>::iterator end);
	void Explosion(const Grid element);
	void removePieces();
	//jackpot function
	void setJackpot();
	void clearJackpot();
	void ApplyJackpot();
	bool hasJackpot(CheckerPiece *p){return p==jackpot_p;};
	

private:
	
	CheckerPiece **content;

	CheckerPiece *jackpot_p;

	
	list<CheckerPiece*> removeList;

	int m_removedPieces;
	int m_dropedPieces;
	int m_preDropPieces;

	//check each checkerpiece number if it's equal to length of line.
	void checkColumnPiece(const int column);
	void checkRowPiece(const int row);
	void arrangePieceColumn(const int column);
	
	

	void guideView();
	vector<Grid> removeGrid;
	void DrawLink(bool horizontal);

	//Jackpot
	void initJackpot();
	
	
	

#ifdef DEBUGVIEW
	void DebugView();
	
	vector<CCLabelTTF*> Debuglabels;
#endif
};




#endif //__CHECKERBOARD_H__