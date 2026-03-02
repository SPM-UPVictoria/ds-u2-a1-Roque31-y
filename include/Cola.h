#ifndef COLA_H
#define COLA_H

#include "Vector.h"
#include <stdexcept>

template <class T>
class Cola {
private:
    Vector<T> datos;
    int frente;

public:
    // Constructor
    Cola() : datos(), frente(0) {}

    // Encolar (enqueue)
    void encolar(const T& valor) {
        datos.agregar(valor);
    }

    // Desencolar (dequeue)
    T desencolar() {
        if (estaVacia()) {
            throw std::underflow_error("Cola vacia");
        }
        T valor = datos[frente];
        ++frente;
        // Compactar si el frente se alejó mucho
        if (frente > datos.getTam() / 2 && frente > 10) {
            Vector<T> nuevos(datos.getTam() - frente);
            for (int i = frente; i < datos.getTam(); ++i) {
                nuevos[i - frente] = datos[i];
            }
            datos = nuevos;
            frente = 0;
        }
        return valor;
    }

    // Primer elemento (front)
    T& primero() {
        if (estaVacia()) {
            throw std::underflow_error("Cola vacia");
        }
        return datos[frente];
    }

    const T& primero() const {
        if (estaVacia()) {
            throw std::underflow_error("Cola vacia");
        }
        return datos[frente];
    }

    // Verificar si está vacía
    bool estaVacia() const {
        return frente >= datos.getTam();
    }

    // Obtener tamaño
    int getTam() const {
        return datos.getTam() - frente;
    }

    // Limpiar
    void limpiar() {
        datos = Vector<T>();
        frente = 0;
    }
};

#endif // COLA_H
