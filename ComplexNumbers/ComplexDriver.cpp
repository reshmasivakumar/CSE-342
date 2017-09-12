// ComplexNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Complex.h"
using namespace std;

int main() {
	cout << "~~~ Complex numbers driver ~~~\n\n";

	Complex c0, c1(-4.24), c2(2, -3), c3;
//	cout << "(0 arg) c0: " << c0 << "\n(1 arg) c1: " << c1 << "\n(2 arg) c2: " << c2 << "\nconst i: " << i;
	cout << "\n\nInput real and imaginary parts for a complex number c3: ";
	cin >> c3;
	cout << "c3: " << c3 << endl << endl;

	cout << "c2 + c3: " << c2 + c3 << endl;
	cout << "c2 - c3: " << c2 - c3 << endl;
	cout << "c2 * c3: " << c2 * c3 << endl;
	cout << "c2 / c3: " << c2 / c3 << endl;
	cout << "c2 ==? c3: " << (c2 == c3 ? "yes" : "no") << endl << endl;

	return 0;
}
