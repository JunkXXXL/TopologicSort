#include "BoolVector.h"

void BoolVector::_shiftRight()
{
	unsigned char lostbit;
	for (int cell = _cells - 1; cell >= 0; cell--)
	{
		_data[cell] <<= 1;
		if (cell != 0)
		{
			lostbit = _data[cell - 1] & 128;
			lostbit = lostbit >> 7;
			_data[cell] |= lostbit;
		}
	}
	//_data[0] &= 127;
}

void BoolVector::_shiftLeft()
{
	unsigned char lostbit = 0;
	for (int cell = 0; cell < _cells; cell++)
	{
		_data[cell] >>= 1;
		if (cell != _cells - 1)
		{
			lostbit = _data[cell + 1] & 1;
			lostbit = lostbit << 7;
			_data[cell] |= lostbit;
		}
	}
	//setComponent(_len - 1, false);
}

BoolVector::BoolVector()
{
	_data = new unsigned char[1];
	_len = 0;
	_cells = 1;
}

BoolVector::BoolVector(const unsigned char* input)
{
	_len = 0;
	while (input[_len] != '\0')
	{
		if ((input[_len] != '1') && (input[_len] != '0'))
		{
			throw errorWrongSymbol;
		}
		_len++;
	}
	_cells = _len / 8;
	if (_len & (8 - 1)) _cells++; // bool(_len%8)

	_data = new unsigned char[_cells];
	for (int cell = 0; cell < _cells; cell++)
	{
		_data[cell] = 0;
		unsigned char mask = 1;
		for (int j = 0; j < 8 && cell * 8 + j < _len; j++)
		{
			if (input[cell * 8 + j] == '1')
			{
				_data[cell] |= mask;
			}

			mask <<= 1;
		}
	}
}

BoolVector::BoolVector(const char* input)
{
	_len = 0;
	while (input[_len] != '\0')
	{
		if ((input[_len] != '1') && (input[_len] != '0'))
		{
			throw errorWrongSymbol;
		}
		_len++;
	}
	_cells = _len / 8;
	if (_len & (8 - 1)) _cells++; // bool(_len%8)

	_data = new unsigned char[_cells];
	for (int cell = 0; cell < _cells; cell++)
	{
		_data[cell] = 0;
		unsigned char mask = 1;
		for (int j = 0; j < 8 && cell * 8 + j < _len; j++)
		{
			if (input[cell * 8 + j] == '1')
			{
				_data[cell] |= mask;
			}

			mask <<= 1;
		}
	}
}

BoolVector::BoolVector(const int input) ///////////////////////////////////////////////////////////////
{
	_len = 4 * 8;
	_cells = 4;
	_data = new unsigned char[_cells] {0};

	unsigned char mask1 = 0;
	int mask2 = 1;
	bool bit;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bit = mask2 & input;
			if (bit)
			{
				mask1 = 1;
				_data[i] |= mask1 << j;
			}
			mask2 <<= 1;
			mask1 = 0;
		}
	}
}

BoolVector::BoolVector(const BoolVector& vec)
{
	_len = vec._len;
	_data = new unsigned char[vec._cells];
	_cells = vec._cells;
	for (int i = 0; i < _cells; i++)
	{
		_data[i] = vec._data[i];
	}
}

BoolVector::BoolVector(const int len, bool type)
{
	_len = len;
	_cells = (len + 7) / 8;
	if (type) _data = new unsigned char[_cells] {1};
	else _data = new unsigned char[_cells] {0};
}

BoolVector::~BoolVector()
{
	delete[] _data;
}

void BoolVector::print() const
{
	for (int i = 0; i < _cells; i++)
	{
		unsigned char mask = 1;
		for (int j = 0; j < 8 && i * 8 + j < _len; j++)
		{
			std::cout << bool(mask & _data[i]);
			mask <<= 1;
		}
	}
	std::cout << "\n";
}

int BoolVector::getLen() const
{
	return _len;
}

void BoolVector::inverse()
{
	for (int i = 0; i < _cells; i++)
	{
		_data[i] = ~_data[i];
	}
}

void BoolVector::inverseComponent(const int pos)
{
	int cell = pos / 8;
	char mask = 1 << (pos % 8);
	int newValue = _data[cell];
	newValue ^= mask;
	_data[cell] = newValue;
}

