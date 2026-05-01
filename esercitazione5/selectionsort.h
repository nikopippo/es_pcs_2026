#include <vector>

/* selection-sort */
template <typename T>

std::vector<T>& selectionsort(std::vector<T>& vec) {
	for (size_t i = 0; i+1 < vec.size(); i++) {
		int min = i;
		for (int j = i+1; j < vec.size(); j++) {
			if (vec[j]<vec[min]) {
				min = j;
				}
			}
		T tmp = vec[min];
		vec[min] = vec[i];	//swap
		vec[i] = tmp;
		}
	return vec;
}