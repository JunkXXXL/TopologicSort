#include "BoolMatrix.h"

BoolMatrix::BoolMatrix()
{
	_lines = 0;
	_rows = 0;
	_matrix = new BoolVector[0];
}

BoolMatrix::BoolMatrix(const int i, const int j)
{
	_rows = i;
	_lines = j;
	if (i <= 0 || j <= 0)
	{
		throw errorWrongIndex;
	}
	_matrix = new BoolVector[j];
	for (int line = 0; line < j; line++)
	{
		_matrix[line] = BoolVector(i, false);
	}
}

BoolMatrix::BoolMatrix(const unsigned char** matrix, int lines, int rows) ///
{
	if (lines < 0 || rows <= 0) throw errorWrongIndex;
	_lines = lines;
	_rows = rows;
	_matrix = new BoolVector[_lines];

	for (int i = 0; i < _lines; i++)
	{
		_matrix[i] = BoolVector(matrix[i]);
	}
}

BoolMatrix::BoolMatrix(const BoolMatrix& matrix)
{
	_rows = matrix._rows;
	_lines = matrix._lines;
	_matrix = new BoolVector[_lines];
	for (int i = 0; i < _lines; i++)
	{
		_matrix[i] = matrix._matrix[i];
	}
}

BoolMatrix::~BoolMatrix()
{
	delete[] _matrix;
}

int BoolMatrix::getLinesNumber() const
{
	return _lines;
}

int BoolMatrix::getRowsNumber() const
{
	return _rows;
}

int BoolMatrix::weight() const
{
	int to_ret = 0;
	for (int i = 0; i < _lines; i++)
	{
		to_ret += _matrix[i].countWeight();
	}
	return to_ret;
}

int BoolMatrix::weightLine(const int line) const
{
	if (line <= 0 || line >= _lines)
	{
		throw errorWrongIndex;
	}
	return _matrix[line].countWeight();
}

void BoolMatrix::inverseComponent(const int i, const int j)
{
	if (i <= 0 || j <= 0)
	{
		throw errorWrongIndex;
	}
	_matrix[i].inverseComponent(j);
}

void BoolMatrix::set(const int i, const int j, const bool value)
{
	if (i <= 0 || j <= 0)
	{
		throw errorWrongIndex;
	}
	_matrix[i].setComponent(j, value);
}

BoolVector BoolMatrix::conjunctAllLines()
{
	BoolVector to_ret(_rows, true);

	for (int i = 0; i < _lines; i++)
	{
		to_ret = to_ret & _matrix[i];
	}

	return to_ret;
}

BoolVector BoolMatrix::disjunctAllLine()
{
	BoolVector to_ret(_rows, false);

	for (int i = 0; i < _lines; i++)
	{
		to_ret = to_ret | _matrix[i];
	}

	return to_ret;
}

BoolMatrix BoolMatrix::operator=(const BoolMatrix& matrix)
{
	if (&matrix == this)
	{
		return *this;
	}
	_rows = matrix._rows;
	_lines = matrix._lines;

	delete[] _matrix;
	_matrix = new BoolVector[_lines];
	for (int i = 0; i < _lines; i++)
	{
		_matrix[i] = matrix._matrix[i];
	}
	return *this;
}

BoolVector& BoolMatrix::operator[](const int i)
{
	if (i < 0 || i >= _rows)
	{
		throw errorWrongIndex;
	}
	return _matrix[i];
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix& matrix)
{
	if (matrix._rows == _rows && matrix._lines == _lines)
	{
		BoolMatrix to_ret(_rows, _lines);
		for (int i = 0; i < _lines; i++)
		{
			to_ret._matrix[i] = _matrix[i] & matrix._matrix[i];
		}
		return to_ret;
	}
	throw errorWrongMatrixSizes;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& matrix)
{
	if (matrix._rows == _rows && matrix._lines == _lines)
	{
		BoolMatrix to_ret(_rows, _lines);
		for (int i = 0; i < _lines; i++)
		{
			to_ret._matrix[i] = _matrix[i] | matrix._matrix[i];
		}
		return to_ret;
	}
	throw errorWrongMatrixSizes;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& matrix)
{
	if (matrix._rows == _rows && matrix._lines == _lines)
	{
		BoolMatrix to_ret(_rows, _lines);
		for (int i = 0; i < _lines; i++)
		{
			to_ret._matrix[i] = _matrix[i] ^ matrix._matrix[i];
		}
		return to_ret;
	}
	throw errorWrongMatrixSizes;
}

BoolMatrix BoolMatrix::operator~()
{
		BoolMatrix to_ret(*this);
		for (int i = 0; i < _lines; i++)
		{
			to_ret._matrix[i].inverse();
		}
		return to_ret;
}

std::ostream& operator<<(std::ostream& out, const BoolMatrix& vec)
{
	unsigned char mask;
	for (int i = 0; i < vec._lines; i++)
	{
		for (int bits = 0; bits < vec._matrix[i].getLen(); bits++)
		{
			out << vec._matrix[i][bits];
		}
		out << "\n";
	}
	return out;
}

std::istream& operator>>(std::istream& in, BoolMatrix& vec)
{
	std::cout << "Input rows number: ";
	in >> vec._rows;
	while (vec._rows <= 0)
	{
		std::cout << "Wrong input";
		in >> vec._rows;
	}
	std::cout << "Input lines number: ";
	in >> vec._lines;
	while (vec._lines <= 0)
	{
		std::cout << "Wrong input";
		in >> vec._lines;
	}
	delete[] vec._matrix;
	vec._matrix = new BoolVector[vec._lines];

	std::string input;
	for (int i = 0; i < vec._lines; i++)
	{
		std::cout << "Input " << i+1 << " line: ";
		in >> input;
		vec._matrix[i] = BoolVector(input.c_str());
	}
	return in;
}
