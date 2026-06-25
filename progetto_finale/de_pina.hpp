#pragma once	//evita ridefinizione
#include <vector>
#include <utility> // per std::pair
#include "unidirected_graph.hpp"
#include "fifo.hpp"
#include "graph_visit.hpp"
#include "ricerca_dfs.hpp"

// Prodotto scalare modulo 2
int scalar_product_mod2(const std::vector<int>& a, const std::vector<int>& b) {
    int sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += a[i] * b[i];
    }
    return sum % 2;
}

// XOR bit a bit
void xor_in_place(std::vector<int>& target, const std::vector<int>& source) {
    for (int i = 0; i < target.size(); i++) {
        target[i] = target[i] ^ source[i];
    }
}

std::vector<std::vector<int>> get_minimum_cycles_de_pina(const unidirected_graph<int>& graph, const unidirected_graph<int>& tree) {
	
	int m = graph.all_edges().size();
	unidirected_graph<int> C = graph - tree; 	
    int k = C.all_edges().size(); 	//numero archi grafo-albero = num cicli minimi (E-V +1)

	// Inizializzazione Vettori di Supporto S. Ogni riga parte con un singolo arco attivo (1).
	// Questa matrice guida la ricerca: impone i passaggi obbligati per 
	// evitare di trovare cicli doppi o combinazioni lineari di cicli già estratti.
    std::vector<std::vector<int>> S(k, std::vector<int>(m, 0));	 
    int s_idx = 0;
    for (const unidirected_edge<int>& edge : C.all_edges()) {	//scorro su archi coalbero
        int e_num = graph.edge_number(edge);
        S[s_idx][e_num] = 1; 
        s_idx++;
    }

    std::vector<std::vector<int>> minimal_cycles; 

    for (int i = 0; i < k; i++) {	//scorro sul numero dei cicli minimi
        
        // FASE 1: Costruzione del grafo liftato G'
        unidirected_graph<std::pair<int, int>> G_prime;
        
        for (const unidirected_edge<int>& edge : graph.all_edges()) {	//scorro archi del grafo iniziale
            int u = edge.from();
            int v = edge.to();
            int e_idx = graph.edge_number(edge);
            
            std::pair<int, int> u_plus = {u, 0};
            std::pair<int, int> u_minus = {u, 1};
            std::pair<int, int> v_plus = {v, 0};
            std::pair<int, int> v_minus = {v, 1};

            if (S[i][e_idx] == 1) {
                // Arco attivo: metto arco nel liftato da + a - e da - a +
                G_prime.add_edge(unidirected_edge<std::pair<int, int>>(u_plus, v_minus));
                G_prime.add_edge(unidirected_edge<std::pair<int, int>>(u_minus, v_plus));
            } else {
                // Arco inattivo: si mantiene sullo stesso livello
                G_prime.add_edge(unidirected_edge<std::pair<int, int>>(u_plus, v_plus));
                G_prime.add_edge(unidirected_edge<std::pair<int, int>>(u_minus, v_minus));
            }
        }

        int min_weight = 2 * (graph.all_nodes()).size(); //il cammino max è pari al numero dei nodi
        std::vector<int> best_C_vector; 
        std::vector<int> best_C_nodes; 
		
		// Per cercare cammino in G' prendo solo i nodi collegati dal+ al - ,ovvero quelli per cui devono necessariamente passare i cicli minimi
		// Questo abbatte la complessità computazionale del prossimo passaggio
		std::set<int> candidate_nodes;
		for (const unidirected_edge<int>& edge : graph.all_edges()) {
			int e_idx = graph.edge_number(edge);
			if (S[i][e_idx] == 1) {
				candidate_nodes.insert(edge.from());
				candidate_nodes.insert(edge.to());
				}
		}

        // FASE 2: Ricerca del cammino minimo in G' per ogni nodo
        for (int start_v : candidate_nodes) {
            
            std::pair<int, int> start_state = {start_v, 0}; // v^+
            std::pair<int, int> end_state = {start_v, 1};   // v^-

            // Uso la funzione generica con il contenitore fifo (BFS)
            // graph_visit restituisce l'albero di esplorazione BFS
            unidirected_graph<std::pair<int, int>> bfs_tree = graph_visit<fifo<std::pair<int, int>>, std::pair<int, int>>(G_prime, start_state);

            std::set<std::pair<int, int>> visited;
            std::vector<std::pair<int, int>> path_pairs;

            // Uso findpath sull'albero BFS appena ottenuto per estrarre il percorso esatto
            if (findpath(bfs_tree, start_state, end_state, visited, path_pairs)) {
                
                // Ricostruisco il ciclo nel grafo originale e ne calcolo il peso
                std::vector<int> C_v_vector(m, 0);
                std::vector<int> path_nodes;
                int weight = 0; 	//numero archi nel cammino -> ciclo min
                
                for (int p = 0; p < path_pairs.size(); p++) {
                    path_nodes.push_back(path_pairs[p].first); // Estraggo il nodo
                }

                for (int p = 0; p < path_nodes.size() - 1; p++) {
                    unidirected_edge<int> e(path_nodes[p], path_nodes[p+1]);
                    int idx = graph.edge_number(e);
                    if (C_v_vector[idx] == 0) {
                        C_v_vector[idx] = 1;
                        weight++;
                    }
                }

                if (weight < min_weight) {	//cerco sempre ciclo minimo
                    min_weight = weight;
                    best_C_vector = C_v_vector;		//vettore che ha 1 in posizione j se l'arco j appartiene al ciclo
                    best_C_nodes = path_nodes;		//aggiorno migliore ciclo (salvato come vector nodi)
                }
            }
        } 

        minimal_cycles.push_back(best_C_nodes);

        // FASE 3: Ortogonalizzazione
        for (int j = i + 1; j < k; j++) {	// scorro dai cicli trovati ai cicli totali (solo sui mancanti)
            if (scalar_product_mod2(best_C_vector, S[j]) == 1) {
                xor_in_place(S[j], S[i]);
            }
        }
    } 

    return minimal_cycles;
}