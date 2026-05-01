#pragma once //evita doppia 
#include <vector>

/* partition */
template<typename T>
int partition(std::vector<T>& vec, int p, int r) {
	T x = vec[r];
	int i = p-1;
	for (int j=p; j<r; j++) {
		if (vec[j] <= x) {
			i+=1;
			//scambio vec[i] e vec[j]
			T tmp = vec[j];
			vec[j] = vec[i];
			vec[i] = tmp;
		}
	}
	//scambio vec[i+1] con vec[r]
	T tmp = vec[r];
	vec[r] = vec[i+1];
	vec[i+1] = tmp;
	return i+1;
}

/* quicksort */
template<typename T>
void quicksort(std::vector<T>& vec, int p, int r) {
	if (p < r) {
		int q = partition(vec, p, r);
		quicksort(vec, p, q-1);
		quicksort(vec, q+1, r);
	}
	return;
}