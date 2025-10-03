#include "TSet.h"
#include <iostream>

class Lights {
protected:
    TSet* set;
public:

    Lights();
    Lights(const Lights& l);
    Lights& operator=(Lights& l);
    virtual ~Lights();

    TSet* getS();

    virtual bool isGreen() = 0;
    virtual bool isRed() = 0;
    virtual bool isYellow() = 0;
    virtual void pr() = 0;

};

class PLights : public Lights {

public:
    PLights();
    PLights(Lights& l);
    PLights& operator=(Lights& l);
    ~PLights();

    virtual bool isRed();
    virtual bool isGreen();
    virtual bool isYellow();
    virtual void pr();
};

class TLights : public Lights {
public:
    TLights();
    TLights(Lights& l);
    TLights& operator=(Lights& l);
    ~TLights();

    virtual bool isGreen();
    virtual bool isYellow();
    virtual bool isRed();
    virtual void pr();
};
