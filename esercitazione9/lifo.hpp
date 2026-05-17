#pragma once	//evita ridefinizione
#include <iostream>
#include <stack>
#include <stdexcept>

template<typename T>
class lifo{
private:
	std::stack<T> pila;

public:
	/* Costruttore di default */
    lifo() = default;
	
	/* Metodo put (inserire elemento nello stack) */
	void put(const T& other) {
		pila.push(other);
	}
	
	/* Metodo get (rimuovere elemento dalla cima dello stack e restituirlo) */
	T get() {
		T value;
		if (pila.empty()) {
			throw std::out_of_range("Stack vuoto");	//genero errore se vuoto
		}
		value = pila.top();
		pila.pop();
		return value;
	}
	
	/* Metodo empty (vedo se lo stack è vuoto) */
	bool empty() const {
		return pila.empty();
	}
};