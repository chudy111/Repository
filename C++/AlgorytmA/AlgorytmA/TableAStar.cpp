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
	for (int i = 0; i < a_iX; i++)
	{
		for (int j = 0; j < a_iY; j++)
		{
			m_poTable[i][j].setX(i);
			m_poTable[i][j].setY(j);
		}
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

void CTableAStar::addOL(CBlock* a_oBlock)
{
	m_oOL->push_back(a_oBlock);
}

void CTableAStar::addCL(CBlock* a_oBlock)
{
	m_oCL->push_back(a_oBlock);
}

void CTableAStar::removeOL(int a_iX, int a_iY)
{
	for (auto i = 0; i < m_oOL->size(); i++)
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
	for (auto i = 0; i < m_oCL->size(); i++)
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
	for (auto i = 0; i < m_oOL->size(); i++)
	{
		if (oMinBlock->getF() >= m_oOL->at(i)->getF())
		{
			oMinBlock = m_oOL->at(i);
		}
	}
	return oMinBlock;
}

void CTableAStar::setNeighbours()
{
	for (int i=0; i<m_iX; i++)
	{
		for (int j=0; j<m_iY; j++)
		{
			if (0 == i && 0 == j)
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j]));
			}
			else if ( m_iX-1 == i && 0 == j)
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j+1]));
			}
			else if ( m_iX-1 == i && m_iY-1 == j)
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j]));
			}
			else if ( 0 == i && m_iY-1 == j)
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j]));
			}
			else if (0 == i)
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j-1]));
			}
			else if (0 == j)
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j]));
			}
			else if (m_iX-1 == i)
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j]));
			}
			else if (m_iY-1 == j)
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j]));
			}
			else
			{
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i-1][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i][j+1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j-1]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j]));
				m_poTable[i][j].addNeighbour(&(m_poTable[i+1][j+1]));
			}


		}
	}

}


string CTableAStar::solve()
{
	CBlock* oTempBlock;
	m_oOL->push_back(m_poStartPoint);
	while (!m_oOL->empty())
	{
		oTempBlock = findMinFFromOL();
		removeOL(oTempBlock->getX(), oTempBlock->getY());
		addCL(oTempBlock->getX(), oTempBlock->getY());
		
		if (oTempBlock == m_poEndPoint)
		{
			printResult();
			break;
		}
		for (auto i = 0; i < oTempBlock->getNeighbours()->size(); i++)
		{	
			if (oTempBlock->getNeighbours()->at(i)->getX() == 3 && oTempBlock->getNeighbours()->at(i)->getY() == 8)
			{
				cout << "";
			}
			if (getCL(oTempBlock->getNeighbours()->at(i)) || !canMove(oTempBlock,oTempBlock->getNeighbours()->at(i)))
			{
				continue;
			}
			else if (!getOL(oTempBlock->getNeighbours()->at(i)))
			{
				addOL(oTempBlock->getNeighbours()->at(i));
				oTempBlock->getNeighbours()->at(i)->setParent(oTempBlock);
				oTempBlock->getNeighbours()->at(i)->calculateFGH(m_poEndPoint);
			}
			else
			{
				int iNewG = oTempBlock->getNeighbours()->at(i)->calculateNewG(oTempBlock);
				if (iNewG < oTempBlock->getNeighbours()->at(i)->getG())
				{
					oTempBlock->getNeighbours()->at(i)->setParent(oTempBlock);
					oTempBlock->getNeighbours()->at(i)->setG(iNewG);
					oTempBlock->getNeighbours()->at(i)->calculateNewF();
				}
			}

		}
	}
	return m_strPath;
}

bool CTableAStar::getCL(CBlock* a_oBlock)
{
	bool bResult = false;
	for (auto i = 0; i < m_oCL->size(); i++)
	{
		if (m_oCL->at(i) == a_oBlock)
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}

bool CTableAStar::getOL(CBlock* a_oBlock)
{
	bool bResult = false;
	for (auto i = 0; i < m_oOL->size(); i++)
	{
		if (m_oOL->at(i) == a_oBlock)
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}

void CTableAStar::printResult()
{
	CBlock* oTemp = m_poEndPoint;
	while (NULL != oTemp)
	{
		cout << oTemp->getX() << " - " << oTemp->getY() << " - " << oTemp->getF() <<  endl;
		oTemp = oTemp->getParent();
	}
}

bool CTableAStar::canMove(CBlock* a_oParent, CBlock* a_oBlock)
{
	bool bReturn = true;
	if (a_oBlock->getCanMove())
	{
		if (a_oBlock->getX() == 1 && a_oBlock->getY() == 7 && a_oParent->getX() == 0 && a_oParent->getY() == 6)
		{
			bReturn = bReturn;
		}
		if (a_oBlock->getX() == a_oParent->getX() + 1 && a_oBlock->getY() == a_oParent->getY() + 1)
		{
			if (!m_poTable[a_oParent->getX() + 1][a_oParent->getY()].getCanMove() || !m_poTable[a_oParent->getX()][a_oParent->getY() + 1].getCanMove())
			{
				bReturn = false;
			}
		}
		else if (a_oBlock->getX() == a_oParent->getX() + 1 && a_oBlock->getY() == a_oParent->getY() - 1)
		{
			if (!m_poTable[a_oParent->getX()][a_oParent->getY() - 1].getCanMove() || !m_poTable[a_oParent->getX() + 1][a_oParent->getY()].getCanMove())
			{
				bReturn = false;
			}
		}
		else if (a_oBlock->getX() == a_oParent->getX() - 1 && a_oBlock->getY() == a_oParent->getY() + 1)
		{
			if (!m_poTable[a_oParent->getX()][a_oParent->getY() + 1].getCanMove() || !m_poTable[a_oParent->getX() - 1][a_oParent->getY()].getCanMove())
			{
				bReturn = false;
			}
		}
		else if (a_oBlock->getX() == a_oParent->getX() - 1 && a_oBlock->getY() == a_oParent->getY() - 1)
		{
			if (!m_poTable[a_oParent->getX()][a_oParent->getY() - 1].getCanMove() || !m_poTable[a_oParent->getX() - 1][a_oParent->getY()].getCanMove())
			{
				bReturn = false;
			}
		}
	}
	else
	{
		bReturn = false;
	}
	

	return bReturn;
}