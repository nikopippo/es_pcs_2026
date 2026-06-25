#pragma once	//evita ridefinizione
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>
#include "unidirected_edge.hpp"

/*Per definire la classe utilizzo un set di nodi e un set di archi.
I set sono insiemi di elementi unici ordinati. Questo mi evita problemi di duplicazione
di nodi e di archi e mantiene il tutto ordinato. La numerazione degli archi
all'interno del grafo viene data in base all'ordinamento intrinseco al set
*/
template<typename T>
class unidirected_graph {
private:
    std::set<T> nodes;
    std::set<unidirected_edge<T>> edges_set;

public:
    /* Costruttore di default */
    unidirected_graph()
		: nodes{}, edges_set{} // Inizializza entrambi come vuoti
	{}

    /* Costruttore di copia */
    unidirected_graph(const unidirected_graph& other) 
        : nodes(other.nodes), edges_set(other.edges_set) {}
		
	/* neighours: restituisce i vicini di un nodo */
    std::set<T> neighours(const T& node) const {
        std::set<T> nbs;
        for (const auto& e : edges_set) {	//scrittura breve per scorrere archi nel set
            if (e.from() == node) {
				nbs.insert(e.to());
			}
            else if (e.to() == node) {
				nbs.insert(e.from());
			}
        }
        return nbs;
    }

    /* add_edge: aggiunge un arco e aggiorna i nodi coinvolti */
    void add_edge(const unidirected_edge<T>& new_edge) {
        edges_set.insert(new_edge);
        // se nodi dell'arco sono nuovi 
		nodes.insert(new_edge.from());
        nodes.insert(new_edge.to());
    }

    /* all_edges: restituisce tutti gli archi in un set */
    std::set<unidirected_edge<T>> all_edges() const {
		return edges_set;
	}

    /* all_nodes: restituisce tutti i nodi sotto forma di vettore */
    std::vector<T> all_nodes() const {
		std::vector<T> v;
		v.reserve(nodes.size()); //alloco memoria subito per velocizzare
		for (const T& n : nodes) {
			v.push_back(n); // Aggiungo ogni arco del set nel vettore
		}		
        return v;
    }

    /* edge_number: restituisce l'indice dell'arco */
	//la numerazione degli archi all'interno del grafo viene data
	//in base all'ordinamento intrinseco al set(basato sul < di unidirected_edge)
    int edge_number(const unidirected_edge<T>& e) const {
        int i = 0;
        for (const unidirected_edge<T>& current : edges_set) {
            if (current == e) return i;	//se trovo arco ritorno
			// per come ho def edge è già ordinato(non serve controllare 2vv)
            i++;
        }
        return -1; // Non trovato
    }

    /* edge_at: restituisce l'arco alla posizione n */
    unidirected_edge<T> edge_at(size_t n) const {
        if (n >= edges_set.size()) {
			// genero errore e stampo un alert visibile
			throw std::out_of_range("Indice arco fuori dai limiti");
		}
        auto it = edges_set.begin();	//genero iteratore set
        std::advance(it, n);	// lo avanzo di n 
        return *it;
    }

    /* operator- Differenza tra grafi */
    unidirected_graph operator-(const unidirected_graph& other) const {
        unidirected_graph result;	//def risultato
        for (const unidirected_edge<T>& e : edges_set) {
            // Se l'arco non è presente nel grafo 'other', lo aggiungo al risultato
            if (other.edges_set.find(e) == other.edges_set.end()) {		//da def find se non trova da .end
                result.add_edge(e);	//aggiunge automaticamente nodi
            }
        }
        return result;
    }
};