#ifndef TRANSFORMACION_H
#define TRANSFORMACION_H

#include "Vector.h"
#include <iostream>
#include <string>

class Transformacion {
private:
    Vector<double> resultado;
    double minimo;
    double maximo;
    double media;
    int nivel; // nivel de transformación (1 = primera diferencia, 2 = segunda, etc.)

public:
    // Constructor por defecto
    Transformacion() : minimo(0), maximo(0), media(0), nivel(0) {}

    // Constructor con parámetros
    Transformacion(const Vector<double>& res, int niv) 
        : resultado(res), nivel(niv) {
        calcularEstadisticas();
    }

    // Constructor copia
    Transformacion(const Transformacion& otra) 
        : resultado(otra.resultado), minimo(otra.minimo), 
          maximo(otra.maximo), media(otra.media), nivel(otra.nivel) {}

    // Operador de asignación
    Transformacion& operator=(const Transformacion& otra) {
        if (this != &otra) {
            resultado = otra.resultado;
            minimo = otra.minimo;
            maximo = otra.maximo;
            media = otra.media;
            nivel = otra.nivel;
        }
        return *this;
    }

    // Calcular estadísticas básicas
    void calcularEstadisticas() {
        if (resultado.getTam() > 0) {
            minimo = resultado.minimo();
            maximo = resultado.maximo();
            media = resultado.media();
        }
    }

    // Getters
    const Vector<double>& getResultado() const { return resultado; }
    double getMinimo() const { return minimo; }
    double getMaximo() const { return maximo; }
    double getMedia() const { return media; }
    int getNivel() const { return nivel; }

    // Imprimir transformación
    void imprimir(std::ostream& os = std::cout) const {
        os << "--- Transformacion Nivel " << nivel << " ---" << std::endl;
        os << "Resultado: " << resultado << std::endl;
        os << "Minimo: " << minimo << std::endl;
        os << "Maximo: " << maximo << std::endl;
        os << "Media:  " << media << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Transformacion& t) {
        t.imprimir(os);
        return os;
    }
};

#endif // TRANSFORMACION_H
