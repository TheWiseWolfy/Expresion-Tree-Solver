#include <iostream>
#include "Header.h"

using namespace std;

int main() {

	cout << "Va rog introduceti o expresie.\n";
	Nod* T = creareArbore();


	cout << "Gradul arborelui este:\n";

	cout << gradArbore(T) << endl;

	cout << "Operanzi introdusi sunt\n";
	afisareOperanzi(T);
	cout << endl;

	cout <<"Rezultatul expresiei este: " <<treeCalculator(T);
	return 0;
}


