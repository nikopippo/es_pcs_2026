#include <iostream>
#include "graph_visit.cpp"
#include "unidirected_graph.hpp"
#include "recursive_dfs.cpp"
#include "fifo.hpp"
#include "lifo.hpp"
#include <fstream>
#include <set>
#include <utility>

// print grafo fai da te su dot formato graphviz
template<typename T>
void save_graphviz(const unidirected_graph<T>& g, const std::string& filename)
{
    std::ofstream out(filename);
    out << "graph G {\n";
    
    std::set<std::pair<T,T>> printed;	// salvo quello che stampo
    
    for (const T& u : g.all_nodes()) {
        for (const T& v : g.neighours(u)) {
            std::pair<T,T> e1 = {u,v};
            std::pair<T,T> e2 = {v,u};
            
            if (!printed.count(e1) && !printed.count(e2)) {	//evito duplicati
                printed.insert(e1);
                out << "    " << u << " -- " << v;
            }
        }
    }
    out << "}\n";
}


int main() {

    unidirected_graph<int> g;

	g.add_edge(unidirected_edge<int>(0,1));
	g.add_edge(unidirected_edge<int>(0,2));
	g.add_edge(unidirected_edge<int>(1,3));
	g.add_edge(unidirected_edge<int>(2,3));
	g.add_edge(unidirected_edge<int>(3,4));
	g.add_edge(unidirected_edge<int>(4,5));

    // BFS
    unidirected_graph<int> bfs_tree = graph_visit<fifo<int>, int>(g, 0);

    save_graphviz(bfs_tree, "bfs.dot");

    // DFS
    unidirected_graph<int> dfs_tree = graph_visit<lifo<int>, int>(g, 0);

    save_graphviz(dfs_tree, "dfs.dot");
	
	// DFS ricorsivo
	unidirected_graph<int> rec_dfs_tree = recursive_dfs<int>(g, 0);
	
	save_graphviz(rec_dfs_tree, "rec_dfs.dot");

    return 0;
}