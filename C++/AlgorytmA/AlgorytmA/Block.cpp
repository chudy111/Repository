#include "stdafx.h"
#include "Block.h"


CBlock::CBlock()
{
	m_iX = 0;
	m_iY = 0;
	m_bCanMove = false;
	m_iF = 0;
	m_iG = 0;
	m_iH = 0;
}

CBlock::CBlock(int a_iX, int a_iY)
{
	m_iX = a_iX;
	m_iY = a_iY;
	m_bCanMove = false;
	m_iF = 0;
	m_iG = 0;
	m_iH = 0;
}

CBlock::~CBlock()
{
}

bool CBlock::getCanMove()
{
	return m_bCanMove;
}

int CBlock::getF()
{
	return m_iF;
}

int CBlock::getG()
{
	return m_iG;
}

int CBlock::getH()
{
	return m_iH;
}

void CBlock::setCanMove(bool a_bCanMove)
{
	m_bCanMove = a_bCanMove;
}

void CBlock::setF(int a_iF)
{
	m_iF = a_iF;
}

void CBlock::setG(int a_iG)
{
	m_iG = a_iG;
}

void CBlock::setH(int a_iH)
{
	m_iH = a_iH;
}

void CBlock::setX(int a_iX)
{
	m_iX = a_iX;
}

void CBlock::setY(int a_iY)
{
	m_iY = a_iY;
}

int CBlock::getX()
{
	return m_iX;
}

int CBlock::getY()
{
	return m_iY;
}

void CBlock::addNeighbour(CBlock* a_oNeighbour)
{
	m_oNeighbours->push_back(a_oNeighbour);
}

vector<CBlock*>* CBlock::getNeighbours()
{
	return m_oNeighbours;
}

CBlock* CBlock::getParent()
{
	return m_oParent;
}

void CBlock::setParent(CBlock* a_oParent)
{
	m_oParent = a_oParent;
}
