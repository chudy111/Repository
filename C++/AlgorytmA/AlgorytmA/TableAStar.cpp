#include "stdafx.h"
#include "TableAStar.h"


CTableAStar::CTableAStar()
{
	m_oOL = new vector<CBlock*>();
	m_oCL = new vector<CBlock*>();
}


CTableAStar::~CTableAStar()
{
	for (int i = 0; i < m_iY; i++)
	{
		delete m_poTable[i];
	}
	delete m_poTable;
	delete m_oOL;
	delete m_oCL;

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
	for (unsigned int i = 0; i < m_oOL->size(); i++)
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
	for (unsigned int i = 0; i < m_oCL->size(); i++)
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
	for (unsigned int i = 0; i < m_oOL->size(); i++)
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
	for (int i = 0; i<m_iX; i++)
	{
		for (int j = 0; j<m_iY; j++)
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


void CTableAStar::solve()
{
	CBlock* oTempBlock;
	addOL(m_poStartPoint);
	int iCounter = 0;
	while (!m_oOL->empty())
	{
		oTempBlock = findMinFFromOL();
		removeOL(oTempBlock->getX(), oTempBlock->getY());
		addCL(oTempBlock);
		iCounter++;
		if (oTempBlock == m_poEndPoint)
		{
			printResult(iCounter);
			return;
		}
		for (unsigned int i = 0; i < oTempBlock->getNeighbours()->size(); i++)
		{	
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
		/*if (oTempBlock->getX() == 5 && oTempBlock->getY() == 10)
		{
			printTempState();
		}*/
	}
	cout << "Brak rozwiazania" << endl;
	//printTempState();
	
	return;
}

bool CTableAStar::getCL(CBlock* a_oBlock)
{
	bool bResult = false;
	for (unsigned int i = 0; i < m_oCL->size(); i++)
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
	for (unsigned int i = 0; i < m_oOL->size(); i++)
	{
		if (m_oOL->at(i) == a_oBlock)
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}

void CTableAStar::printResult(int a_iCounter)
{
	CBlock* oTemp = m_poEndPoint;
	while (NULL != oTemp)
	{
		cout << oTemp->getX() << " - " << oTemp->getY() <<  endl;
		oTemp = oTemp->getParent();
	}
	cout << "Ilosc przejsc przez petle: " << a_iCounter << endl;
}

bool CTableAStar::canMove(CBlock* a_oBlock, CBlock* a_oNeighbour)
{
	bool bReturn = true;
	if (a_oNeighbour->getCanMove())
	{
		if (a_oNeighbour->getX() == a_oBlock->getX() + 1 && a_oNeighbour->getY() == a_oBlock->getY() + 1)
		{
			if (!m_poTable[a_oBlock->getX() + 1][a_oBlock->getY()].getCanMove() || !m_poTable[a_oBlock->getX()][a_oBlock->getY() + 1].getCanMove())
			{
				bReturn = false;
			}
		}
		else if (a_oNeighbour->getX() == a_oBlock->getX() + 1 && a_oNeighbour->getY() == a_oBlock->getY() - 1)
		{
			if (!m_poTable[a_oBlock->getX()][a_oBlock->getY() - 1].getCanMove() || !m_poTable[a_oBlock->getX() + 1][a_oBlock->getY()].getCanMove())
			{
				bReturn = false;
			}
		}
		else if (a_oNeighbour->getX() == a_oBlock->getX() - 1 && a_oNeighbour->getY() == a_oBlock->getY() + 1)
		{
			if (!m_poTable[a_oBlock->getX()][a_oBlock->getY() + 1].getCanMove() || !m_poTable[a_oBlock->getX() - 1][a_oBlock->getY()].getCanMove())
			{
				bReturn = false;
			}
		}
		else if (a_oNeighbour->getX() == a_oBlock->getX() - 1 && a_oNeighbour->getY() == a_oBlock->getY() - 1)
		{
			if (!m_poTable[a_oBlock->getX()][a_oBlock->getY() - 1].getCanMove() || !m_poTable[a_oBlock->getX() - 1][a_oBlock->getY()].getCanMove())
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

void CTableAStar::printTempState()
{
	for (int i = 0; i < m_iX; i++)
	{
		for (int j = 0; j < m_iY; j++)
		{
			cout << m_poTable[i][j].getX()+1 << " - " << m_poTable[i][j].getY()+1 << " - F: " << m_poTable[i][j].getF()
				<< " G: " << m_poTable[i][j].getG() << " H: " << m_poTable[i][j].getH(); 
			if (NULL != m_poTable[i][j].getParent())
				cout << " P: " << m_poTable[i][j].getParent()->getX() + 1 << "-" << m_poTable[i][j].getParent()->getY() + 1 << endl  << endl;
			else
				cout << endl;
		}
	}
	cout << "<<<<<<OL>>>>>>>" << endl;
	for (unsigned int i = 0; i < m_oOL->size(); i++)
	{
		cout << m_oOL->at(i)->getX() + 1 << "-" << m_oOL->at(i)->getY() + 1 << endl << endl;
	}
	cout << "<<<<<<CL>>>>>>>" << endl;
	for (unsigned int i = 0; i < m_oCL->size(); i++)
	{
		cout << m_oCL->at(i)->getX() + 1 << "-" << m_oCL->at(i)->getY() + 1 << endl << endl;
	}
}