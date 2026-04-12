#include <iostream>
#include <vector>
#include <string>
#include "randfiller.h"
#include "issorted.h"
#include "selectionsort.h"

bool testRandom() {
    randfiller rf;  /* instantiate a randfiller */
	bool wrong = false;
			
    for (int i = 0; i < 100; i++) {
        std::vector<int> vi(rand() % 1000);  // dimensione casuale
        rf.fill(vi, -1000, 1000);

        selectionsort(vi);

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
    selectionsort(vs);
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