void BoolVector::setComponent(const int pos, const bool value)
{
	int cell = pos / 8;
	char mask = 1 << (pos % 8);
	int newValue = _data[cell];
	if (value)
	{
		newValue |= mask;
	}
	else
	{
		mask = ~mask;
		newValue &= mask;
	}
	//newValue ^= mask;
	_data[cell] = newValue;
}

int BoolVector::countWeight() const
{
	int result = 0;
	unsigned char mask = 1;

	for (int i = 0; i < _cells; i++)
	{
		mask = 1;
		for (int j = 0; mask && j + i * 8 < _len; mask <<= 1)
		{
			result += bool(mask & _data[i]);
		}
	}

	return result;
}

bool BoolVector::operator[](const int pos) const
{
	bool to_ret;
	int cell = pos / 8;
	int element = pos % 8;
	if (cell < 0 || pos < 0)
	{
		throw errorWrongIndex;
	}
	if (pos >= 0)
	{
		to_ret = _data[cell] & (1 << element);
	}
	return to_ret;
}

BoolVector BoolVector::operator=(const BoolVector& vec)
{
	if (&vec == this) return *this;
	delete[] _data;
	_data = new unsigned char[vec._cells];
	_len = vec._len;
	_cells = vec._cells;
	for (int i = 0; i < vec._cells; i++)
	{
		_data[i] = vec._data[i];
	}
	return *this;
}

BoolVector BoolVector::operator&(const BoolVector& vec)
{
	const BoolVector& minimum = (vec._len > _len ? *this : vec);
	const BoolVector& maximum = (vec._len <= _len ? *this : vec);

	BoolVector to_ret = maximum;
	unsigned char value = 0;
	int shift = maximum._len - minimum._len;

	for (int i = shift; i < maximum._len; i++)
	{
		value |= minimum[i - shift] << i % 8;
		if (i % 8 == 7)
		{
			to_ret._data[i / 8] &= value;
			value = 0;
		}
	}
	to_ret._data[to_ret._cells - 1] &= value;
	return to_ret;
}

BoolVector BoolVector::operator|(const BoolVector& vec)
{
	BoolVector minimum, maximum;
	if (vec._len > _len)
	{
		maximum = vec;
		minimum = *this;
	}
	else
	{
		maximum = *this;
		minimum = vec;
	}

	BoolVector to_ret = maximum;
	unsigned char value = 0;
	int shift = maximum._len - minimum._len;

	for (int i = shift; i < maximum._len; i++)
	{
		value |= minimum[i - shift] << i % 8;
		if (i % 8 == 7)
		{
			to_ret._data[i / 8] |= value;
			value = 0;
		}
	}
	to_ret._data[to_ret._cells - 1] |= value;

	return to_ret;
}

BoolVector BoolVector::operator^(const BoolVector& vec)
{

	BoolVector minimum, maximum;
	if (vec._len > _len)
	{
		maximum = vec;
		minimum = *this;
	}
	else
	{
		maximum = *this;
		minimum = vec;
	}

	BoolVector to_ret = maximum;
	unsigned char value = 0;
	int shift = maximum._len - minimum._len;

	for (int i = shift; i < maximum._len; i++)
	{
		value |= minimum[i - shift] << i % 8;
		if (i % 8 == 7)
		{
			to_ret._data[i / 8] ^= value;
			value = 0;
		}
	}
	to_ret._data[to_ret._cells - 1] ^= value;

	return to_ret;
}

BoolVector BoolVector::operator~()
{
	BoolVector to_ret(*this);
	to_ret.inverse();
	return to_ret;
}

BoolVector BoolVector::operator<<(const int shift)
{
	BoolVector to_ret = *this;
	for (int i = 0; i < shift; i++)
	{
		to_ret._shiftLeft();
	}

	return to_ret;
}

BoolVector BoolVector::operator>>(const int shift)
{
	BoolVector to_ret = *this;
	for (int i = 0; i < shift; i++)
	{
		to_ret._shiftRight();
	}

	return to_ret;
}

std::ostream& operator<<(std::ostream& out, const BoolVector& vec)
{
	unsigned char mask;
	for (int i = 0; i < vec._cells; i++)
	{
		mask = 1;
		for (int j = 0; j < 8 && i * 8 + j < vec._len; j++)
		{
			if (vec._data[i] & mask) out << '1';
			else out << '0';
			mask <<= 1;
		}
	}
	return out;
}

std::istream& operator>>(std::istream& in, BoolVector& vec)
{
	std::string input;
	in >> input;

	BoolVector newVec(input.c_str());
	vec = newVec;
	return in;
}
