#ifndef __CHECKERPIECE_H__
#define __CHECKERPIECE_H__

#include "cocos2d.h"
#include "CheckerBoard.h"

using namespace cocos2d;
struct Grid
{
	int x;
	int y;
	Grid(int in_x=0,int in_y=0):x(in_x),y(in_y){};
};

enum PieceType
{
EMPTY=0,
NUM=1,
ROCK=2
};
class CheckerBoard;

class CheckerPiece: public CCNode
{
	friend class CheckerBoard;
public:
	CheckerPiece():m_type(PieceType(0)),m_num(0),m_rock(0){};
	~CheckerPiece(){};
	void init(CheckerBoard* parent,Grid grid){m_parent=parent;m_grid=grid;};
	bool IsEmpty(){return m_type==PieceType(0);};
	bool IsRock(){return m_type==PieceType(2);};
	bool IsNum(){return m_type==PieceType(1);};
	int GetNum(){return m_num;};
	int GetRock(){return m_rock;};

	void SetSprite(cocos2d::CCSprite* sp){m_sp=sp;};
	Grid GetGrid(){return m_grid;};

	CheckerPiece& operator=(const CheckerPiece& rhs);


	void Clear();
	void onRemoveSprite(CCNode* node);
	void AddContent(int num,bool isRock);
	void BreakRock();
	
	
private:
	PieceType m_type;
	int m_num;
	int m_rock;
	cocos2d::CCSprite* m_sp;
	CheckerBoard* m_parent;
	Grid m_grid;


};





#endif