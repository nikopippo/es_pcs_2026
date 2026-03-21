#include <iostream>

int main()
{
	static const int N = 7;
	double arr[N] = {1.5, -9.8, 4.5, -2.3, 1.7, 5.3, 2.9};
	// vedo quando cambio ordine
	int flag = 1;
	// stampo l'array prima di ordinarlo
	std::cout << "starter: ";
	for (int i = 0; i < N; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
	
	while (flag == 1) {
		flag = 0;
		// scorro l'array e scambio ordine
		for (int i=0; i<N-1; i++){
			if (arr[i]>arr[i+1]) {
				double tmp = arr[i];
				arr[i] = arr[i+1];
				
				arr[i+1] = tmp;
				// se cambio rientrerò nel while; basta che cambi una sola volta
				flag = 1;
			}	
		}	
	}
	std::cout << "sorted: ";
	for (int i = 0; i < N; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
	
	return 0;
}