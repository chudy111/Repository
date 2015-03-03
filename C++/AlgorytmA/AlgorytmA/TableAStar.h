#pragma once
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
private:
	CBlock** m_poTable;
	CBlock* m_poStartPoint;
	CBlock* m_poEndPoint;
	vector <CBlock*> m_oOL;
	vector <CBlock*> m_oCL

};

