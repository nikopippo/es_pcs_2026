#include <iostream>
#include <vector>
#include <string>

// Inclusione de file header del progetto
#include "reader.hpp"   // Lettura strutture dati CircuitData, Component e la funzione reader
#include "graph_visit.hpp"    // Funzioni di visita del grafo (contiene anche findpath template)
#include "de_pina.hpp"         // Contiene get_minimum_cycles_de_pina
#include "solver.hpp"          // Contiene solve_circuit e gradienteConiugato

using namespace std;

int main() {
    // Il file di input contenente la netlist del circuito
	std::string filename = "circuit.txt";
   
    // Creiamo la struttura dati principale che conterrà tutto il circuito
	CircuitData data;

	cout << "==================================================" << endl;
	cout << "   SIMULATORE DI CIRCUITI ELETTRICI (METODO MAGLIE) " << endl;
	cout << "==================================================" << endl;
	cout << "Lettura del file di netlist: " << filename << "..." << endl;

    // Chiamata al reader per caricare i dati ed inizializzare le strutture
	if (!reader(filename, data)) {
		cout << "Errore: Impossibile aprire o leggere il file." << endl;
		return EXIT_FAILURE;
    }

	// info generali
	cout << "Lettura completata con successo." << endl;
	cout << "Numero di nodi: " << data.graph.all_nodes().size() << endl;
	cout << "Numero di resistori: " << data.resistors.size() << endl;
	cout << "Numero di generatori: " << data.voltages.size() << endl;
	cout << "--------------------------------------------------" << endl;

    // Selezione dell'algoritmo di ricerca dei cicli da parte dell'utente
	int scelta = 0;
	cout << "Scegli l'algoritmo per la ricerca dei cicli fondamentali:" << endl;
	cout << "1) Ricerca tramite DFS" << endl;
	cout << "2) Algoritmo di De Pina" << endl;
	cout << "Inserisci il numero della scelta (1 o 2): ";
	cin >> scelta;
	
	// Controllo input utente 
	while (scelta != 1 && scelta != 2) {
		cout << "Scelta non valida. Inserisci 1 per DFS o 2 per De Pina: ";
		cin >> scelta;
    }

    // Inizializziamo vettore che conterrà la base dei cicli (maglie) finale
	std::vector<std::vector<int>> maglie;

    // Calcoliamo prima l'albero di copertura necessario a entrambi gli algoritmi
    // Usiamo graph_visit partendo dal primo nodo disponibile
	int nodo_radice = *(data.graph.all_nodes().begin());	//dereferenzio valore all'inizio
	unidirected_graph<int> dfs_tree = graph_visit<fifo<int>, int>(data.graph, nodo_radice);

	if (scelta == 1) {
		cout << "\n Esecuzione della ricerca cicli tramite DFS..." << endl;
        // Chiamiamo la funzione DFS
		maglie = get_fundamental_cycles(data.graph, dfs_tree);
    }
	else if (scelta == 2) {
		cout << "\n Esecuzione dell'algoritmo di De Pina..." << endl;
		// Chiamata all'algoritmo di De Pina con il template su findpath
		maglie = get_minimum_cycles_de_pina(data.graph, dfs_tree);
    }

	cout << "Numero di maglie indipendenti individuate: " << maglie.size() << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "RISULTATI:" << endl;
	cout << "--------------------------------------------------" << endl;

    // Risoluzione del circuito e stampa dei risultati a schermo
    // La funzione solve_circuit riceve le maglie trovate, indipendentemente dall'algoritmo usato,
    // assembla B, R, v, applica il Gradiente Coniugato e stampa l'output finale richiesto.
	solve_circuit(data, maglie);

	cout << "==================================================" << endl;
	cout << "Esecuzione terminata correttamente." << endl;
	cout << "==================================================" << endl;

	return 0;
}