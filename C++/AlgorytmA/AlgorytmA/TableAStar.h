#pragma once
#include <string>
#include <iostream>
#include "Block.h"
#include <vector>
using namespace std;
class CTableAStar
{
public:
	CTableAStar();
	~CTableAStar();
	void setTable(int, int);
	void setWall(int, int);
	void setStart(int, int);
	void setEnd(int, int);
	void addOL(int, int);
	void addOL(CBlock*);
	void removeOL(int, int);
	void addCL(int, int);
	void addCL(CBlock*);
	void removeCL(int, int);
	void solve();
	CBlock* findMinFFromOL();
	void setNeighbours();
	bool getCL(CBlock*);
	bool getOL(CBlock*);
	void printResult(int);
	bool canMove(CBlock*, CBlock*);
	void printTempState();
private:
	CBlock** m_poTable;
	CBlock* m_poStartPoint;
	CBlock* m_poEndPoint;
	vector <CBlock*>* m_oOL;
	vector <CBlock*>* m_oCL;
	int m_iX;
	int m_iY;
	string m_strPath;
};

