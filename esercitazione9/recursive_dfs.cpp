#include <map>


/* Implemento l'algoritmo DFS ricorsivamente. Per non rifare reached ogni volta 
e mantenere gli input richiesti uso ricorsione dentro una funzione con gli input dati
 mantenendo la mappa reached. */

template<typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& g, const T& source) {

    unidirected_graph<T> tree;
    std::map<T, bool> reached;

    dfs_visit(g, source, reached, tree);

    return tree;
}

template<typename T>
void dfs_visit(const unidirected_graph<T>& g, const T& u, std::map<T, bool>& reached, unidirected_graph<T>& tree) {

    reached[u] = true;

    for (const T& v : g.neighours(u)) {

        if (!reached[v]) {
			
			std::cout << u << " -> " << v << std::endl;
            
			tree.add_edge(unidirected_edge<T>(u, v));
            dfs_visit(g, v, reached, tree);
        }
    }
}