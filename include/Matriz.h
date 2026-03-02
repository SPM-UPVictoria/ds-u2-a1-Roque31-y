#ifndef MATRIZ_H
#define MATRIZ_H

#include "Vector.h"
#include <iostream>
#include <iomanip>

template <class T>
class Matriz {
private:
    T** datos;
    int filas;
    int columnas;

    void liberar() {
        if (datos) {
            for (int i = 0; i < filas; ++i) {
                delete[] datos[i];
            }
            delete[] datos;
            datos = nullptr;
        }
    }

    void copiarDesde(const Matriz<T>& otra) {
        filas = otra.filas;
        columnas = otra.columnas;
        datos = new T*[filas];
        for (int i = 0; i < filas; ++i) {
            datos[i] = new T[columnas];
            for (int j = 0; j < columnas; ++j) {
                datos[i][j] = otra.datos[i][j];
            }
        }
    }

public:
    // Constructor por defecto
    Matriz() : datos(nullptr), filas(0), columnas(0) {}

    // Constructor con dimensiones
    Matriz(int f, int c) : filas(f), columnas(c) {
        datos = new T*[filas];
        for (int i = 0; i < filas; ++i) {
            datos[i] = new T[columnas]();
        }
    }

    // Constructor copia
    Matriz(const Matriz<T>& otra) : datos(nullptr), filas(0), columnas(0) {
        copiarDesde(otra);
    }

    // Operador de asignación
    Matriz<T>& operator=(const Matriz<T>& otra) {
        if (this != &otra) {
            liberar();
            copiarDesde(otra);
        }
        return *this;
    }

    // Destructor
    ~Matriz() {
        liberar();
    }

    // Acceso a elementos
    T& operator()(int i, int j) {
        if (i < 0 || i >= filas || j < 0 || j >= columnas) {
            throw std::out_of_range("Indice de matriz fuera de rango");
        }
        return datos[i][j];
    }

    const T& operator()(int i, int j) const {
        if (i < 0 || i >= filas || j < 0 || j >= columnas) {
            throw std::out_of_range("Indice de matriz fuera de rango");
        }
        return datos[i][j];
    }

    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }

    // Generar matriz de transformación (diferenciación discreta)
    static Matriz<T> generarMatrizTransformacion(int n) {
        Matriz<T> T_mat(n, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    T_mat(i, j) = static_cast<T>(1);
                } else if (i == j + 1) {
                    T_mat(i, j) = static_cast<T>(-1);
                } else {
                    T_mat(i, j) = static_cast<T>(0);
                }
            }
        }
        return T_mat;
    }

    // Multiplicación matriz por vector: g = T * f
    Vector<T> multiplicarPorVector(const Vector<T>& v) const {
        if (columnas != v.getTam()) {
            throw std::invalid_argument("Dimensiones incompatibles para multiplicacion");
        }
        Vector<T> resultado(filas);
        for (int i = 0; i < filas; ++i) {
            T suma = static_cast<T>(0);
            for (int j = 0; j < columnas; ++j) {
                suma += datos[i][j] * v[j];
            }
            resultado[i] = suma;
        }
        return resultado;
    }

    // Imprimir matriz
    void imprimir(std::ostream& os = std::cout) const {
        for (int i = 0; i < filas; ++i) {
            os << "| ";
            for (int j = 0; j < columnas; ++j) {
                os << std::setw(6) << datos[i][j] << " ";
            }
            os << "|" << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Matriz<T>& m) {
        m.imprimir(os);
        return os;
    }
};

#endif // MATRIZ_H
