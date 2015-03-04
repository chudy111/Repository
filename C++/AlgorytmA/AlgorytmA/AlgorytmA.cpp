// AlgorytmA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TableAStar.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CTableAStar* oTable = new CTableAStar();
	oTable->setTable(6, 10);
	oTable->setStart(3, 2);
	oTable->setEnd(3, 8);
	oTable->setWall(1, 5);
	oTable->setWall(2, 5);
	oTable->setWall(3, 5);
	oTable->setWall(4, 5);
	oTable->setWall(4, 8);
	oTable->setWall(3, 7);
	oTable->setWall(2, 8);
	oTable->setNeighbours();
	oTable->solve();

	system("pause");
	return 0;
}

