#include <iostream>
#include <vector>
#include <string>
#include "randfiller.h"
#include "issorted.h"
#include "super_quicksort.hpp"

bool testRandom() {
    randfiller rf;  /* instantiate a randfiller */
	bool wrong = false;
			
    for (int i = 0; i < 100; i++) {
		int dim = rand() % 1000;
        std::vector<int> vi(dim);  // dimensione casuale
        rf.fill(vi, -1000, 1000);

        super_quicksort(vi, 0, dim-1);

		if (! issorted(vi)) {
			wrong = true;
		}
	}
	return !wrong;
}

bool testStrings() {
    std::vector<std::string> vs = {
        "cia", "bidet", "siepe", "cappa", "zattera",
		"fila",	"crispy", "mina", "police", "strutto"
    };
	
	bool wrong = false;
    super_quicksort(vs, 0, 9);
	if (!issorted(vs)) {
		wrong = true;
	}
	return !wrong;
}

int main(void)
{
	if (!testRandom()) return EXIT_FAILURE;
	if (!testStrings()) return EXIT_FAILURE;
	
	return EXIT_SUCCESS;
}