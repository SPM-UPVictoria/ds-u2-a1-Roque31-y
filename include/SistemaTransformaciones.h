#ifndef SISTEMA_TRANSFORMACIONES_H
#define SISTEMA_TRANSFORMACIONES_H

#include "Vector.h"
#include "Matriz.h"
#include "ListaEnlazada.h"
#include "Pila.h"
#include "Cola.h"
#include "Transformacion.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

class SistemaTransformaciones {
private:
    Vector<double> funcionOriginal;
    Matriz<double> matrizTransformacion;
    ListaEnlazada<Transformacion> historial;
    Pila<Transformacion> pilaDeshacer;  // undo
    Cola<Transformacion> colaRehacer;   // redo
    int nivelActual;
    bool funcionIngresada;
    bool matrizGenerada;

    // Vector actual sobre el que se aplica la siguiente transformación
    Vector<double> vectorActual;

public:
    SistemaTransformaciones() 
        : nivelActual(0), funcionIngresada(false), matrizGenerada(false) {}

    // 1. Ingresar función discreta
    void ingresarFuncion() {
        int n;
        std::cout << "\nIngrese el numero de puntos de la funcion discreta (N+1): ";
        std::cin >> n;

        if (n <= 0) {
            std::cout << "Error: El numero de puntos debe ser positivo." << std::endl;
            return;
        }

        funcionOriginal = Vector<double>(n);
        std::cout << "Ingrese los " << n << " valores de f(n):" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << "  f(" << i << ") = ";
            std::cin >> funcionOriginal[i];
        }

        vectorActual = funcionOriginal;
        funcionIngresada = true;
        matrizGenerada = false;
        nivelActual = 0;

        // Limpiar historial y pilas/colas
        historial.limpiar();
        pilaDeshacer.limpiar();
        colaRehacer.limpiar();

