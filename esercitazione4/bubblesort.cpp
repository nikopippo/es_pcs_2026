#include <vector>
/* bubble-sort */
// agisco direttamente sul vettore e ritorno riferimento non creando copia
template<typename T>

std::vector<T>& bubble_sort(std::vector<T>& vec) {
	for (int i = 0; i < vec.size()-1; i++) {
		for (int j = vec.size()-1; j > i; j--) {
			if (vec[j]<vec[j-1]) {		//swap vec(j e vec(j-1))
				T tmp = vec[j];
				vec[j] = vec[j-1];
				vec[j-1] = tmp;
			}
		}
	}
	return vec;
}