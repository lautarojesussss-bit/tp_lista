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

Los siguientes analisis de complejidad temporal asintótica se realizan bajo la premisa de que la variable n representa la cantidad de elementos del TDA.

#### 3.2.1 Lista
A continuación se detallan las complejidades de todas las primitivas del TDA `lista`

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `lista_crear`       |  $O(1)$   |Se reserva memoria para una lista vacía, con 0 elementos.|
|      `lista_vacia`       |  $O(1)$   |Solo se compara el campo `cantidad` de la lista|
|      `lista_cantidad`       |  $O(1)$ |Solo se retorna el campo `cantidad` de la lista|
|      `lista_insertar`       |  $O(1)$ |Al tener una referencia directa al último nodo de la lista la operación es constante, ya que enlazar un nodo al final se resume en cambiar dos referencias: el campo `siguiente` del ultimo nodo y el campo `ultimo` de la `lista_t`, ambas operaciones se pueden hacer en tiempo constante sin importar la cantidad de elementos de la lista.  |
|      `lista_insertar_posicion`       |  $O(n)$ |En el peor de los casos, que es agregar un elemento en la ante última posición, la operación es lineal, ya que se debe editar el campo `siguiente` del ante penúltimo nodo de la lista, para lo cual cual es necesario pasar primero por todos los nodos anteriores, dado que las referencias entre nodos solo son en una dirección dentro de la lista.     |
|      `lista_obtener`       |  $O(1)$ |Como se dispone de una referencia directa al último nodo de la lista, se puede simplemente acceder a su campo `elemento`, en este caso para retornar ese valor. |
|      `lista_obtener_posicion`       |  $O(n)$ |En el peor de los casos, que es obtener el elemento de la ante última posición, es necesario pasar por todos los nodos de la lista, menos el último, porque las referencias entre nodos solo son en una dirección.|
|      `lista_eliminar`       |  $O(n)$ |Como para desenlazar un nodo es necesario alterar campos del nodo anterior al que se desenlaza, para desenlazar el último nodo de la lista es necesario acceder, y editar, el ante último nodo de la lista, cuyo acceso solo puede darse pasando primero por todos los nodos anterior. Por eso la operación es lineal.|
|      `lista_eliminar_posicion`       |  $O(n)$ |El peor caso de esta operación es que la posición a eliminar sea la última de la lista, cuya complejidad temporal es lineal, por lo cual la complejidad temporal asintótica de esta operación es lineal. |
|      `lista_buscar`       |  $O(N \cdot O(comparador))$  |En el peor de los casos el único elemento que coincide con el que se busca se encontraría en la última posición, dado que es necesario revisar toda la lista para saber si hay elementos que coincidan con el que busca, y que por cada elemento se utiliza la función `comparador` ,cuya complejidad temporal se desconoce, la complejidad temporal de la operación se deja expresada en función de la complejidad temporal del `comparador`. |
|      `lista_con_cada_elemento`       |  $O(N \cdot O(f))$  |En el peor de los casos la función `f` siempre da true, por lo cual la iteración sobre la lista es una iteración completa. La complejidad temporal es como mínimo lineal respecto al número de elementos, pero se deja expresada en función de la complejidad temporal de la función `f` dado que al elemento de cada nodo se le aplica esta función.|
|      `lista_destruir_todo`       |  $O(N \cdot O(destructor))$  |La iteración sobre la lista en esta operación siempre es una iteración completa, y como a cada elemento se le aplica la función `destructor` se expresa la complejidad temporal en función de la complejdiad temporal del `destructor`, como mínimo la complejidad temporal de esta operación es lineal respecto al número de elementos.|
|      `lista_destruir`       |  $O(n)$ |Dado que a cada nodo de la lista, cuya memoria fue reservada de forma no simúltanea con el resto de la memoria, se le debe aplicar un free, antes de liberar la estructura `lista_t`, la complejidad temporal de la operación es lineal respecto al número de elementos de la lista.|
|      `lista_iterador_crear`       |  $O(1)$ |Solo se reserva memoria para un `lista_iterador_t` y se copia la referencia del primer nodo de la lista, amabas operaciones que se realizan en tiempo constante respecto al número de elementos de la lista. Por esto la complejidad temporal de la operación es constante.|
|      `lista_iterador_hay_mas_elementos`       |  $O(1)$ |Solo se lee y compara el nodo actual del iterador, para saber si es nulo o no, esta operación es constante respecto al número de elementos de la lista a partir de la cual se creó el iterador. Por esto la operación es de complejidad temporal constante.|
|      `lista_iterador_avanzar`       |  $O(1)$ |Solo se accede al campo `siguiente` del nodo actual del iterador, y se establece ese nodo como el nuevo nodo actual del iterador, estas son operaciones constantes respecto al número de elementos de la lista a partir de la cual se creó el iterador. Por esto la operación es de complejidad temporal constante.|
|      `lista_iterador_actual`       |  $O(1)$ |Solo se retorna el elemento del nodo actual del iterador, que es una operación constante respecto al número de elementos de la lista a partir de la cual se creó el iterador. Por esto la operación es de complejidad temporal constante.|
|      `lista_iterador_destruir`       |  $O(1)$ |Al destruir el iterador solo se libera la memoria de la estructura `lista_iterador_t`, que fue reservada en un solo calloc, por lo cual necesita un solo free, tanto la memoria de la lista, como la de sus nodos y elementos, no se liberan. Por esto la complejidad temporal de la operación es constante respecto a la cantidad de elementos de la lista a partir de la cual se creó el iterador.|

