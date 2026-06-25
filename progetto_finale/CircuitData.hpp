#include <vector>
#include <map>
#include "componente.hpp"
#pragma once	//evita ridefinizione
#include "unidirected_graph.hpp"

struct CircuitData {
    // Il grafo topologico puro (con TUTTI gli archi, sia R che V)
    unidirected_graph<int> graph;

    // Vettori separati per Eigen
    std::vector<Component> resistors;
    std::vector<Component> voltages;

    // Mappe per la decodifica durante la ricerca dei cicli
    std::map<unidirected_edge<int>, int> resistor_row_map; 	//key = edge, value = indice della resistenza sull'arco
    std::map<unidirected_edge<int>, int> voltage_map; //key = edge,	value = Component
};