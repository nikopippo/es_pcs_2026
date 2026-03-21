#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	static const int N = 4;
	double arr[N] = {-2.3, 1.7, 5.3, 2.9};
	// faccio min su array
	double min_arr = arr[0];
	for (int i=1; i<N; i++) {
		min_arr = min(arr[i], min_arr);
	}
	// faccio max su array
	double max_arr = arr[0];
	for (int i=1; i<N; i++) {
		max_arr = max(arr[i], max_arr);
	}
	
	// faccio deviazione standard vettore
	//ricavo media
	double media = 0.0;
	for (int i=0; i<N; i++) {
		media = media + arr[i];
	}
	media = media/N;
	// ricavo varianza e faccio radice
	double var_arr = 0.0;
	for (int i=0; i<N; i++) {
		var_arr = var_arr + ((arr[i]-media)*(arr[i]-media));
	}
	var_arr = var_arr/N;
	double stdev_arr = sqrt(var_arr);
	
	cout << "minimo : " << min_arr << "\n";	
	cout << "massimo: " << max_arr << "\n";	
	cout << "st.dev : " << stdev_arr << "\n";	

	return 0;
}