#### 3.2.2 Pila
A continuación se detallan las complejidades de todas las primitivas del TDA `Pila`. En este caso n representa la cantidad de elementos que tiene la lista interna de la pila.

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `pila_crear`       |  $O(1)$   |Solo se reserva memoria para un estructura `pila_t`, y se crea una `lista_t` vacía, ambas operaciones que se realizan en tiempo constante. Por esto la complejidad temporal de la operación es constante.|
|      `pila_apilar`       |  $O(1)$   |Siempre se agrega el nuevo elemento al comienzo de la lista interna de la pila, por lo cual siempre es una operación constante respecto al número de elementos que tiene la pila.|
|      `pila_desapilar`       |  $O(1)$ |Siempre se elimina el primer elemento de la lista interna de la pila, y esta operación, que solo altera a la `lista_t` y a su primer nodo, es de complejidad temporal constante respecto al número de elementos que tiene la pila (que es el número de elementos que tiene su lista interna).|
|      `pila_tope`       |  $O(1)$ |Siempre se retorna el elemento del primer nodo de la lista interna, y este acceso es siempre en tiempo constante. Por esto la complejidad temporal es constante.|
|      `pila_cantidad`       |  $O(1)$ |Siempre se devuelve el valor del campo `cantidad` de la lista interna de la pila. Por esto la complejidad temporal es constante.|
|      `pila_destruir`       |  $O(n)$ |Se utiliza la función `lista_destruir` con la lista interna de la pila, esa función tiene una complejidad temporal lineal respecto al número de elementos. Y lo demás que se realiza en la función se resume a un free, que se realiza en tiempo constante. Por esto la complejidad temporal de la operación es lineal.|
|      `pila_destruir_todo`       |  $O(N \cdot O(destructor))$  |Se utiliza la función `lista_destruir_todo` con la lista interna de la pila, y con el destructor recibido, dado que esta función tiene una complejidad que es como lineal, y que depende de la complejidad del destructor, y dado que en la operación `pila_destruir_todo` todo lo demás se resume a un free que se realiza en tiempo constante, la operación en su totalidad queda expresada como la complejidad temporal de `lista_destruir_todo`.|

#### 3.2.3 Cola
A continuación se detallan las complejidades de todas las primitivas del TDA `Cola`. En este caso n representa la cantidad de elementos que tiene la lista interna de la cola.

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `cola_crear`       |  $O(1)$   |Solo se reserva memoria para un estructura `cola_t`, y se crea una `lista_t` vacía, ambas operaciones que se realizan en tiempo constante. Por esto la complejidad temporal de la operación es constante.|
|      `cola_encolar`       |  $O(1)$   |Dado que se usa la función `lista_insertar` con la lista interna de la cola, la complejidad de `cola_encolar` es la complejidad de `lista_insertar`|
|      `cola_desencolar`       |  $O(1)$ |Siempre se elimina el primer nodo de la lista interna de la cola, y esto implica solo modificar dos referencias y hacer un free, operaciones que se realizan en tiempo constante respecto al número de elementos de la cola.|
|      `cola_frente`       |  $O(1)$ |Siempre se retorna el elemento del primer nodo de la lista interna, y este acceso es siempre en tiempo constante. Por esto la complejidad temporal es constante.|
|      `cola_cantidad`       |  $O(1)$ |Siempre se devuelve el valor del campo `cantidad` de la lista interna de la cola. Por esto la complejidad temporal es constante.|
|      `cola_destruir`       |  $O(n)$ |Se utiliza la función `lista_destruir` con la lista interna de la cola, esa función tiene una complejidad temporal lineal respecto al número de elementos. Y lo demás que se realiza en la función se resume a un free, que se realiza en tiempo constante. Por esto la complejidad temporal de la operación es lineal.|
|      `cola_destruir_todo`       |  $O(N \cdot O(destructor))$  |Se utiliza la función `lista_destruir_todo` con la lista interna de la cola, y con el destructor recibido. Dado que la función `lista_destruir_todo` tiene una complejidad que es como lineal, y que depende de la complejidad del destructor, y dado que en la operación `cola_destruir_todo` todo lo demás se resume a un free, que se realiza en tiempo constante, la operación en su totalidad queda expresada como la complejidad temporal de `lista_destruir_todo`.|

