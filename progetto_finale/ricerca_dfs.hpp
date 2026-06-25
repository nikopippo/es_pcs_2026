#pragma once
#include "unidirected_graph.hpp"
#include <vector>
#include <set>


// Funzione ricorsiva che ritorna true se trova il percorso tra u e v, false altrimenti.
// La funzione aggiorna il path e i nodi visitati in input.
template<typename T>
bool findpath(const unidirected_graph<T>& tree, const T& u, const T& v, 
              std::set<T>& visited, std::vector<T>& path) {
    
    // Segna il nodo u come visitato
    visited.insert(u);
    
    // Aggiungi u al percorso corrente
    path.push_back(u);

    // Caso base: abbiamo raggiunto la destinazione
    if (u == v) {
        return true;
    }

    // Esplora i vicini del nodo u nell'albero
    for (const T& n : tree.neighours(u)) {
        // Se il vicino non è stato ancora visitato
        if (visited.find(n) == visited.end()) {
            // Chiamata ricorsiva
            if (findpath(tree, n, v, visited, path)) {
                return true;
            }
        }
    }

    // Backtracking: se nessun vicino porta a v, rimuovi u dal percorso
    path.pop_back();
    return false;
}




// Dato un grafo e il suo albero dfs trova i cicli minimi
std::vector<std::vector<int>> get_fundamental_cycles(const unidirected_graph<int>& graph, const unidirected_graph<int>& tree) {
    
	std::vector<std::vector<int>> cycles;
    
    // Calcolo il coalbero C = graph - tree sfruttando l'operatore - di unididrected_graph
	// A ogni arco del coalbero corrisponde un ciclo minimo
    unidirected_graph<int> C = graph - tree;

    // Itero su tutti gli archi del coalbero
    for (const unidirected_edge<int>& edge : C.all_edges()) {
        int u = edge.from();
        int v = edge.to();

        std::set<int> visited;
        std::vector<int> path;

        // Trovo il percorso in tree tra gli estremi dell'arco (u, v)
        if (findpath(tree, u, v, visited, path)) {
            // path contiene il percorso lineare, es: [u, a, b, ..., v]
            
            // L'arco del coalbero che reinseriamo è (v, u)
            // Per rappresentare il ciclo correttamente, basta aggiungere di nuovo il nodo u alla fine del percorso.
            path.push_back(u);
            
            // Aggiungiamo la maglia completata (es: [u, a, b, ..., v, u])
            cycles.push_back(path);
        }
    }

    return cycles;
}