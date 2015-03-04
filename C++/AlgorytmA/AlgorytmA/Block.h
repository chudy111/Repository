#pragma once
#include <vector>
#include <math.h>
using namespace std;
class CBlock
{
public:
	CBlock();
	CBlock(int, int);
	~CBlock();
	void setF(int);
	void setG(int);
	void setH(int);
	void setX(int);
	void setY(int);
	void setCanMove(bool);
	int getF();
	int getH();
	int getG();
	int getX();
	int getY();
	bool getCanMove();
	void addNeighbour(CBlock*);
	vector<CBlock*>* getNeighbours();
	CBlock* getParent();
	void setParent(CBlock*);
	void calculateFGH(CBlock*);
	int calculateNewG(CBlock*);
	void calculateNewF();
private:
	CBlock* m_oParent;
	vector<CBlock*>* m_oNeighbours;
	int m_iF;
	int m_iG;
	int m_iH;
	int m_iX;
	int m_iY;
	bool m_bCanMove;
};

