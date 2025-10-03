#include "Lights.h"

// сразу объ€сню идею: € заметила закономерность между светофорами
//  p:  r  r  g
//      |  |  |
//      v  v  v
//  t:  g  y  r
// то есть в принципе мы можем завести одно поле из трех штук и работать чисто с ним
// таки образом мы можем провер€ть только ќƒ»Ќ светофор и делать к ќЅќ»ћ одинаковый метод (в общем смотрите лучше далее)

//  LIGHTS

Lights::Lights() 
{
    set = new TSet(3);
    set->InsElem(0);
}

Lights::Lights(const Lights& l) 
{
    set = new TSet(*l.set);
}
Lights& Lights:: operator=(Lights& l) {
    if (this == &l) return *this;
    delete set;
    set = new TSet(*l.set);
    return *this;
}
Lights:: ~Lights() {
    delete set;
}

TSet* Lights:: getS() 
{
    return set;
}

// PLIGHTS

PLights:: PLights() : Lights() {};

PLights:: PLights(Lights& l) {
    set = new TSet(*l.getS());
}

PLights& PLights:: operator=(Lights& l) 
{
    if (this == &l) return *this;
    delete set;
    set = new TSet(*l.getS());

    return *this;
}

PLights:: ~PLights() {}

bool PLights:: isRed() {
    // 0,1 ind
    if (set->IsMember(0) || set->IsMember(1))
    {
        return true;
    }
    return false;
}

bool PLights::isGreen()
{
    // 2 ind
    if (set->IsMember(2))
    {
        return true;
    }
    return false;
}

bool PLights::isYellow()
{
    throw - 10;
}

void PLights:: pr()
{
    if (this->isRed())
    {
        std::cout << "Pedestrian is Red" << endl;
    }
    if (this->isGreen())
    {
        std::cout << "Pedestrian is Green" << endl;
    }
}

// TLIGHTS

TLights:: TLights() : Lights() {};

TLights:: TLights(Lights& l) 
{
    set = new TSet(*l.getS());
}

TLights& TLights:: operator=(Lights& l) {
    if (this == &l) return *this;
    delete set;
    set = new TSet(*l.getS());
    return *this;
}

TLights:: ~TLights() {}


bool  TLights:: isGreen()
{
    // 0 ind
    if (set->IsMember(0))
    {
        return true;
    }
    return false;
}

 bool TLights::isYellow()
{
    // 1 ind
    if (set->IsMember(1))
    {
        return true;
    }
    return false;
}

 bool TLights::isRed()
{
    // 2 ind
    if (set->IsMember(2))
    {
        return true;
    }
    return false;
}


 void TLights::pr() {
    if (this->isRed())
    {
        std::cout << "Traffic is Red" << endl;
    }
    if (this->isGreen())
    {
        std::cout << "Traffic is Green" << endl;
    }
    if (this->isYellow())
    {
        std::cout << "Traffic is Yellow" << endl;
    }
}