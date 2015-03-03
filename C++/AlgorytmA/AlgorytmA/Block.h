#pragma once
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
private:
	int m_iF;
	int m_iG;
	int m_iH;
	int m_iX;
	int m_iY;
	bool m_bCanMove;
};

