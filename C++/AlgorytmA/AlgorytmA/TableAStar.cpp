#include "stdafx.h"
#include "TableAStar.h"


CTableAStar::CTableAStar()
{
	m_oOL = new vector<CBlock*>();
	m_oCL = new vector<CBlock*>();
}


CTableAStar::~CTableAStar()
{
	
}

void CTableAStar::setTable(int a_iX, int a_iY)
{
	m_iX = a_iX;
	m_iY = a_iY;
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

void CTableAStar::addOL(int a_iX, int a_iY)
{
	m_oOL->push_back(&(m_poTable[a_iX][a_iY]));
}

void CTableAStar::removeOL(int a_iX, int a_iY)
{
	for (int i = 0; i < m_oOL->size(); i++)
	{
		if (m_oOL->at(i) == &(m_poTable[a_iX][a_iY]))
		{
			m_oOL->erase(m_oOL->begin() + i);
			break;
		}
	}
}

void CTableAStar::addCL(int a_iX, int a_iY)
{
	m_oCL->push_back(&(m_poTable[a_iX][a_iY]));
}

void CTableAStar::removeCL(int a_iX, int a_iY)
{
	for (int i = 0; i < m_oCL->size(); i++)
	{
		if (m_oCL->at(i) == &(m_poTable[a_iX][a_iY]))
		{
			m_oCL->erase(m_oCL->begin() + i);
			break;
		}
	}
}

CBlock* CTableAStar::findMinFFromOL()
{
	CBlock* oMinBlock = m_oOL->at(0);
	for (int i = 0; i < m_oOL->size(); i++)
	{
		if (oMinBlock->getF() >= m_oOL->at(i)->getF())
		{
			oMinBlock = m_oOL->at(i);
		}
	}
	return oMinBlock;
}


string CTableAStar::solve()
{
	CBlock* oTempBlock;
	m_oOL->push_back(m_poStartPoint);
	while (!m_oOL->empty)
	{
		oTempBlock = findMinFFromOL();
		removeOL(oTempBlock->getX(), oTempBlock->getY());
		addCL(oTempBlock->getX(), oTempBlock->getY());
		if (oTempBlock == m_poEndPoint)
		{
			break;
		}
	}


	return m_strPath;
}