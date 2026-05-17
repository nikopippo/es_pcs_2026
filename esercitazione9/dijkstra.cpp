#include <map>
#include <limits>
#include "w_unidirected_edge.hpp"
#include "w_unidirected_graph.hpp"
#include <queue>

/*L'algoritmo di Dijkstra si usa nei grafi pesati per trovare il cammino minimo da un 
nodo sorgente a tutti gli altri nodi, quando i pesi degli archi sono non negativi.*/

template<typename T>
std::pair<std::map<T, double>, std::map<T, T>>	  //ritorno distanze e percorso
dijkstra(const w_unidirected_graph<T>& g, const T& source) {

    std::map<T, double> dist;		//per ogni nodo salva il costo minimo trovato dalla sorgente
    std::map<T, T> pred;		//salva da quale nodo sono arrivato nel cammino minimo.

    // inizializzazione
    for (const T& v : g.all_nodes()) {
        dist[v] = std::numeric_limits<double>::infinity();
        pred[v] = T(); // costruttore di default del tipo T(necessario per farlo funzionare anche con non int)
    }

    dist[source] = 0;
    pred[source] = source;

    // priority queue (uso quella della std scambiando ordine)
    std::priority_queue<std::pair<double, T>, std::vector<std::pair<double, T>>, std::greater<std::pair<double, T>> > pq;	//greater mi cambia ordine 
	
	for (const T& v : g.all_nodes()) {
		pq.push({dist[v], v});
	} 


    while (!pq.empty()) {

        auto [d, u] = pq.top();
        pq.pop();

        for (auto [v, w] : g.neighours(u)) {

            if (dist[v] > dist[u] + w) {

                dist[v] = dist[u] + w;
                pred[v] = u;

                pq.push({dist[v], v});
            }
        }
    }

	return {dist, pred};
}