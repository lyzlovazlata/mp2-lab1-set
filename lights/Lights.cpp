#include "TSet.h"

class Lights {
protected:
	TSet* set;
public:

	Lights() {
		set = new TSet(3);
		set = set + 0;
	}

	virtual bool isGreen() = 0;
	virtual bool isRed() = 0;
	virtual bool isYellow() = 0;
};

class PLights: public Lights {

public:
	PLights() : Lights() {};
		
	virtual bool isGreen() 
	{
		// 2 bit
		if (set->IsMember())
		{

		}

	}
	virtual bool isRed() = 0;
	virtual bool isYellow() = 0;
};

class TLights: public Lights {
public:
	TLights() : Lights() {};

	virtual bool isGreen() = 0;
	virtual bool isRed() = 0;
	virtual bool isYellow() = 0;
};

class Road {


};

int main() {
	return 1;
}