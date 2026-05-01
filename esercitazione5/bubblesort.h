#include <vector>
/* bubble-sort */
// agisco direttamente sul vettore e ritorno riferimento non creando copia
template<typename T>

std::vector<T>& bubblesort(std::vector<T>& vec) {
	for (size_t i = 0; i+1 < vec.size(); i++) {
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