#pragma once	//evita ridefinizione
#include <iostream>
#include <queue>
#include <stdexcept>

/*Implemento di seguito queue e stack con specifici comandi tratti dalla std
 per semplificarmi l'implementazione di DFS e BFS  */

template<typename T>
class fifo{
private:
	std::queue<T> coda;

public:
	/* Costruttore di default */
    fifo() = default;
	
	/* Metodo put (inserire elemento nello queue) */
	void put(const T& other) {
		coda.push(other);
	}
	
	/* Metodo get (rimuovere elemento dalla cima dello queue e restituirlo) */
	T get() {
		T value;
		if (coda.empty()) {
			throw std::out_of_range("queue vuoto");	//genero errore se vuoto
		}
		value = coda.front();
		coda.pop();
		return value;
	}
	
	/* Metodo empty (vedo se lo queue è vuoto) */
	bool empty() const {
		return coda.empty();
	}
};