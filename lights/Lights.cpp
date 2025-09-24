#include "TSet.h"
#include <iostream>

// сразу объ€сню идею: € заметила закономерность между светофорами
//  p:  r  r  g
//      |  |  |
//      v  v  v
//  t:  g  y  r
// то есть в принципе мы можем завести одно поле из трех штук и работать чисто с ним
// таки образом мы можем провер€ть только ќƒ»Ќ светофор и делать к ќЅќ»ћ одинаковый метод (в общем смотрите лучше далее)
class Lights {
protected:
	TSet* set;
public:

	Lights() {
		set = new TSet(3);
		set->InsElem(0);
	}

	TSet* getS() {
		return set;
	}

	virtual bool isGreen() = 0;
	virtual bool isRed() = 0;
	virtual bool isYellow() = 0;
	virtual void pr() = 0;
	
};

class PLights: public Lights {

public:
	PLights() : Lights() {};
		

	virtual bool isRed() {
		// 0,1 ind
		if (set->IsMember(0) || set->IsMember(1))
		{
			return true;
		}
		return false;
	}

	virtual bool isGreen() 
	{
		// 2 ind
		if (set->IsMember(2))
		{
			return true;
		}
		return false;
	}

	virtual bool isYellow() 
	{
		throw - 10;
	}

	virtual void pr() 
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
};

class TLights: public Lights {
public:
	TLights() : Lights() {};

	virtual bool isGreen()
	{
		// 0 ind
		if (set->IsMember(0))
		{
			return true;
		}
		return false;
	}
		
	virtual bool isYellow()
	{
		// 1 ind
		if (set->IsMember(1))
		{
			return true;
		}
		return false;
	}
		
	virtual bool isRed()
	{
		// 2 ind
		if (set->IsMember(2))
		{
			return true;
		}
		return false;
	}


	virtual void pr() {
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
};

class Road {

	Lights* pl;
	Lights* tl;
public:
	Road() {
		pl = new PLights();
		tl = new TLights();
	}

	void sw()
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

	Lights* Getpl()
	{
		return pl;
	}

	Lights* Gettl()
	{
		return tl;
	}
};

int main() {
	Road* r = new Road();
	r->Getpl()->pr();
	r->Gettl()->pr();
	std::cout << "NEXT" << endl;
	r->sw();

	r->Getpl()->pr();
	r->Gettl()->pr();
	std::cout << "NEXT" << endl;
	r->sw();

	r->Getpl()->pr();
	r->Gettl()->pr();
	std::cout << "NEXT" << endl;
	r->sw();

	r->Getpl()->pr();
	r->Gettl()->pr();
	std::cout << "NEXT" << endl;

	r->Getpl()->pr();
	r->Gettl()->pr();
	std::cout << "NEXT" << endl;
	r->sw();

	r->Getpl()->pr();
	r->Gettl()->pr();
	std::cout << "NEXT" << endl;
	r->sw();

	r->Getpl()->pr();
	r->Gettl()->pr();
	std::cout << "NEXT" << endl;

	delete r;
	return 0;
}