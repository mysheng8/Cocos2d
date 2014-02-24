#ifndef __CHECKERPIECE_H__
#define __CHECKERPIECE_H__

#include "cocos2d.h"
#include "CheckerBoard.h"

USING_NS_CC;
struct Grid
{
	int x;
	int y;
	Grid(int in_x=0,int in_y=0):x(in_x),y(in_y){};
	bool operator==(const Grid &rhs)
	{
		return x==rhs.x&&y==rhs.y;
	};
	bool operator!=(const Grid &rhs)
	{
		return x!=rhs.x&&y!=rhs.y;
	};
};

enum PieceType
{
EMPTY=0,
NUM=1,
ROCK=2,
BOMB=3
};

class CheckerBoard;

class CheckerPiece: public CCNode
{
public:
	CheckerPiece():m_type(PieceType(0)),m_num(0),m_rock(0),m_sp(0),jackpot_sp(0){};
	~CheckerPiece(){};
	void init(CheckerBoard* parent,Grid grid){m_parent=parent;m_grid=grid;};
	bool IsEmpty(){return m_type==PieceType(0);};
	bool IsRock(){return m_type==PieceType(2);};
	bool IsNum(){return m_type==PieceType(1);};
	bool IsBomb(){return m_type==PieceType(3);};
	int GetNum(){return m_num;};
	int GetRock(){return m_rock;};
	int GetType(){return (int)m_type;}
	void SetNum(const int num);

	void SetSprite(CCSprite* sp){m_sp=sp;};
	Grid GetGrid(){return m_grid;};

	CheckerPiece& operator=(const CheckerPiece& rhs);

	void Drop(const int dis);
	void Rise(const int dis);
	void Clear();
	void Explose();
	void onDropSprite();
	void onRemoveSprite();
	void onExplose();
	void AddContent(const int num,const bool isRock,const bool isBomb);
	void BreakRock();
	void Empty(){m_type=PieceType(0);m_sp=0;};
	void initJackpot();
	void clearJackpot();
	void clearSprite();

private:
	PieceType m_type;
	int m_num;
	int m_rock;
	CCSprite* m_sp;
	CheckerBoard* m_parent;
	Grid m_grid;
	CCSprite *jackpot_sp;
};





#endif	// __CHECKERPIECE_H__