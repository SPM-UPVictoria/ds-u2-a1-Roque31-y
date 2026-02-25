[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/K_p5iEqk)
# Estructura de Datos - Unidad 2 - Actividad 1

## Problema a resolver

Se desea implementar un sistema capaz de resolver el siguiente problema:

Dada una función discreta ( $f(n)$ ) definida en un intervalo finito ( $0 \le n \le N$ ), el programa deberá:

1. **Almacenar la función discreta** en un **vector unidimensional**.
2. **Generar una matriz de transformación** ( T ) de tamaño ( N \times N ), donde cada elemento se define como:

$$
T_{i,j} = \left\{ \begin{matrix}
1 & \text{si } i = j \\
-1 & \text{si } i = j+1 \\
0 & \text{en otro caso}
\end{matrix} \right.
$$

Esta matriz puede verse como un operador de *diferenciación discreta*.

3. Aplicar la transformación:

$$
g = T \cdot f
$$

donde ( $g$ ) es un nuevo vector que representa la diferencia discreta entre puntos contiguos de la función.

4. **Registrar múltiples transformaciones sucesivas** (por ejemplo, primera diferencia, segunda diferencia, etc.), y almacenarlas en:

   * **una lista enlazada genérica**, donde cada nodo contiene:

     * un vector resultado,
     * estadísticas básicas (mínimo, máximo, media),
     * un identificador del nivel de transformación.

5. Implementar un **sistema de deshacer/rehacer** (undo/redo):

   * Deshacer transformación: utilizando una **pila**.
   * Rehacer transformación: utilizando una **cola**.

6. El programa deberá permitir:

   * Ingresar la función original.
   * Aplicar transformaciones sucesivas.
   * Visualizar resultados en forma tabular.
   * Deshacer o rehacer cambios.
   * Exportar un reporte final en texto plano.

---

## Estructuras de Datos que Deben Usarse Obligatoriamente

### **Tipos de Datos Genéricos**

* Todas las clases principales deberán ser **plantillas (`template<class T>`)**.
* La lista enlazada, pila y cola deberán manejar datos genéricos.

### Programación orientada a objetos

Se deben definir al menos las siguientes clases:

1. `Vector<T>` – implementación propia usando memoria dinámica.
2. `Matriz<T>` – soporta multiplicación por vectores.
3. `ListaEnlazada<T>` – nodos genéricos.
4. `Pila<T>` – basada en vector dinámico.
5. `Cola<T>` – basada en vector dinámico.
6. `Transformacion` – clase para encapsular resultados y metadatos.
7. `SistemaTransformaciones` – clase principal que orquesta todo el programa.

### Vectores (unidimensionales y multidimensionales)

* Vector para almacenar la función.
* Matriz ( N \times N ) para el operador discreto.
* Uso de memoria dinámica (no `std::vector`).

### Listas enlazadas

* Cada nodo contendrá el resultado de una transformación y estadísticas.

### Pilas y colas (implementadas mediante vectores dinámicos)

* Pila para acciones de "undo".
* Cola para acciones de "redo".

---

## Funcionalidades Mínimas del Sistema

El programa debe ofrecer un menú con las siguientes opciones:

1. **Ingresar función discreta**.
2. **Generar matriz transformadora**.
3. **Aplicar transformación** (y guardarla en lista enlazada).
4. **Mostrar historial de transformaciones**.
5. **Deshacer última transformación (pila)**.
6. **Rehacer transformación (cola)**.
7. **Calcular estadísticas** (mínimo, máximo, promedio).
8. **Exportar reporte**.
9. **Salir**.

---

## Entregables

Los alumnos deberán entregar:

### Código Fuente

* Proyecto realizado en  CMAKE
* Archivos `.cpp` y `.h`.
* Implementación obligatoria sin usar contenedores estándar (excepto para comparaciones básicas).

### Proyecto en CMake

El proyecto debe contener al menos:

```
/CMakeLists.txt
/src
/include
/build
/docs
```

### Reporte de Resultados (Markdown dentro del repositorio)

Debe incluir:

1. Introducción y descripción del problema.
2. Casos de prueba utilizados.
3. Evidencia de funcionamiento (capturas).
4. Conclusiones sobre el uso de estructuras de datos.