#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <cmath>

template <class T>
class Vector {
private:
    T* datos;
    int tam;

public:
    // Constructor por defecto
    Vector() : datos(nullptr), tam(0) {}

    // Constructor con tamaño
    explicit Vector(int n) : tam(n) {
        if (n < 0) {
            throw std::invalid_argument("El tamano no puede ser negativo");
        }
        datos = new T[n]();
    }

    // Constructor con tamaño y valor inicial
    Vector(int n, T valorInicial) : tam(n) {
        datos = new T[n];
        for (int i = 0; i < n; ++i) {
            datos[i] = valorInicial;
        }
    }

    // Constructor copia
    Vector(const Vector<T>& otro) : tam(otro.tam) {
        datos = new T[tam];
        for (int i = 0; i < tam; ++i) {
            datos[i] = otro.datos[i];
        }
    }

    // Operador de asignación
    Vector<T>& operator=(const Vector<T>& otro) {
        if (this != &otro) {
            delete[] datos;
            tam = otro.tam;
            datos = new T[tam];
            for (int i = 0; i < tam; ++i) {
                datos[i] = otro.datos[i];
            }
        }
        return *this;
    }

    // Destructor
    ~Vector() {
        delete[] datos;
    }

    // Acceso por índice
    T& operator[](int indice) {
        if (indice < 0 || indice >= tam) {
            throw std::out_of_range("Indice fuera de rango");
        }
        return datos[indice];
    }

    const T& operator[](int indice) const {
        if (indice < 0 || indice >= tam) {
            throw std::out_of_range("Indice fuera de rango");
        }
        return datos[indice];
    }

    // Obtener tamaño
    int getTam() const {
        return tam;
    }

    // Redimensionar
    void redimensionar(int nuevoTam) {
        T* nuevosDatos = new T[nuevoTam]();
        int minTam = (nuevoTam < tam) ? nuevoTam : tam;
        for (int i = 0; i < minTam; ++i) {
            nuevosDatos[i] = datos[i];
        }
        delete[] datos;
        datos = nuevosDatos;
        tam = nuevoTam;
    }

    // Agregar elemento al final
    void agregar(const T& valor) {
        redimensionar(tam + 1);
        datos[tam - 1] = valor;
    }

    // Eliminar último elemento
    void eliminarUltimo() {
        if (tam == 0) {
            throw std::underflow_error("Vector vacio");
        }
        redimensionar(tam - 1);
    }

    // Obtener mínimo
    T minimo() const {
        if (tam == 0) throw std::logic_error("Vector vacio");
        T min = datos[0];
        for (int i = 1; i < tam; ++i) {
            if (datos[i] < min) min = datos[i];
        }
        return min;
    }

    // Obtener máximo
    T maximo() const {
        if (tam == 0) throw std::logic_error("Vector vacio");
        T max = datos[0];
        for (int i = 1; i < tam; ++i) {
            if (datos[i] > max) max = datos[i];
        }
        return max;
    }

    // Obtener media
    double media() const {
        if (tam == 0) throw std::logic_error("Vector vacio");
        double suma = 0.0;
        for (int i = 0; i < tam; ++i) {
            suma += static_cast<double>(datos[i]);
        }
        return suma / tam;
    }

    // Imprimir vector
    void imprimir(std::ostream& os = std::cout) const {
        os << "[ ";
        for (int i = 0; i < tam; ++i) {
            os << datos[i];
            if (i < tam - 1) os << ", ";
        }
        os << " ]";
    }

    // Operador de salida
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
        v.imprimir(os);
        return os;
    }
};

#endif // VECTOR_H
