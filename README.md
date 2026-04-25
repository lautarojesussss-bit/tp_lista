<div align="right">
    <img width="32px" src="img/algo2.svg">
</div>

# TP

## Información del estudiante

* Lautaro Jesús Duarte Vera
* 114088
* lautarojesussss@gmail.com

---

## Índice
* [1. Instrucciones](#1-Instrucciones)
  * [1.1. Compilar el proyecto](#11-Compilar-el-proyecto)
  * [1.2. Ejecutar las pruebas](#12-Ejecutar-las-pruebas)
  * [1.3. Ejecutar el programa con Valgrind](#13-Ejecutar-el-programa-con-Valgrind)
* [2. Funcionamiento](#2-Funcionamiento)
* [3. Estructura](#3-Estructura)
  * [3.1. Diagrama de memoria](#31-Diagrama-de-memoria)
  * [3.2. Análisis de complejidades](#32-Análisis-de-complejidades)
* [4. Decisiones de diseño y/o complejidades de implementación](#4-Decisiones-de-diseño-yo-complejidades-de-implementación)
* [5. Respuestas a las preguntas teóricas](#5-Respuestas-a-las-preguntas-teóricas)

## 1. Instrucciones

> [!TIP]
> Se recomienda usar un Makefile y colocar en esta sección los comandos Make.

### 1.1. Compilar el proyecto
```bash
make
```

### 1.2. Ejecutar las pruebas
```bash
make run
```

### 1.3. Ejecutar el programa con Valgrind
```bash
make valgrind
```

## 2. Funcionamiento
Fueron implementados 3 TDAs: lista, pila y cola, a continuación se detalla su funcionamiento por separado.

### 2.1 Lista
El TDA `Lista` almacena información de forma secuencial mediante referencias a los elementos. Esta estructura permite gestionar los datos de manera flexible, ofreciendo la capacidad de insertar, consultar y eliminar elementos en cualquier posición válida. Además, provee medios para buscar elementos específicos dentro de la estructura y obtener su posición exacta a partir de su referencia. Se puede saber en todo momento cuántos elementos hay en la `lista`.

<details>
<summary><b>Ver los diagramas de flujo de las primitivas del TDA `lista`</b></summary>

<br>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_crear_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_crear`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_vacia_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_vacia`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_cantidad_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_cantidad`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_insertar_1.svg" width="70%">
  <p>Diagrama de flujo de `lista_insertar`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_insertar_posicion_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_insertar_posicion`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_obtener_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_obtener`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_obtener_posicion_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_obtener_posicion`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_eliminar_1.svg" width="70%">
  <p>Diagrama de flujo de `lista_eliminar`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_eliminar_posicion_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_eliminar_posicion`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_buscar_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_buscar`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_con_cada_elemento_1.svg" width="70%">
  <p>Diagrama de flujo de `lista_con_cada_elemento`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_destruir_todo_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_destruir_todo`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_destruir_1.svg" width="70%">
  <p>Diagrama de flujo de `lista_destruir`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_iterador_crear_1.svg" width="70%">
  <p>Diagrama de flujo de `lista_iterador_crear`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_iterador_hay_mas_elementos_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_iterador_hay_mas_elementos`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_iterador_avanzar_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_iterador_avanzar`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_iterador_actual_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_iterador_actual`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/lista/lista_iterador_destruir_0.svg" width="70%">
  <p>Diagrama de flujo de `lista_iterador_destruir`.</p>
</div>

</details>


### 2.2 Pila
El TDA `Pila` almacena información mediante referencias a los elementos. Esta estructura permite gestionar los datos bajo el principio LIFO, ofreciendo la capacidad de insertar, consultar y eliminar elementos en en la última posición de la `pila`. Se puede saber en todo momento cuántos elementos hay en la pila.

<details>
<summary><b>Ver los diagramas de flujo de las primitivas del TDA `pila`</b></summary>

<br>

<div align="center">
  <img src="img/diagramas_de_flujo/pila/pila_crear_0.svg" width="70%">
  <p>Diagrama de flujo de `pila_crear`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/pila/pila_apilar_0.svg" width="70%">
  <p>Diagrama de flujo de `pila_apilar`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/pila/pila_desapilar_1.svg" width="70%">
  <p>Diagrama de flujo de `pila_desapilar`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/pila/pila_tope_0.svg" width="70%">
  <p>Diagrama de flujo de `pila_tope`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/pila/pila_cantidad_0.svg" width="70%">
  <p>Diagrama de flujo de `pila_cantidad`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/pila/pila_destruir_0.svg" width="70%">
  <p>Diagrama de flujo de `pila_destruir`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/pila/pila_destruir_todo_0.svg" width="70%">
  <p>Diagrama de flujo de `pila_destruir_todo`.</p>
</div>

</details>

### 2.3 Cola
El TDA `Cola` permite almacenar información de elementos mediante referencias a ellos. La estructura permite gestionar la información de los elementos bajo el principio FIFO, ofreciendo la capacidad de leer y eliminar elementos en el comienzo de la cola, y de insertar elementos en el final de la `cola`. Se puede saber en todo momento cuántos elementos hay en la `cola`.

<details>
<summary><b>Ver los diagramas de flujo de las primitivas del TDA `cola`</b></summary>

<br>

<div align="center">
  <img src="img/diagramas_de_flujo/cola/cola_crear_0.svg" width="70%">
  <p>Diagrama de flujo de `cola_crear`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/cola/cola_encolar_0.svg" width="70%">
  <p>Diagrama de flujo de `cola_encolar`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/cola/cola_desencolar_0.svg" width="70%">
  <p>Diagrama de flujo de `cola_desencolar`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/cola/cola_frente_0.svg" width="70%">
  <p>Diagrama de flujo de `cola_frente`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/cola/cola_cantidad_0.svg" width="70%">
  <p>Diagrama de flujo de `cola_cantidad`.</p>
</div>

<div align="center">
  <img src="img/diagramas_de_flujo/cola/cola_destruir_todo_0.svg" width="70%">
  <p>Diagrama de flujo de `cola_destruir_todo`.</p>
</div>

</details>

## 3. Estructura (Lista)
Para implementar la estructura se dicidió hacer uso de una estructura `nodo_t` auxiliar, esta estructura auxiliar se compone de un puntero genérico (void*) llamado `elemento`, que como su nombre indica, guarda la referencia a un elemento, y un nodo_t* llamado `siguiente` que guarda la referencia al siguiente nodo en la lista.
La `lista_t` se compone por dos referencias a nodos y un campo size_t que funciona como el tope, hay una referencia al primer nodo de la `lista` y una referencia al último nodo de la misma.

### 3.1. Diagrama de memoria
<div align="center">
  <img src="img/diagramas_de_memoria/lista_t_struct_0.svg" width="70%">
  <p>Diagrama de memoria de la estructura en el caso de que tuviese solo 1 elemento cargado.</p>
</div>


### 3.2. Análisis de complejidades
#### 3.2.1 Lista
A continuación se detallan las complejidades de todas las primitivas del TDA `lista`

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `lista_crear`       |  $O(1)$   |Tiene como parámetro... y, al leer una línea....|
|      `lista_vacia`       |  $O(1)$   |Tiene como parámetro..., la cual....            |
|      `lista_cantidad`       |  $O(1)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_insertar`       |  $O(1)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_insertar_posicion`       |  $O(n)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_obtener`       |  $O(1)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_obtener_posicion`       |  $O(n)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_eliminar`       |  $O(n)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_eliminar_posicion`       |  $O(n)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_buscar`       |  $O(n x la complejidad del comparador)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_con_cada_elemento`       |  $O(n x complejidad de f)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_destruir_todo`       |  $O(n x complejidad del destructor)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_destruir`       |  $O(n)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_iterador_crear`       |  $O(1)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_iterador_hay_mas_elementos`       |  $O(1)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_iterador_avanzar`       |  $O(1)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_iterador_actual`       |  $O(1)$ |Tiene como parámetro... y se encarga de....     |
|      `lista_iterador_destruir`       |  $O(1)$ |Tiene como parámetro... y se encarga de....     |
## 4. Decisiones de diseño y/o complejidades de implementación
Explicar las decisiones de diseño y/o las complejidades de implementación que hubo durante la resolución del TP.

## 4. Decisiones de diseño y/o complejidades de implementación (EJEMPLO)
La mayor complejidad en el TP se encuentra en la función `foo` que requiere hacer...; es por esto que decidí.... Además, decidí que el programa haga... para mejorar la implementación.

## 5. Respuestas a las preguntas teóricas
Deberás incluir en esta sección las respuestas a las preguntas teóricas indicadas en el [enunciado](./ENUNCIADO.md) del TP.

## 5. Respuestas a las preguntas teóricas (EJEMPLO)

### 5.1. ¿Porqué...?
Respondido en su respectiva sección.

### 5.2 ¿Cómo...?
Para implementar el....

### 5.3 ¿Cuál fue el...?
El motivo fue....
