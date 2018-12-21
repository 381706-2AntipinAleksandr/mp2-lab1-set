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
    tBitLen = len;
    tMemLen = len / (8 * sizeof(TELEM)) + 1;
    pMem = new TELEM[tMemLen];
    for (int i = 0; i < tMemLen; i++)
      pMem[i] = 0;
  }
  else
    throw(1);
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  tMemLen = bf.tMemLen;
  tBitLen = bf.tBitLen;
  pMem = new TELEM[tMemLen];
  for (int i = 0; i < tMemLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  if (pMem != NULL)
    delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n > tBitLen)
    throw(1);
  return n / (8 * sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n > tBitLen)
    throw(1);
  int bit = n % (8 * sizeof(TELEM));
  return 1 << bit;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return tBitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n > tBitLen)
    throw(1);
  int i = GetMemIndex(n);
  int bit = GetMemMask(n);
  pMem[i] = pMem[i] | bit;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n > tBitLen)
    throw(1);
  int i = GetMemIndex(n);
  int bit = GetMemMask(n);
  pMem[i] = pMem[i] & ~bit;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n > tBitLen)
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
    tBitLen = bf.tBitLen;
    tMemLen = bf.tMemLen;
    if (pMem)
      delete[]pMem;
    pMem = new TELEM[tMemLen];
    for (int i = 0; i < tMemLen; i++)
      pMem[i] = bf.pMem[i];
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  bool rez = true;
  if (tBitLen != bf.tBitLen || tMemLen != bf.tMemLen)
    rez = false;
  else
  {
    for (int i = 0; i < tMemLen; i++)
      if (pMem[i] != bf.pMem[i])
        rez = false;
  }
  return rez;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  bool rez = true;
  if (tBitLen != bf.tBitLen || tMemLen != bf.tMemLen)
    return rez;
  else
  {
    for (int i = 0; i < (tBitLen / (sizeof(int) * 8)); i++)
      if (pMem[i] != bf.pMem[i])
        return rez;
  }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int less = tBitLen;
  int more = bf.tBitLen;
  int lessM = tMemLen;
  int moreM = bf.tMemLen;
  if (bf.tBitLen < tBitLen)
  {
    lessM = bf.tMemLen;
    moreM = tMemLen;
    less = bf.tBitLen;
    more = tBitLen;

  }
  TBitField tmp(more);
  for (int i = 0; i < lessM; i++)
    tmp.pMem[i] = pMem[i] | bf.pMem[i];
  if (tBitLen > bf.tBitLen)
    for (int i = lessM; i < tMemLen; i++)
      tmp.pMem[i] = pMem[i];
  else
    for (int i = lessM; i < bf.tMemLen; i++)
      tmp.pMem[i] = bf.pMem[i];
  return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int less = tBitLen;
  int more = bf.tBitLen;
  int lessM = tMemLen;
  int moreM = bf.tMemLen;
  if (bf.tBitLen < tBitLen)
  {
    lessM = bf.tMemLen;
    moreM = tMemLen;
    less = bf.tBitLen;
    more = tBitLen;
  }
  TBitField tmp(more);
  for (int i = 0; i < lessM; i++)
    tmp.pMem[i] = pMem[i] & bf.pMem[i];
  if (tBitLen > bf.tBitLen)
    for (int i = lessM; i < tMemLen; i++)
      tmp.pMem[i] = 0;
  else
    for (int i = lessM; i < bf.tMemLen; i++)
      tmp.pMem[i] = 0;
  return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField rez(tBitLen);
  TELEM g = ~(TELEM(0));
  for (int i = 0; i < tMemLen; i++)
    rez.pMem[i] = ~pMem[i];
  rez.pMem[tMemLen - 1] &= g >> (tMemLen * sizeof(TELEM) * 8 - tBitLen);
  return rez;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char ch;
  for(int i = 0; i < bf.tBitLen; i++)
  {
    istr >> ch;
    if (ch == '0')
      bf.ClrBit(i);
    else if (ch == '1')
      bf.SetBit(i);
    else if (ch == ' ')
      break;
    else if (ch == '\n')
      break;
    else break;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.tBitLen; i++)
    ostr << bf.GetBit(i);
  return ostr;
}
