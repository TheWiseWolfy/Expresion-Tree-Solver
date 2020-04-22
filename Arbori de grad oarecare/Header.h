#pragma once


#define DIM_EXPR 100
#define GRMAX 10

typedef int Atom;

struct Nod {
    Atom data;          
    int grad;
    Nod* vDesc[GRMAX];
};

//1
int  gradArbore(Nod* radacina);
void afisareOperanzi(Nod* radacina);
bool isOperand(const char& S);
int treeCalculator(Nod* radacina);
///
Nod* creareArbore();
Nod* parse(char buffer[], int start, int end);
Nod* make_nod(int grad);