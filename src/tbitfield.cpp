// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len >= 0)
	{
		BitLen = len;
		MemLen = len / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw(1);
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	if (pMem != NULL)
		delete []pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n > BitLen)
		throw(1);
	return n / (8 * sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n > BitLen)
		throw(1);
	int bit = n % (8 * sizeof(TELEM));
	return 1 << bit;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen)
		throw(1);
	int i = GetMemIndex(n);
	int bit = GetMemMask(n);
	pMem[i] = pMem[i] | bit;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen)
		throw(1);
	int i = GetMemIndex(n);
	int bit = GetMemMask(n);
	pMem[i] = pMem[i] & ~bit;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen)
		throw(1);
	int i = GetMemIndex(n);
	int bit = GetMemMask(n);
	return (pMem[i] & bit) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (pMem != bf.pMem)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		if (pMem)
			delete []pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	bool rez = true;
	if (BitLen != bf.BitLen || MemLen != bf.MemLen)
		rez = false;
	else
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				rez = false;
	}
	return rez;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	bool rez = true;
	if (BitLen != bf.BitLen || MemLen != bf.MemLen)
		return rez;
	else
	{
		for (int i = 0; i < (BitLen / (sizeof(int) * 8)); i++)
			if (pMem[i] != bf.pMem[i])
				return rez;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int less = BitLen;
	int more = bf.BitLen;
	int lessM = MemLen;
	int moreM = bf.MemLen;
	if (bf.BitLen < BitLen)
	{
		lessM = bf.MemLen;
		moreM = MemLen;
		less = bf.BitLen;
		more = BitLen;

	}
	TBitField tmp(more);
	for (int i = 0; i < lessM; i++)
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	if (BitLen > bf.BitLen)
		for (int i = lessM; i < MemLen; i++)
			tmp.pMem[i] = pMem[i];
	else
		for (int i = lessM; i < bf.MemLen; i++)
			tmp.pMem[i] = bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int less = BitLen;
	int more = bf.BitLen;
	int lessM = MemLen;
	int moreM = bf.MemLen;
	if (bf.BitLen < BitLen)
	{
		lessM = bf.MemLen;
		moreM = MemLen;
		less = bf.BitLen;
		more = BitLen;
	}
	TBitField tmp(more);
	for (int i = 0; i < lessM; i++)
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
	if (BitLen > bf.BitLen)
		for (int i = lessM; i < MemLen; i++)
			tmp.pMem[i] = 0;
	else
		for (int i = lessM; i < bf.MemLen; i++)
			tmp.pMem[i] = 0;
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField rez(BitLen);
	TELEM g = ~(TELEM(0));
	for (int i = 0; i < MemLen; i++)
		rez.pMem[i] = ~pMem[i];
	rez.pMem[MemLen - 1] &= g >> (MemLen * sizeof(TELEM) * 8 - BitLen);
	return rez;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0; 
	char ch;
	do 
	{ 
		istr >> ch; 
	} while (ch != ' ');
	while (1) 
	{ 
		istr >> ch;
		if (ch == '0') 
			bf.ClrBit(i++);
		else if (ch == '1') 
			bf.SetBit(i++); 
		else break; 
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
