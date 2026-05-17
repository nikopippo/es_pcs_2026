#include <iostream>
#include "w_unidirected_graph.hpp"
#include "w_unidirected_edge.hpp"
#include "dijkstra.cpp"
#include <fstream>
#include <set>
#include <utility>	//per pair

// funzione per salvare il grafo pesato in formato Graphviz
template<typename T>
void save_graphviz(const w_unidirected_graph<T>& g, const std::string& filename)
{
    std::ofstream out(filename);
    out << "graph G {\n";
    
    std::set<std::pair<T,T>> printed;	//salvo quello che stampo
    
    for (const T& u : g.all_nodes()) {
        for (const auto& [v, w] : g.neighours(u)) {
            std::pair<T,T> e1 = {u,v};
            std::pair<T,T> e2 = {v,u};
            
            if (!printed.count(e1) && !printed.count(e2)) {	//evito duplicati
                printed.insert(e1);
                out << "    " << u << " -- " << v << " [label=\"" << w << "\"];\n";
            }
        }
    }
    out << "}\n";
}

// funzione per salvare l'albero dei cammini minimi dall'output di dijkstra(dist e pred)
// uso solo il grafo pesato originale e pred
template<typename T>
void save_path_tree(const w_unidirected_graph<T>& g, const std::map<T, T>& pred, const std::string& filename)
{
    std::ofstream out(filename);
    out << "graph PathTree {\n";
    
    std::set<std::pair<T,T>> printed;	//salvo quello che stampo
    
    for (const T& node : g.all_nodes()) {
        if (pred.at(node) != node) {
            T parent = pred.at(node);
            std::pair<T,T> e = {parent, node};
            
            if (!printed.count(e) && !printed.count({node, parent})) {	//evito duplicati
                printed.insert(e);
                out << "    " << parent << " -- " << node << " [color=red, penwidth=2];\n";
            }
        }
    }
    out << "}\n";
}

int main() {
    // Creazione del grafo pesato
    w_unidirected_graph<int> g;
    
    g.add_edge(w_unidirected_edge<int>(0, 1, 4));
    g.add_edge(w_unidirected_edge<int>(0, 2, 2));
    g.add_edge(w_unidirected_edge<int>(1, 2, 1));
    g.add_edge(w_unidirected_edge<int>(1, 3, 5));
    g.add_edge(w_unidirected_edge<int>(2, 3, 8));
    g.add_edge(w_unidirected_edge<int>(2, 4, 10));
    g.add_edge(w_unidirected_edge<int>(3, 4, 2));
    g.add_edge(w_unidirected_edge<int>(3, 5, 6));
    g.add_edge(w_unidirected_edge<int>(4, 5, 3));
    
    // Dijkstra dal nodo 0
    auto [dist, pred] = dijkstra(g, 0);
    
    // Salva il grafo originale e l'albero dei cammini minimi
    save_graphviz(g, "dijkstra_graph.dot");
    save_path_tree(g, pred, "dijkstra_tree.dot");
    
    // Stampa risultati base
    std::cout << "Distanze dal nodo 0:\n";
    for (const auto& [node, distance] : dist) {
        std::cout << "  Nodo " << node << ": " << distance << "\n";
    }
    
    return 0;
}