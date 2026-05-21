#include <iostream>
#include "grad_coniug.cpp"

int main()
{
    // Matrice simmetrica definita positiva
    Eigen::MatrixXd A(5,5);

    A <<  10, 2, 0, 0, 0,
          2, 9, 3, 0, 0,
          0, 3, 8, 1, 0,
          0, 0, 1, 7, 2,
          0, 0, 0, 2, 6;

    // Soluzione esatta scelta a priori
    Eigen::VectorXd x_exact(5);

    x_exact << 1, 2, 3, 4, 5;

    // Costruisco b = A*x_exact
    Eigen::VectorXd b = A * x_exact;

    // Risolvo con il gradiente coniugato da testare
    Eigen::VectorXd x = grad_coniug(A, b);

    // Errore rispetto alla soluzione esatta
    double errore = (x - x_exact).norm();

    std::cout << "Errore = " << errore << "\n";

    // Test
    if (errore < 1e-10)
    {
        std::cout << "TEST SUPERATO\n";
		return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "TEST FALLITO\n";
		return EXIT_FAILURE;
    }
}