## 4. Decisiones de diseño y/o complejidades de implementación 

### 4.1 Extremo 'activo' de la pila
Se decidió usar como extremo 'activo' de la pila al extremo inicial de la lista interna de la pila, dado que así se puede cumplir con la reestricción de que la operación `pila_desapilar` se haga en tiempo constante.

### 4.2 Reutilización de código
Se decidió reciclar el código en algunas partes de la implementación de las primitivas de `lista_t`, principalmente en las operaciones `lista_eliminar` y `lista_destruir` que representan casos particulares de las operaciones `lista_eliminar_posicion` y `lista_destruir_todo`.

### 4.3 Avisos de errores (main)
Se decidió utilizar enums y prints personalizados para manejar los principales casos de errores del programa de la calculadora con notación polaca inversa.


## 5. Respuestas a las preguntas teóricas 

### 5.1. Explicar qué es una lista, lista enlazada y lista doblemente enlazada.
La `lista` es un conjunto TDAs, es muy famoso y muy utilizado en la industria del software, y los TDAs que lo poseen las siguientes caracteristicas (entiendase estas como el contrato básico de una lista):

1) Una clasificación elemental de los datos en "posiciones", que se asumen con un orden secuencial, es decir, la posición 0 está detrás de la 1, la 1 detrás de la 2... (los extremos, la primer y última posición, pueden no tener una posición anterior y siguiente, respectivamente). 

2) Una Inserción, eliminación y lectura/acceso arbitrarios, es decir, que se puede hacer estas operaciones en cualquier posición válida de la lista.

La `lista_enlazada` es un subconjunto del conjunto `lista`, estos TDAs, además de cumplir con el 'contrato' ya mencionado, deben hacerlo de una forma particular, mediante 'pedazos' individuales de memoria (llamados nodos) que contienen un elemento y una referencia a otro nodo. De esta forma la información total de la lista no está almacenada en un bloque contiguo de la memoria sina dispersa entre diferentes pedazos de memoria que están 'unidos' mediante referencias.

La `lista_doblemente_enlazada` es un subconjunto del conjunto `lista_enlazada`, cumple todo lo anterior mencionado, y además consta de una caracteristica especial respecto a la cantidad de referencias que posee cada nodo. En la `lista_doblemente_enlazada` cada nodo debe contar, por lo mínimo, con una referencia al nodo anterior y una referencia al nodo siguiente. Este detalle garantiza que se pueda iterar entre los elementos (mediante sus nodos) en dos direcciones dentro de la lista.

Cabe aclarar que dado que la relación que existe entre estos conjuntos es de inclusión estricta, hacer una comparación de ventajas y desventajas resulta inconducente. Al ser el conjunto `lista` el que posee todos los TDAs de los otros dos conjuntos más muchos otros, es este el que posee todas las ventajas teóricas (posibilidades), pero no necesariamente todas las limitaciones de sus subconjuntos.

<div align="center">
  <img src="img/diagramas_respuestas_teoricas/listas_conjuntos_0.svg" width="70%">
  <p>Diagrama de Euler de la relación entre lista, lista enlazada y lista doblemente enlazada.</p>
</div>



### 5.2 Explicar qué es una lista circular y de qué maneras se puede implementar.
La `lista_circular` es una de las variantes de la `lista`, o sea, un subconjunto de `lista`. En esta se implementa una reestricción extra en relación al orden relativo de los extremos de la lista, estos deben tener ambos una posición anterior y posterior (o siguiente), especificamente la posición anterior a la primera posición debe ser la última posición, y la posición posterior de la última posición debe ser la primera posición.
Una de las formas más intuitivas de implementar una `lista_circular` es tomando una lista simplemente enlazada y agregarle al último nodo una referencia al primero.
También es posible implementar una lista circular sin necesidad de una lista enlazada, es decir, por medio de un bloque contiguo de memoria y usando una operación especial para calcular la posición siguiente, por ej POS_SIGUIENTE = (POS_ACTUAL + 1) % TAMAÑO_LISTA 

<div align="center">
  <img src="img/diagramas_respuestas_teoricas/diagrama_memoria_lista_simplemente_enlazada_circular_2.svg" width="70%">
  <p>Diagrama de memoria de una lista circular simplemente enlazada.</p>
</div>

### 5.3 Explicar la diferencia de funcionamiento entre cola y pila.
El motivo fue....

### 5.4 Explicar la diferencia de funcionamiento entre cola y pila.
El motivo fue....
