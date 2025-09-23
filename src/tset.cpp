// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    // воспользуемся методом битового поля тк он сам проверит границы и выбросит исключение
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0)
    {
        throw - 5;
    }
    if (Elem >= MaxPower)
    {
        throw - 6;
    }
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0)
    {
        throw - 5;
    }
    if (Elem >= MaxPower)
    {
        throw - 6;
    }
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this == &s) return *this;

    MaxPower = s.MaxPower;
    BitField = s.BitField;

    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (this == &s) return 1;

    if (MaxPower != s.MaxPower) return 0;

    if (BitField == s.BitField) return 1;
    else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (this == &s) return 0;

    if (MaxPower != s.MaxPower) return 1;

    if (BitField != s.BitField) return 1;
    else return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int newMax;
    if (MaxPower > s.MaxPower) newMax = MaxPower;
    else newMax = s.MaxPower;

    TSet result(newMax);

    // используем оператор или для битовых полей
    result.BitField = BitField | s.BitField;

    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0)
    {
        throw - 5;
    }
    if (Elem >= MaxPower)
    {
        throw - 6;
    }

    TSet result(*this);
    result.InsElem(Elem);

    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0)
    {
        throw - 5;
    }
    if (Elem >= MaxPower)
    {
        throw -6;
    }

    TSet result(*this);
    result.DelElem(Elem);

    return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    // опять же как сказали - делаем большее
    int newMax;
    if (MaxPower > s.MaxPower) newMax = MaxPower;
    else newMax = s.MaxPower;

    TSet result(newMax);

    result.BitField = BitField & s.BitField;

    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(MaxPower);

    result.BitField = ~BitField;

    return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    // отправляем в поле
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    // опять в поле
    ostr << s.BitField;
    return ostr;
}
