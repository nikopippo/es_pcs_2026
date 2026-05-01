#include <vector>
#include <limits>


/* merge  */
template<typename T>
void my_merge(std::vector<T>& vec, int p, int q, int r) {
	int n_1 = q-p+1;
	int n_2 = r-q;
	std::vector<T> L(n_1);		//inizializzo vettori con n_1-1 elementi (ho rimosso inf dello pseudocodice)
	std::vector<T> R(n_2);
	
	for (int i=0; i< n_1; i++) {
		L[i] = vec[p+i];
	}
	for (int j=0; j<n_2; j++) {
		R[j] = vec[q+1+j];
	}
	int i = 0;
	int j = 0;
	for (int k=p; k<=r; k++) {
		if (i == n_1) {
			vec[k] = R[j];
			j = j+1;
		}
		else if (j == n_2) {
			vec[k] = L[i];
			i = i+1;
		}
		else {
			if ( L[i] <= R[j] ) {
				vec[k] = L[i];
				i = i+1;
			}
			else {
				vec[k] = R[j];
				j = j+1;
			}	
		}
	}
	return;
}


/* merge-sort  */
template<typename T>
void mergesort(std::vector<T>& vec, int p, int r) {		//uso void perchè agisco già sul vettore
	if ( p < r ) {
		int q = (p+r)/2;	//per def / arrotonda a int inferiore
		mergesort(vec, p, q);
		mergesort(vec, q+1, r);
		my_merge(vec, p, q, r);	//ho omonimia con merge se includo algorithm
	}
	return;
}
