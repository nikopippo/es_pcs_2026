#include <vectot>

/* insertion-sort  */
template<typename T>

std::vector<T>& insertion_sort(std::vector<T>& vec) {
	for (int j = 1; j < vec.size(); j++) {
		T key = vec[j];
		int i = j-1;
		while (i >= 0 && vec[i] > key) {
			vec[i+1] = vec[i];
			i = i-1;
			}
		vec[i+1] = key;
		}
	return vec;
}