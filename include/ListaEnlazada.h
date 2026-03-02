#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
#include <stdexcept>

template <class T>
class ListaEnlazada {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    int tam;

public:
    // Constructor
    ListaEnlazada() : cabeza(nullptr), tam(0) {}

    // Constructor copia
    ListaEnlazada(const ListaEnlazada<T>& otra) : cabeza(nullptr), tam(0) {
        Nodo* actual = otra.cabeza;
        while (actual != nullptr) {
            agregarAlFinal(actual->dato);
            actual = actual->siguiente;
        }
    }

    // Operador de asignación
    ListaEnlazada<T>& operator=(const ListaEnlazada<T>& otra) {
        if (this != &otra) {
            limpiar();
            Nodo* actual = otra.cabeza;
            while (actual != nullptr) {
                agregarAlFinal(actual->dato);
                actual = actual->siguiente;
            }
        }
        return *this;
    }

    // Destructor
    ~ListaEnlazada() {
        limpiar();
    }

    // Limpiar lista
    void limpiar() {
        while (cabeza != nullptr) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        tam = 0;
    }

    // Agregar al final
    void agregarAlFinal(const T& dato) {
        Nodo* nuevo = new Nodo(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        ++tam;
    }

    // Agregar al inicio
    void agregarAlInicio(const T& dato) {
        Nodo* nuevo = new Nodo(dato);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        ++tam;
    }

    // Eliminar último
    T eliminarUltimo() {
        if (cabeza == nullptr) {
            throw std::underflow_error("Lista vacia");
        }
        if (cabeza->siguiente == nullptr) {
            T dato = cabeza->dato;
            delete cabeza;
            cabeza = nullptr;
            --tam;
            return dato;
        }
        Nodo* actual = cabeza;
        while (actual->siguiente->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        T dato = actual->siguiente->dato;
        delete actual->siguiente;
        actual->siguiente = nullptr;
        --tam;
        return dato;
    }

    // Obtener elemento por índice
    T& obtener(int indice) {
        if (indice < 0 || indice >= tam) {
            throw std::out_of_range("Indice fuera de rango");
        }
        Nodo* actual = cabeza;
        for (int i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }

    const T& obtener(int indice) const {
        if (indice < 0 || indice >= tam) {
            throw std::out_of_range("Indice fuera de rango");
        }
        Nodo* actual = cabeza;
        for (int i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }

    // Obtener tamaño
    int getTam() const {
        return tam;
    }

    // Verificar si está vacía
    bool estaVacia() const {
        return tam == 0;
    }

    // Imprimir lista
    void imprimir(std::ostream& os = std::cout) const {
        Nodo* actual = cabeza;
        int indice = 0;
        while (actual != nullptr) {
            os << "[" << indice << "] -> " << actual->dato << std::endl;
            actual = actual->siguiente;
            ++indice;
        }
    }
};

#endif // LISTA_ENLAZADA_H
