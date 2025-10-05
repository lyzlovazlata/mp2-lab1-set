#include "Road.h"



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