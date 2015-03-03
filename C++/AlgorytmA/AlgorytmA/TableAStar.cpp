#include "stdafx.h"
#include "TableAStar.h"


CTableAStar::CTableAStar()
{
}


CTableAStar::~CTableAStar()
{
}

void CTableAStar::setTable(int a_iX, int a_iY)
{
	m_poTable = new CBlock*[a_iX]();
	for (int i = 0; i < a_iX; i++)
	{
		m_poTable[i] = new CBlock[a_iY]();
	}
}

void CTableAStar::setStart(int a_iX, int a_iY)
{
	m_poStartPoint = &(m_poTable[a_iX][a_iY]);
}

void CTableAStar::setEnd(int a_iX, int a_iY)
{
	m_poEndPoint = &(m_poTable[a_iX][a_iY]);
}

void CTableAStar::setWall(int a_iX, int a_iY)
{
	m_poTable[a_iX][a_iY].setCanMove(false);
}
