#pragma once	//evita ridefinizione
#include <iostream>
#include <string>	// stringhe confrontabili
#include <concepts> // serve per std::integral/floating_point
#include <algorithm> // per std::min e std::max

/* arco indiretto 
voglio che from sia sempre minore di true(tipo elementi comparabile) */
template<typename T>
requires requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;	//funziona con tutti i tipi con < definito per usare std::min e co
}  
class unidirected_edge{
private:
	T node_1;
	T node_2;

public:
	/* Costruttore user-definer */
	// pongo node_1 sempre minore di node_2
    unidirected_edge(T a, T b){
		node_1 = std::min(a,b);
		node_2 = std::max(a,b);
	}

	/* metodi from/to */
    const T& from() const {return node_1; }
    const T& to() const { return node_2; }
	
	/* operatore < */
	// confronta prima nodi minori (1) e se pareggio i 2
	bool operator<(const unidirected_edge& other) const {
        if (node_1 != other.node_1) {
            return node_1 < other.node_1;
        }
        return node_2 < other.node_2;
    }

    /* operatore di uguaglianza == */
    bool operator==(const unidirected_edge& other) const {
        return (node_1 == other.node_1 && node_2 == other.node_2);
    }
};

/* Operatore << per stampa arco */
template<typename T>
std::ostream&
operator << (std::ostream& os, const unidirected_edge<T>& edge) { 
	os << "[" << edge.from() << "-" << edge.to() << "]";
	return os;
}