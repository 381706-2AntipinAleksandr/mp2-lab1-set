// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : tBitField(mp)
{
  if (mp < 0)
    throw(1);
  tMaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : tBitField(s.tBitField)
{
  tMaxPower = s.tMaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : tBitField(bf)
{
  tMaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return tBitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return tMaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  return tBitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  tBitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  tBitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  tMaxPower = s.tMaxPower;
  tBitField = s.tBitField;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if (tMaxPower == s.tMaxPower && tBitField == s.tBitField)
    return 1;
  else
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  if (tMaxPower == s.tMaxPower && tBitField == s.tBitField)
    return 0;
  else
    return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  if (tMaxPower >= s.tMaxPower)
  {
    TSet tmp(tMaxPower);
    tmp.tBitField = tBitField | s.tBitField;
    return tmp;
  }
  if (tMaxPower < s.tMaxPower)
  {
    TSet tmp(s.tMaxPower);
    tmp.tBitField = tBitField | s.tBitField;
    return tmp;
  }
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  tBitField.SetBit(Elem);
  return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  tBitField.ClrBit(Elem);
  return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  if (tMaxPower >= s.tMaxPower)
  {
    TSet tmp(tMaxPower);
    tmp.tBitField = tBitField & s.tBitField;
    return tmp;
  }
  if (tMaxPower < s.tMaxPower)
  {
    TSet tmp(s.tMaxPower);
    tmp.tBitField = tBitField & s.tBitField;
    return tmp;
  }
}

TSet TSet::operator~(void) // дополнение
{
  tBitField = ~tBitField;
  return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int temp;
  char ch;
  do
  {
    istr >> ch;
  } while (ch != '{');
  do
  {
    istr >> temp;
    s.InsElem(temp);
    do
    {
      istr >> ch;
    } while ((ch != ',') && (ch != '}'));
  } while (ch != '}');
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  int i, n;
  char ch = ' ';
  ostr << "{";
  n = s.GetMaxPower();
  for (i = 0; i < n; i++)
    if (s.IsMember(i))
    {
      ostr << ch << ' ' << i;
      ch = 'i';
    }
  ostr << " }";
  return ostr;
}