        std::cout << "\nFuncion ingresada correctamente: " << funcionOriginal << std::endl;
    }

    // 2. Generar matriz transformadora
    void generarMatriz() {
        if (!funcionIngresada) {
            std::cout << "Error: Primero debe ingresar la funcion discreta." << std::endl;
            return;
        }

        int n = vectorActual.getTam();
        matrizTransformacion = Matriz<double>::generarMatrizTransformacion(n);
        matrizGenerada = true;

        std::cout << "\nMatriz de transformacion (" << n << "x" << n << ") generada:" << std::endl;
        matrizTransformacion.imprimir();
    }

    // 3. Aplicar transformación
    void aplicarTransformacion() {
        if (!funcionIngresada) {
            std::cout << "Error: Primero debe ingresar la funcion discreta." << std::endl;
            return;
        }

        int n = vectorActual.getTam();
        if (n < 2) {
            std::cout << "Error: El vector actual tiene menos de 2 elementos, no se puede transformar mas." << std::endl;
            return;
        }

        // Regenerar la matriz al tamaño correcto del vector actual
        matrizTransformacion = Matriz<double>::generarMatrizTransformacion(n);
        matrizGenerada = true;

        // Aplicar g = T * f
        Vector<double> resultado = matrizTransformacion.multiplicarPorVector(vectorActual);

        ++nivelActual;
        Transformacion trans(resultado, nivelActual);

        // Guardar en historial (lista enlazada)
        historial.agregarAlFinal(trans);

        // Guardar estado anterior en pila undo
        pilaDeshacer.apilar(Transformacion(vectorActual, nivelActual - 1));

        // Limpiar cola redo al hacer nueva transformación
        colaRehacer.limpiar();

        // Actualizar vector actual
        vectorActual = resultado;

        std::cout << "\nTransformacion nivel " << nivelActual << " aplicada." << std::endl;
        std::cout << "Resultado: " << resultado << std::endl;
        std::cout << "Min: " << trans.getMinimo() 
                  << " | Max: " << trans.getMaximo() 
                  << " | Media: " << trans.getMedia() << std::endl;
    }

    // 4. Mostrar historial de transformaciones
    void mostrarHistorial() {
        if (historial.estaVacia()) {
            std::cout << "\nNo hay transformaciones en el historial." << std::endl;
            return;
        }

        std::cout << "\n========================================" << std::endl;
        std::cout << "   HISTORIAL DE TRANSFORMACIONES" << std::endl;
        std::cout << "========================================" << std::endl;

        std::cout << "\nFuncion original: " << funcionOriginal << std::endl;
        std::cout << std::endl;

        for (int i = 0; i < historial.getTam(); ++i) {
            const Transformacion& t = historial.obtener(i);
            std::cout << "Nivel " << t.getNivel() << ": " << t.getResultado() << std::endl;
            std::cout << "  Min: " << std::fixed << std::setprecision(4) << t.getMinimo()
                      << " | Max: " << t.getMaximo()
                      << " | Media: " << t.getMedia() << std::endl;
            std::cout << std::endl;
        }
        std::cout << "Vector actual: " << vectorActual << std::endl;
        std::cout << "========================================" << std::endl;
    }

    // 5. Deshacer última transformación (pila)
    void deshacer() {
        if (pilaDeshacer.estaVacia()) {
            std::cout << "\nNo hay transformaciones para deshacer." << std::endl;
            return;
        }

        // Guardar estado actual en cola redo
        colaRehacer.encolar(Transformacion(vectorActual, nivelActual));

        // Recuperar estado anterior
        Transformacion anterior = pilaDeshacer.desapilar();
        vectorActual = anterior.getResultado();
        --nivelActual;

        std::cout << "\nTransformacion deshecha. Nivel actual: " << nivelActual << std::endl;
        std::cout << "Vector actual: " << vectorActual << std::endl;
    }

    // 6. Rehacer transformación (cola)
    void rehacer() {
        if (colaRehacer.estaVacia()) {
            std::cout << "\nNo hay transformaciones para rehacer." << std::endl;
            return;
        }

        // Guardar estado actual en pila undo
        pilaDeshacer.apilar(Transformacion(vectorActual, nivelActual));

        // Recuperar de cola redo
        Transformacion siguiente = colaRehacer.desencolar();
        vectorActual = siguiente.getResultado();
        ++nivelActual;

        std::cout << "\nTransformacion rehecha. Nivel actual: " << nivelActual << std::endl;
        std::cout << "Vector actual: " << vectorActual << std::endl;
    }

    // 7. Calcular estadísticas
    void calcularEstadisticas() {
        if (!funcionIngresada) {
            std::cout << "Error: No hay funcion ingresada." << std::endl;
            return;
        }

        std::cout << "\n========================================" << std::endl;
        std::cout << "       ESTADISTICAS" << std::endl;
        std::cout << "========================================" << std::endl;

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "\nFuncion original:" << std::endl;
        std::cout << "  Valores: " << funcionOriginal << std::endl;
        std::cout << "  Minimo:  " << funcionOriginal.minimo() << std::endl;
        std::cout << "  Maximo:  " << funcionOriginal.maximo() << std::endl;
        std::cout << "  Media:   " << funcionOriginal.media() << std::endl;

        if (!historial.estaVacia()) {
            std::cout << "\nTransformaciones:" << std::endl;
            for (int i = 0; i < historial.getTam(); ++i) {
                const Transformacion& t = historial.obtener(i);
                std::cout << "  Nivel " << t.getNivel() << ":" << std::endl;
                std::cout << "    Minimo:  " << t.getMinimo() << std::endl;
                std::cout << "    Maximo:  " << t.getMaximo() << std::endl;
                std::cout << "    Media:   " << t.getMedia() << std::endl;
            }
        }

        std::cout << "\nVector actual:" << std::endl;
        std::cout << "  Valores: " << vectorActual << std::endl;
        std::cout << "  Minimo:  " << vectorActual.minimo() << std::endl;
        std::cout << "  Maximo:  " << vectorActual.maximo() << std::endl;
        std::cout << "  Media:   " << vectorActual.media() << std::endl;
        std::cout << "========================================" << std::endl;
    }

    // 8. Exportar reporte
    void exportarReporte() {
        std::string nombreArchivo = "../docs/reporte_transformaciones.txt";
        std::ofstream archivo(nombreArchivo);

        // Si falla con ruta relativa (ej: desde build/), intentar sin prefijo
        if (!archivo.is_open()) {
            nombreArchivo = "docs/reporte_transformaciones.txt";
            archivo.open(nombreArchivo);
        }

        if (!archivo.is_open()) {
            std::cout << "Error: No se pudo crear el archivo de reporte." << std::endl;
            return;
        }

        archivo << "============================================================" << std::endl;
        archivo << "  REPORTE DE TRANSFORMACIONES DISCRETAS" << std::endl;
        archivo << "============================================================" << std::endl;
        archivo << std::endl;

        archivo << std::fixed << std::setprecision(4);

        archivo << "FUNCION ORIGINAL:" << std::endl;
        archivo << "  Valores: " << funcionOriginal << std::endl;
        archivo << "  Tamano:  " << funcionOriginal.getTam() << std::endl;
        if (funcionOriginal.getTam() > 0) {
            archivo << "  Minimo:  " << funcionOriginal.minimo() << std::endl;
            archivo << "  Maximo:  " << funcionOriginal.maximo() << std::endl;
            archivo << "  Media:   " << funcionOriginal.media() << std::endl;
        }
        archivo << std::endl;

        if (matrizGenerada) {
            archivo << "MATRIZ DE TRANSFORMACION:" << std::endl;
            matrizTransformacion.imprimir(archivo);
            archivo << std::endl;
        }

        archivo << "HISTORIAL DE TRANSFORMACIONES:" << std::endl;
        archivo << "------------------------------------------------------------" << std::endl;

        if (historial.estaVacia()) {
            archivo << "  (Sin transformaciones aplicadas)" << std::endl;
        } else {
            for (int i = 0; i < historial.getTam(); ++i) {
                const Transformacion& t = historial.obtener(i);
                archivo << "  Nivel " << t.getNivel() << ":" << std::endl;
                archivo << "    Resultado: " << t.getResultado() << std::endl;
                archivo << "    Minimo:    " << t.getMinimo() << std::endl;
                archivo << "    Maximo:    " << t.getMaximo() << std::endl;
                archivo << "    Media:     " << t.getMedia() << std::endl;
                archivo << std::endl;
            }
        }

        archivo << "------------------------------------------------------------" << std::endl;
        archivo << "VECTOR ACTUAL:" << std::endl;
        archivo << "  Valores: " << vectorActual << std::endl;
        if (vectorActual.getTam() > 0) {
            archivo << "  Minimo:  " << vectorActual.minimo() << std::endl;
            archivo << "  Maximo:  " << vectorActual.maximo() << std::endl;
            archivo << "  Media:   " << vectorActual.media() << std::endl;
        }
        archivo << std::endl;
        archivo << "Nivel de transformacion actual: " << nivelActual << std::endl;
        archivo << "Transformaciones en pila undo: " << pilaDeshacer.getTam() << std::endl;
        archivo << "Transformaciones en cola redo: " << colaRehacer.getTam() << std::endl;
        archivo << "============================================================" << std::endl;

        archivo.close();
        std::cout << "\nReporte exportado exitosamente a: " << nombreArchivo << std::endl;
    }

    // Mostrar menú y ejecutar
    void ejecutar() {
        int opcion = 0;
        do {
            std::cout << "\n============================================" << std::endl;
            std::cout << "  SISTEMA DE TRANSFORMACIONES DISCRETAS" << std::endl;
            std::cout << "============================================" << std::endl;
            std::cout << "  1. Ingresar funcion discreta" << std::endl;
            std::cout << "  2. Generar matriz transformadora" << std::endl;
            std::cout << "  3. Aplicar transformacion" << std::endl;
            std::cout << "  4. Mostrar historial de transformaciones" << std::endl;
            std::cout << "  5. Deshacer ultima transformacion (undo)" << std::endl;
            std::cout << "  6. Rehacer transformacion (redo)" << std::endl;
            std::cout << "  7. Calcular estadisticas" << std::endl;
            std::cout << "  8. Exportar reporte" << std::endl;
            std::cout << "  9. Salir" << std::endl;
            std::cout << "============================================" << std::endl;
            std::cout << "  Seleccione una opcion: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1: ingresarFuncion(); break;
                case 2: generarMatriz(); break;
                case 3: aplicarTransformacion(); break;
                case 4: mostrarHistorial(); break;
                case 5: deshacer(); break;
                case 6: rehacer(); break;
                case 7: calcularEstadisticas(); break;
                case 8: exportarReporte(); break;
                case 9:
                    std::cout << "\nSaliendo del sistema. Hasta pronto!" << std::endl;
                    break;
                default:
                    std::cout << "\nOpcion no valida. Intente de nuevo." << std::endl;
                    break;
            }
        } while (opcion != 9);
    }
};

#endif // SISTEMA_TRANSFORMACIONES_H
