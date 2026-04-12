#include <iostream>
#include <vector>
#include <algorithm>

#include "randfiller.h"
#include "timecounter.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "selectionsort.h"

// funzione che genera vettore lungo n con randfiller
randfiller rf;
std::vector<int> generate_vector(size_t n) {
    std::vector<int> v(n);
	rf.fill(v, -1000, 1000);
	
    return v;
}

int main() {

    timecounter tc;
	std::cout << "N,Bubble,Insertion,Selection,StdSort\n";

    for (size_t n = 4; n <= 8192; n *= 2) {

        std::vector<int> base = generate_vector(n);

        // faccio e misuro bubble-sort su copia
        std::vector<int> v1 = base;
        tc.tic();
        bubblesort(v1);
        double t_bubble = tc.toc();		//salvo tempo

        // faccio e misuro insertion-sort
        std::vector<int> v2 = base;
        tc.tic();
        insertionsort(v2);
        double t_insertion = tc.toc();

        // selection-sort
        std::vector<int> v3 = base;
        tc.tic();
        selectionsort(v3);
        double t_selection = tc.toc();

        // uso metodo sort libreria std
        std::vector<int> v4 = base;
        tc.tic();
        std::sort(v4.begin(), v4.end());
        double t_std = tc.toc();

        // printo risultati
        std::cout << n << ","  << t_bubble << "," << t_insertion << "," << t_selection << "," << t_std << "\n";
    }

    return 0;
}