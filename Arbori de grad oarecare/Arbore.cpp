#include <iostream> 
#include "Header.h" 

using namespace std;

//Calculator

int treeCalculator(Nod* radacina) {
    int sum = 0, product = 1;
    for (int f1 = 0; f1 < radacina->grad; ++f1) {

        if (radacina->vDesc[f1] != nullptr) {
           
            if (isOperand(radacina->vDesc[f1]->data)) {

                if (radacina->data == '+') {
                    sum += (int)radacina->vDesc[f1]->data - 48;
                }
                else if (radacina->data == '*') {
                    product *= (int)radacina->vDesc[f1]->data - 48;
                }
            }
            else {
                radacina->vDesc[f1]->data = treeCalculator(radacina->vDesc[f1]);

                if (radacina->data == '+') {
                    sum += radacina->vDesc[f1]->data;
                }
                else if (radacina->data == '*') {
                    product *=radacina->vDesc[f1]->data;
                }
            }

        }
                
    }
    if (radacina->data == '+') {
        return sum;
    }
    else if (radacina->data == '*') {
        return product;
    }
}

//afisare operanzi

void afisareOperanzi(Nod* radacina){

    for (int f1 = 0; f1 < radacina->grad; ++f1) {
        if (radacina->vDesc[f1] != nullptr) {
            afisareOperanzi(radacina->vDesc[f1]);
        }
    }
    if (isOperand(radacina->data)) {
        // check back
        cout <<(int)radacina->data - 48 << " ";
    }
    return;
}

bool isOperand(const char& S) {
    if (S >= '0' && S <= '9') {
        return true;
    }

    return false;
}
//grad arbore recursiv

int gradArbore(Nod* nod) {

    static int max = 0;
    //Alegem un maxim din seria de functii recursive rulate in fiecare nod intern
    max = nod->grad > max ? nod->grad : max;


    for (int f1 = 0; f1 < nod->grad; ++f1) {
        if (nod->vDesc[f1] != nullptr) {
           gradArbore(nod->vDesc[f1]);
        }
    }
    return max;
}

Nod* creareArbore() {
    char buffer[DIM_EXPR];
    cin >> buffer;
    int length = strlen(buffer);
    Nod* n = parse(buffer, 0, length - 1);
    return n;
}

Nod* make_nod(int grad) {

	// ?? that looks not safe

	Nod* p = (Nod*) new char[sizeof(Nod) - (GRMAX - grad) * sizeof(Nod*)];   
	p->grad = grad;
	return p;
}

Nod* parse(char buffer[], int start, int end) {
    int openP = 0;
    int indici[GRMAX];
    int k = 0;
    openP = 0;
    for (int i = start; i <= end; i++) {
        if (buffer[i] == '(') openP++;
        if (buffer[i] == ')') openP--;
        if (buffer[i] == '+') {
            if (openP > 0) continue;
            indici[k++] = i;
        }
    }
    if (k > 0) {
        Nod* p = (Nod*) new char[sizeof(Nod) - (GRMAX - k + 1) * sizeof(Nod*)];
        p -> grad = k + 1;
        p -> data = '+';
        p -> vDesc[0] = parse(buffer, start, indici[0] - 1);
        for (int j = 1; j < p -> grad - 1; j++) {
            p -> vDesc[j] = parse(buffer, indici[j - 1] + 1, indici[j] - 1);
        }
        p -> vDesc[p -> grad - 1] = parse(buffer, indici[p -> grad - 2] + 1, end);
        return p;
    }
    openP = 0;
    for (int i = start; i <= end; i++) {
        if (buffer[i] == '(') openP++;
        if (buffer[i] == ')') openP--;
        if (buffer[i] == '*') {
            if (openP > 0) continue;
            indici[k++] = i;
        }
    }
    if (k > 0) {
        Nod* p = (Nod*) new char[sizeof(Nod) - (GRMAX - k + 1) * sizeof(Nod*)];
        p -> grad = k + 1;
        p -> data = '*';
        p -> vDesc[0] = parse(buffer, start, indici[0] - 1);
        for (int j = 1; j < p -> grad - 1; j++) {
            p -> vDesc[j] = parse(buffer, indici[j - 1] + 1, indici[j] - 1);
        }
        p -> vDesc[p -> grad - 1] = parse(buffer, indici[p -> grad - 2] + 1, end);
        return p;
    }
    if (buffer[start] == '(' && buffer[end] == ')') return parse(buffer, start + 1, end - 1);
    if (start == end)
        if (isdigit(buffer[start])) {
            Nod* p = (Nod*) new char[sizeof(Nod) - (GRMAX) * sizeof(Nod*)];
            p -> data = buffer[start];
            p -> grad = 0;
            return p;
        }
    printf("\nExpresia de intrare este eronata. Apasati o tasta");
    exit(1);
}