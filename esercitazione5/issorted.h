#include <vector>

template<typename T>

bool issorted(const std::vector<T>& vec) {
	if (vec.size() == 0) {
		return true;
	}
	bool cresce = true;
	bool decresce = true;
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i] < vec[i-1] && cresce){		//vettore decresce
			cresce = false;
		}			
		else if (vec[i] > vec[i-1] && decresce){	//vettore cresce
			decresce = false;
		}
	}
	return decresce||cresce;
}