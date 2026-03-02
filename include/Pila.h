#ifndef PILA_H
#define PILA_H

#include "Vector.h"
#include <stdexcept>

template <class T>
class Pila {
private:
    Vector<T> datos;

public:
    // Constructor
    Pila() : datos() {}

    // Apilar (push)
    void apilar(const T& valor) {
        datos.agregar(valor);
    }

    // Desapilar (pop)
    T desapilar() {
        if (estaVacia()) {
            throw std::underflow_error("Pila vacia");
        }
        T valor = datos[datos.getTam() - 1];
        datos.eliminarUltimo();
        return valor;
    }

    // Cima (top)
    T& cima() {
        if (estaVacia()) {
            throw std::underflow_error("Pila vacia");
        }
        return datos[datos.getTam() - 1];
    }

    const T& cima() const {
        if (estaVacia()) {
            throw std::underflow_error("Pila vacia");
        }
        return datos[datos.getTam() - 1];
    }

    // Verificar si está vacía
    bool estaVacia() const {
        return datos.getTam() == 0;
    }

    // Obtener tamaño
    int getTam() const {
        return datos.getTam();
    }

    // Limpiar
    void limpiar() {
        while (!estaVacia()) {
            desapilar();
        }
    }
};

#endif // PILA_H
