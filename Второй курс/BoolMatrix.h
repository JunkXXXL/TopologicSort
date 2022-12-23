#pragma once
#include "BoolVector.h"




class BoolMatrix
{
private:
	int _lines;
	int _rows;
	BoolVector *_matrix;

public:
	BoolMatrix();
	BoolMatrix(const int i, const int j);
	BoolMatrix(const unsigned char** matrix, int lines, int rows);
	BoolMatrix(const BoolMatrix& matrix);

	~BoolMatrix();

	int getLinesNumber() const;
	int getRowsNumber() const;
	int weight() const;
	int weightLine(const int line) const;
	void inverseComponent(const int i, const int j);
	void set(const int i, const int j, const bool value);
	BoolVector conjunctAllLines(); //&
	BoolVector disjunctAllLine(); //|

	friend std::ostream& operator<< (std::ostream& out, const BoolMatrix& vec);
	friend std::istream& operator>> (std::istream& in, BoolMatrix& vec);

	BoolMatrix operator= (const BoolMatrix& matrix);
	BoolVector& operator[] (const int i);
	BoolMatrix operator& (const BoolMatrix& matrix);
	BoolMatrix operator| (const BoolMatrix& matrix);
	BoolMatrix operator^ (const BoolMatrix& matrix);
	BoolMatrix operator~ ();
};