#include <iostream>
#include <Eigen/Eigen/Dense>
#include <Eigen/Eigen/SVD>

Eigen::VectorXd grad_coniug(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const double tol_rel = 1.0e-15, const unsigned int it_max = 10000 ) 
{
  int n = A.rows();
  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);		// inizializzo x
  Eigen::VectorXd res = b - A * x;			// resto 
  Eigen::VectorXd p = res;		
  double res_norm_0 = res.norm();	//faccio copia residuo iniziale per tol
  
  unsigned int it = 0;
  const double res_tol = tol_rel;

  while (it < it_max && res.norm() > res_tol * res_norm_0)
  {
    const double alpha_k = ((p.transpose() * res) / (p.transpose() * A * p)).value();
	
	x = x + alpha_k * p;
    res = b - ( A * x);
	
	const double beta = ((p.transpose() * A *res) / (p.transpose() * A * p)).value();
	p = res - (beta*p);

    it++;
  }

  return x;
}
