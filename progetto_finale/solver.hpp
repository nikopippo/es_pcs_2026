#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "CircuitData.hpp"
#include "grad_coniug.cpp"

using namespace Eigen;
using namespace std;

void solve_circuit(const CircuitData& data, const std::vector<std::vector<int>>& maglie) {
	int num_resistori = data.resistors.size();
    int num_maglie = maglie.size();

    // Se il circuito non ha maglie chiuse, non c'è nulla da risolvere
    if (num_maglie == 0) {
        cout << "Errore: Nessuna maglia trovata nel circuito." << endl;
        return;
    }

    // Inizializziamo le matrici e i vettori di Eigen con tutti zeri
    MatrixXd B = MatrixXd::Zero(num_resistori, num_maglie);
    MatrixXd R = MatrixXd::Zero(num_resistori, num_resistori);
    VectorXd v = VectorXd::Zero(num_maglie);

    // Popoliamo la matrice Diagonale delle Resistenze (R)
    // scoorriamo sulla riga i che corrisponde al resistore i-esimo
    for (int i = 0; i < num_resistori; i++) {
        R(i, i) = data.resistors[i].value;
    }

    // Costruiamo la matrice B e il vettore v analizzando le maglie
    // j scorre le colonne di B (una colonna per ogni maglia)
    for (int j = 0; j < num_maglie; j++) {
       
        // Estraiamo il cammino di nodi della maglia corrente
        vector<int> cammino = maglie[j];
       
        // Scorriamo i nodi della singola maglia a coppie (passo dopo passo)
        // Se la maglia ha K nodi, facciamo K-1 passi
        for (int step = 0; step < cammino.size() - 1; step++) {
            int nodo_corrente = cammino[step];
            int nodo_prossimo = cammino[step + 1];

            // Creiamo l'arco geometrico associato a questo passo (applica min e max in automatico)
            unidirected_edge<int> edge_passo(nodo_corrente, nodo_prossimo);

            // VERIFICHIAMO SE È UN RESISTORE (Popolamento Matrice B)
            // Controlliamo se questo arco è presente nella mappa dei resistori (.find restituisce end se non trova niente)
            if (data.resistor_row_map.find(edge_passo) != data.resistor_row_map.end()) {	
               
                // Recuperiamo l'indice di riga corretto per questo resistore
                int riga_resistore = data.resistor_row_map.at(edge_passo);

                // Determiniamo il segno in base alla direzione del cammino
                if (nodo_corrente < nodo_prossimo) {
                    // Andiamo da un nodo piccolo a uno grande -> Verso Concorde (+1)
                    B(riga_resistore, j) = B(riga_resistore, j) + 1.0;
                } else {
                    // Andiamo da un nodo grande a uno piccolo -> Verso Discorde (-1)
                    B(riga_resistore, j) = B(riga_resistore, j) - 1.0;
                }
            }

            // VERIFICHIAMO SE È UN GENERATORE (Popolamento Vettore v)
            // Controlliamo se questo arco è presente nella mappa dei generatori
            if (data.voltage_map.find(edge_passo) != data.voltage_map.end()) {
                 
				// Recuperiamo i dati del generatore reale          
				int indice_gen = data.voltage_map.at(edge_passo);
    
				Component gen = data.voltages[indice_gen];
			   
                // original_node1 è il polo (+), original_node2 è il polo (-)
                if (nodo_corrente == gen.original_node2 && nodo_prossimo == gen.original_node1) {
                    // Entriamo dal (-) e usciamo dal (+) -> Guadagniamo potenziale (+V)
                    v(j) = v(j) + gen.value;
                }
                else if (nodo_corrente == gen.original_node1 && nodo_prossimo == gen.original_node2) {
                    // Entriamo dal (+) e usciamo dal (-) -> Perdiamo potenziale (-V)
                    v(j) = v(j) - gen.value;
                }
            }
        }
    }

    // Calcoliamo la matrice del sistema A = B' * R * B
    MatrixXd A = B.transpose() * R * B;

    // Risolviamo il sistema lineare A * i_maglia = v
    // Impostiamo i parametri di tolleranza
    int iter_max = 10*num_maglie;
    double tol_rel = 1e-7;

    // Chiamiamo la funzione del Gradiente Coniugato
    VectorXd i_maglia = grad_coniug(A, v, tol_rel, iter_max);

    // Calcoliamo le correnti e le tensioni effettive sui singoli resistori
    // Formula del metodo delle maglie: i_resistori = B * i_maglia
    VectorXd i_resistori = B * i_maglia;
    // Legge di Ohm: V_resistori = R * i_resistori
    VectorXd v_resistori = R * i_resistori;

    // Formattazione output finale
    for (int r = 0; r < num_resistori; r++) {
        Component res = data.resistors[r];
       
        cout << "R" << res.id << ": V=" << v_resistori(r)
             << " volts, I=" << i_resistori(r) << " amps" << endl;
    }
}