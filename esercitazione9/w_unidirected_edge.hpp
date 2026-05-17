#pragma once	//evita ridefinizione
#include <iostream>
#include <string>	// stringhe confrontabili
#include <concepts> // serve per std::integral/floating_point
#include <algorithm> // per std::min e std::max

/* Implementazione arco pesato inserendo essenziale(peso e piccole variazioni)
 da unidirected_edge.*/

/* arco indiretto 
voglio che from sia sempre minore di true(tipo elementi comparabile) */
template<typename T>
requires requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;	//funziona con tutti i tipi con < definito per usare std::min e co
}  
class w_unidirected_edge{
private:
	T node_1;
	T node_2;
	double weight;

public:
	/* Costruttore user-definer */
	// pongo node_1 sempre minore di node_2
    w_unidirected_edge(T a, T b, double w =1)
		:	node_1(std::min(a,b)),
			node_2(std::max(a,b)),
			weight(w) {}
	

	/* metodi from/to */
    const T& from() const {return node_1; }
    const T& to() const { return node_2; }
	double get_weight() const { return weight; }
	
	/* operatore < */
	// confronta prima nodi minori (1) e se pareggio i 2
	bool operator<(const w_unidirected_edge& other) const {
        if (node_1 != other.node_1) {
            return node_1 < other.node_1;
        }
        return node_2 < other.node_2;
    }

    /* operatore di uguaglianza == */
    bool operator==(const w_unidirected_edge& other) const {
        return (node_1 == other.node_1 && node_2 == other.node_2);
    }
};

/* Operatore << per stampa arco */
template<typename T>
std::ostream&
operator << (std::ostream& os, const w_unidirected_edge<T>& edge) { 
	os << "[" << edge.from() << "-" << edge.to() << "]";
	return os;
}