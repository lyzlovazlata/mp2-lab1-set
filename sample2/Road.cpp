#include "Road.h"

Road:: Road() {
    pl = new PLights();
    tl = new TLights();
}

Road::Road(const Road& r) {
    pl = new PLights(*r.pl);
    tl = new TLights(*r.tl);
}

Road& Road:: operator=(Road& r) {
    if (this == &r) return *this;
    delete pl;
    delete tl;
    pl = new PLights(*r.pl);
    tl = new TLights(*r.tl);

    return *this;
}

Road:: ~Road() {
    delete pl;
    delete tl;
}

void Road::sw()
{
    if (tl->isGreen())
    {
        tl->getS()->DelElem(0);
        tl->getS()->InsElem(1);

        pl->getS()->DelElem(0);
        pl->getS()->InsElem(1);
    }
    else if (tl->isYellow())
    {
        tl->getS()->DelElem(1);
        tl->getS()->InsElem(2);

        pl->getS()->DelElem(1);
        pl->getS()->InsElem(2);
    }
    else if (tl->isRed())
    {
        tl->getS()->DelElem(2);
        tl->getS()->InsElem(0);

        pl->getS()->DelElem(2);
        pl->getS()->InsElem(0);
    }

}

Lights* Road:: Getpl()
{
    return pl;
}

Lights* Road::Gettl()
{
    return tl;
}