#include <iostream>
#include <vector>
#include <algorithm>

#include "randfiller.h"
#include "timecounter.h"
#include "mergesort.hpp"
#include "quicksort.hpp"
#include "bubblesort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "super_quicksort.hpp"

// funzione che genera vettore lungo n con randfiller
randfiller rf;
std::vector<int> generate_vector(size_t n) {
    std::vector<int> v(n);
	rf.fill(v, -1000, 1000);
	
    return v;
}

int main() {

    timecounter tc;
	std::cout << "N,Bubble,Insertion,Selection,Quick,Merge,SuperQuick,StdSort;\n";
	
	//faccio test su vettore di 100 vettori di dimensioni da 1 a 100
	

    for (size_t n = 1; n <= 100; n++) {

		//definisco e riempio vettore di 100 vettori di dim n
        std::vector<std::vector<int>> base(100);
		
		for (int i=0; i<100; i++) {
			base[i] = generate_vector(n);
		}
		
        // faccio e misuro bubble-sort su copia
        std::vector<std::vector<int>> v1 = base;
        tc.tic();
		for (int j =0; j<100; j++) {
			bubblesort(v1[j]);
		}
        double t_bubble = tc.toc();		//salvo tempo
		t_bubble /= 100.0;		//faccio media

        // faccio e misuro insertion-sort
        std::vector<std::vector<int>> v2 = base;
        tc.tic();
		for (int j =0; j<100; j++) {
			insertionsort(v2[j]);
		}
        double t_insertion = tc.toc();
		t_insertion /= 100.0;

        // selection-sort
        std::vector<std::vector<int>> v3 = base;
        tc.tic();
        for (int j =0; j<100; j++) {
			selectionsort(v3[j]);
		}
        double t_selection = tc.toc();
		t_selection /= 100.0;
		
		// quick-sort
		std::vector<std::vector<int>> v4 = base;
		tc.tic();
		for (int j =0; j<100; j++) {
			quicksort(v4[j], 0, n-1);
		}
		double t_quick = tc.toc();
		t_quick /= 100.0;
		
		// merge-sort
		std::vector<std::vector<int>> v5 = base;
		tc.tic();
		for (int j =0; j<100; j++) {
			mergesort(v5[j], 0, n-1);
		}
		double t_merge = tc.toc();
		t_merge /= 100.0;
		
		// super_quicksort
		std::vector<std::vector<int>> v7 = base;
		tc.tic();
		for (int j =0; j<100; j++) {
			super_quicksort(v7[j], 0, n-1);
		}
		double t_super_quick = tc.toc();
		t_super_quick /= 100.0;
		
        // uso metodo sort libreria std
        std::vector<std::vector<int>> v6 = base;
        tc.tic();
		for (int j =0; j<100; j++) {
			std::sort(v6[j].begin(), v6[j].end());
		}
        double t_std = tc.toc();
		t_std /= 100.0;
		
        // printo risultati
        std::cout << n << " "  << t_bubble << " " << t_insertion << " " << t_selection << " " << t_quick << " " << t_merge << " " << t_super_quick << " " << t_std << ";" << "\n";
    }

    return 0;
}