#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include "BoolMatrix.h"

int _findVertexWithoutEffluent(BoolMatrix& matr)
{
	bool WithoutEffluent;
	for (int rows = 0; rows < matr.getRowsNumber(); rows++)
	{
		WithoutEffluent = true;
		for (int lines = 0; lines < matr.getLinesNumber(); lines++)
		{
			if (matr[lines][rows]) WithoutEffluent = false;
		}
		if (WithoutEffluent) return rows;
	}
	return -1;
}

bool _IsMatrixEmpty(BoolMatrix& matr)
{
	
	for (int i = 0; i < matr.getLinesNumber(); i++)
	{
		if (!matr[i][i]) return false;
	}
	return true;
}

void _deleteVertex(BoolMatrix& matr, int element)
{
	for (int pointer = 0; pointer < matr.getLinesNumber(); pointer++)
	{
		matr[element].setComponent(pointer, false);
	}
	matr[element].setComponent(element, true);
}

int* TopologicMatrixSort(BoolMatrix& matr)
{
	int* solution = new int[matr.getRowsNumber()];
	BoolMatrix copyMatr = matr;
	int vertexNum;
	int counter = 0;
	while (!_IsMatrixEmpty(copyMatr))
	{
		if (copyMatr.disjunctAllLine().countWeight() == copyMatr.getRowsNumber())  //
		{																	       //
			throw "Cycle was found";										       //
		}																	       //
		vertexNum = _findVertexWithoutEffluent(copyMatr);
		solution[counter] = vertexNum + 1;
		std::cout << vertexNum << "\n";
		_deleteVertex(copyMatr, vertexNum);
		counter++;
	}
	return solution;
}

int main00()
{
	BoolMatrix matr;
	std::cin >> matr;
	int* solution;

	solution = TopologicMatrixSort(matr);

	for (int i = 0; i < matr.getLinesNumber(); i++)
	{
		std::cout << solution[i];
	}
	delete[] solution;
	return 0;
}


//01111
//00000
//01000
//00100
//01010