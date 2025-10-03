#include "Lights.h"

class Road {

    Lights* pl;
    Lights* tl;
public:
    Road();
    Road(const Road& r);
    Road& operator=(Road& r);
    ~Road();

    void sw();
    Lights* Getpl();
    Lights* Gettl();
};