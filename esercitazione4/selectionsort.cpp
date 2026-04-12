#include <vector>

/* selection-sort */
template <typename T>

std::vector<T>& selection_sort(std::vector<T>& vec) {
	for (int i = 0; i < vec.size()-1; i++) {
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