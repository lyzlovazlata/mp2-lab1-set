// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0)
    {
        throw - 1;
    }
    else
    {
        BitLen = len;
        MemLen = (bitsInTELEM + len - 1) >> bytesInTELEM; // учитываем случай когда длина меньше байта
        pMem = new TELEM[MemLen];

        for (int i = 0; i < MemLen; i++) pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0)
    {
        throw - 2;
    }
    else if (n >= BitLen)
    {
        throw - 3;
    }
    else
    {
            int MemIndex = n >> bytesInTELEM;
            return MemIndex;
    }

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0)
    {
        throw - 2;
    }
    else if (n >= BitLen)
    {
        throw - 3;
    }
    else
    {
         TELEM MemMask = TELEM(1) << (n & (bitsInTELEM - 1));
         return MemMask;
    }

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0)
    {
        throw - 2;
    }
    else if (n >= BitLen)
    {
        throw - 3;
    }
    else
    {
        pMem[n >> bytesInTELEM] |= GetMemMask(n); 
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0)
    {
        throw - 2;
    }
    else if (n >= BitLen)
    {
        throw - 3;
    }
    else
    {
        pMem[n >> bytesInTELEM] &= ~GetMemMask(n);
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0)
    {
        throw - 2;
    }
    else if (n >= BitLen)
    {
        throw - 3;
    }
    else
    {
        int takeBit;
        takeBit = pMem[n >> bytesInTELEM] & GetMemMask(n);
        if (takeBit != 0)
        {
            return int(1); // инт тут для наглядности, то есть я возвращаю именно чиселку
        }
        else
        {
            return int(0);
        }
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) return *this;

    delete[] pMem;

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i) pMem[i] = bf.pMem[i];

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this == &bf) return 1; // одинаковые указатели
    if (BitLen != bf.BitLen) return 0;

    // сравниваем все полностью (все равно на последнее слово, потому что у нас гарантированно одна длина
    for (int i = 0; i < MemLen ; ++i) {
        if (pMem[i] != bf.pMem[i]) return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (this == &bf) return 0; // одинаковые указатели
    if (BitLen != bf.BitLen) return 1;

    // сравниваем все полностью (все равно на последнее слово, потому что у нас гарантированно одна длина
    for (int i = 0; i < MemLen; ++i) {
        if (pMem[i] != bf.pMem[i]) return 1;
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int newLen;
    if (BitLen > bf.BitLen) {
        newLen = BitLen;
    }
    else {
        newLen = bf.BitLen;
    }
    // мы создадим поле БОЛЬШЕЙ длины
    TBitField result(newLen);
    
    // меньшее поле
    int minMemLen;
    if (MemLen < bf.MemLen) {
        minMemLen = MemLen;
    }
    else {
        minMemLen = bf.MemLen;
    }

    // складываем общую часть
    for (int i = 0; i < minMemLen; i++) {
        result.pMem[i] = pMem[i] | bf.pMem[i];
    }

    // копируем а та которая бОльшая - копируем из большего
    if (MemLen > bf.MemLen) {
        for (int i = minMemLen; i < MemLen; i++) {
            result.pMem[i] = pMem[i];
        }
    }
    else if (bf.MemLen > MemLen) {
        for (int i = minMemLen; i < bf.MemLen; i++) {
            result.pMem[i] = bf.pMem[i];
        }
    }

    return result;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{ 
    // ну тут все так же, только пришлось все таки брать БОЛЬШУЮ длину, что нелогично но ладно
    int newLen;
    if (BitLen > bf.BitLen) {
        newLen = BitLen;
    }
    else {
        newLen = bf.BitLen;
    }

    TBitField result(newLen);

    int minMemLen;
    if (MemLen < bf.MemLen) {
        minMemLen = MemLen;
    }
    else {
        minMemLen = bf.MemLen;
    }

    for (int i = 0; i < minMemLen; i++) {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }

    // все что дальше minMemLen и так останется нулями
    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);

    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = ~pMem[i];
    }

    // обнуляем "лишние" биты в последнем слове, если они выходят за BitLen
    int rem = BitLen & (bitsInTELEM - 1);
    if (rem != 0) {
        TELEM mask = (TELEM(1) << rem) - 1; // в этой масочке в младших рем позициях (незначимых) - 1
        result.pMem[MemLen - 1] &= mask; // обнуляем незначимые!!
    }

    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string s;
    istr >> s; // работаем со строчкой

    int len = s.length();
    bf = TBitField(len); // получили длину и создали поле

    for (int i = 0; i < len; i++)
    {
        if (s[i] == '1')
        {
            bf.SetBit(i);
        }
        else if (s[i] == '0')
        {
            bf.ClrBit(i);
        }
        else
        {
            throw - 4; // если вписали не то
        }
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i) == 1)
        {
            ostr << 1;
        }
        else
        {
            ostr << 0;
        }
    }
    return ostr;
}


