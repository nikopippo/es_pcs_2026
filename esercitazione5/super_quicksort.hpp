#include <vector>
#include "quicksort.hpp" //per partition

/* Documentation
Visto che da vari test sulle velocità di vari algoritmi di sorting 
risulta che il più veloce è l'insertion-sort quando il 
numero di elementi è minore di 30-50 e poi il quicksort, creo versione
combinata per avere tempo minore per ogn lunghezza di vettore*/

/* insertion-sort  */
// ho versione modificata con p e r per pulizia
template<typename T>
void new_insertionsort(std::vector<T>& vec, int p, int r) {
	for (int j = p+1; j <= r ; j++) {
		T key = vec[j];
		int i = j-1;
		while (i >= p && vec[i] > key) {
			vec[i+1] = vec[i];
			i = i-1;
			}
		vec[i+1] = key;
	}
	return;
}

/* super-quicksort */
// quicksort che usa insertionsort sotto un certo n0
constexpr int n0 = 50;
template<typename T>
void super_quicksort(std::vector<T>& vec, int p, int r) {
    
	if (p >= r) return;

    if (r - p <= n0) {
        new_insertionsort(vec, p, r);
        return;
    }
	// se r-p>n0 divido vettore con partition e riprovo
    int q = partition(vec, p, r);
    super_quicksort(vec, p, q - 1);
    super_quicksort(vec, q + 1, r);
}