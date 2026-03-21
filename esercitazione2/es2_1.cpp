#include <iostream>

int main()
{
	double ad[4] = {0.0, 1.1, 2.2, 3.3};
	float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
	int ai[3] = {0, 1, 2};
	int x = 1;
	float y = 1.1;
	
	// il puntatore va 4byte dopo y per [1] dove c'è x
	(&y)[1] = 0;
	std::cout << x << "\n";

	// stampo l'indirizzo di x e y e vicini per vedere indirizzo
	std::cout << "y:     " << &y << "\n";
	std::cout << "x:     " << &x << "\n";
	std::cout << "ai[0]: " << &ai[0] << "\n";
	std::cout << "ai[2]: " << &ai[2] << "\n";
	std::cout << "af[0]: " << &af[0] << "\n";
	std::cout << "af[1]: " << &af[1] << "\n";
	std::cout << "af[7]: " << &af[7] << "\n";
	std::cout << "ad[0]: " << &ad[0] << "\n";	

	return 0;
}