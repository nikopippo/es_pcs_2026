#pragma once	//evita ridefinizione
#include <vector>
#include <map>
#include <set>
#include "unidirected_graph.hpp"
#include "lifo.hpp"
#include "fifo.hpp"

/*Implemento di seguito gli algoritmi di visita di grafi DFS e BFS sfruttando
 template sul container da utilizzare:
-queue(fifo) --> BFS ampiezza
-stack(lifo) --> DFS profondità*/


template<typename Container, typename T>
unidirected_graph<T> graph_visit(const unidirected_graph<T>& g, const T& source) {
	
	unidirected_graph<T> tree;		//inizializzo albero finale
	
    std::map<T,bool> reached;	//faccio map per farlo runnare anche con nodi non int
	
	std::vector<T> nodes = g.all_nodes();
	
	int n = nodes.size();
	
	for (int i=0; i<n; i++) {
		reached[nodes[i]] = false;
	}
    
	Container container;
    container.put(source);
	reached[source] = true;
	
    while (!container.empty()) {

        T u = container.get();

        for (const T& v : g.neighours(u)) {

            if (!reached[v]) {
				reached[v] = true;
                container.put(v);
				//creo edge e aggiungo al nuovo albero
				unidirected_edge<T> edge(u, v);
                tree.add_edge(edge);
            }
        }
    }

    return tree;
}