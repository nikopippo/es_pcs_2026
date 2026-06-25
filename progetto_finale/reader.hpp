#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "CircuitData.hpp"

// Funzione di confronto esterna per i componenti (input per std::sort)
// Ritorna true se il componente 'a' deve precedere 'b' nell'ordinamento lessicografico degli archi.
bool compareResistors(const Component& a, const Component& b) {
    // Per ogni componente individuiamo il nodo con indice minore e quello con indice maggiore
    int min_a = (a.original_node1 < a.original_node2) ? a.original_node1 : a.original_node2;
    int max_a = (a.original_node1 > a.original_node2) ? a.original_node1 : a.original_node2;

    int min_b = (b.original_node1 < b.original_node2) ? b.original_node1 : b.original_node2;
    int max_b = (b.original_node1 > b.original_node2) ? b.original_node1 : b.original_node2;

    // Regola 1: Ordina prima in base al nodo minore dell'arco
    if (min_a != min_b) {
        return min_a < min_b;
    }
    // Regola 2: In caso di parità del nodo minore, ordina in base al nodo maggiore
    return max_a < max_b;
}

// Funzione principale di lettura del circuito
bool reader(const std::string& filename, CircuitData& data) {
    // Apertura del file tramite stream di input
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Errore: Impossibile aprire " << filename << "\n";  //sputo errore se non apro file
        return false;
    }

    // Variabili locali per estrarre i dati riga per riga
    std::string comp_name;
    double value;
    int n1, n2;

    // Lettura standard: l'operatore >> estrae i dati ignorando automaticamente spazi e /n.
    // Il ciclo termina non appena si raggiunge la fine del file (EOF) o un errore di formato.
    while (file >> comp_name >> value >> n1 >> n2) {
        
        Component c;
        c.value = value;
        c.original_node1 = n1;
        c.original_node2 = n2;

        // comp_name contiene stringhe come "R1" o "V12".
        // Sappiamo che comp_name[0] è la lettera, mentre i caratteri successivi sono cifre.

        // Estraiamo la sottostringa a partire dal carattere 1 (saltando la 'R' o la 'V' in posizione 0)
        // e la convertiamo direttamente in un intero col comando stoi (string to int) dalla std. 
        int calcolo_id = std::stoi(comp_name.substr(1));	//substr estrae sottostringa da 1 in poi
        c.id = calcolo_id;

        // Creazione dell'arco non orientato del grafo all'interno della struttura data
        unidirected_edge<int> edge(n1, n2);
        data.graph.add_edge(edge);

        // Controllo del tipo di componente in base al primo carattere del nome (per stabilità mettiamo anche minuscole)
        if (comp_name[0] == 'R' || comp_name[0] == 'r') {
            c.type = CompType::Resistor;
            data.resistors.push_back(c); // Inserimento nel vettore dei resistori
        } 
        else if (comp_name[0] == 'V' || comp_name[0] == 'v') {
            c.type = CompType::VoltageSource;
            data.voltages.push_back(c); // Inserimento nel vettore dei generatori
            int indice_generatore = data.voltages.size() - 1;
			data.voltage_map[edge] = indice_generatore;
        }
    }
    
    // Chiusura dello stream del file
    file.close();

    // Ordinamento dei resistori
    // Chiamata a std::sort utilizzando la funzione esterna di ordinamento dichiarata sopra
    std::sort(data.resistors.begin(), data.resistors.end(), compareResistors);

    // Assegnazione delle righe nella mappa
    // Ora che il vettore dei resistori è ordinato, popoliamo la mappa associando
    // a ciascun arco l'indice della riga corrispondente (la sua posizione i nel vettore).
    for (int i = 0; i < data.resistors.size(); i++) {
        unidirected_edge<int> edge(data.resistors[i].original_node1, data.resistors[i].original_node2);
        data.resistor_row_map[edge] = i; 
    }

    return true;
}

