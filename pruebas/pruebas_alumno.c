#include "pa2m.h"
#include <stdio.h>
#include "../src/lista.h"
#include "../src/pila.h"
#include "../src/cola.h"

static int comparar_enteros(const void *puntero_A, const void *puntero_B)
{
	if (!puntero_A && !puntero_B)
		return 0;

	if (!puntero_A)
		return -1;

	if (!puntero_B)
		return 1;

	const int *entero_A = (const int *)puntero_A;
	const int *entero_B = (const int *)puntero_B;

	if (*entero_A < *entero_B)
		return -1;

	if (*entero_A > *entero_B)
		return 1;

	return 0;
}

static bool funcion_false(void *ptr1, void *ptr2)
{
	return false;
}

void prueba_lista_insertar_NULL()
{
	lista_t *lista = lista_crear();
	lista_t *lista_recuperada = lista_insertar(lista, NULL);
	pa2m_afirmar(lista_recuperada != NULL,
		     "Insertar un elemento NULL a una lista.");
	lista_destruir(lista);
}

void prueba_lista_destruir_todo_sin_destructor()
{
	int elemento = 1;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento);

	lista_destruir_todo(lista, NULL);

	pa2m_afirmar(
		true,
		"Se elimina una lista pasando un destructor NULL, y no hay error.");
}

void prueba_lista_obtener_sin_eliminar()
{
	int elemento = 1;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento);

	lista_obtener(lista);

	pa2m_afirmar(
		lista_cantidad(lista) == 1,
		"Se obtiene un elemento de una lista con lista_obtener sin que este se elimine de la lista.");
	lista_destruir(lista);
}

void prueba_buscar_posicion_NULL()
{
	int elemento = 1;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento);

	bool esta_el_uno =
		lista_buscar(lista, &elemento, comparar_enteros, NULL);

	pa2m_afirmar(
		esta_el_uno,
		"La función devuelve true si está el elemento, incluso si el puntero posición es NULL.");
	lista_destruir(lista);
}

void prueba_buscar_posicion_elemento_repetido()
{
	int elemento_primero = 1;
	int elemento_segundo = 1;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento_primero);

	size_t posicion_elemento = 0;
	bool esta_el_uno = lista_buscar(lista, &elemento_segundo,
					comparar_enteros, &posicion_elemento);

	pa2m_afirmar(
		esta_el_uno && (posicion_elemento == 0),
		"Se logra diferenciar entre el valor de los elementos y sus punteros a la hora de comparar.");
	lista_destruir(lista);
}

void prueba_lista_eliminar_e_insertar_seguidamente()
{
	int elemento_primero = 1;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento_primero);
	lista_eliminar(lista);
	int elemento_segundo = 2;
	lista_insertar(lista, &elemento_segundo);
	int *elemento_recuperado = lista_obtener(lista);

	pa2m_afirmar(
		*elemento_recuperado == elemento_segundo &&
			lista_cantidad(lista) == 1,
		"Se logra agregar, eliminar y volver a cargar elementos a la lista sin tener errores.");
	lista_destruir(lista);
}

void prueba_lista_insertar_posicion_fuera_de_rango()
{
	int elemento_primero = 1;
	int elemento_segundo = 2;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento_primero);
	lista_insertar_posicion(lista, 100, &elemento_segundo);
	int *elemento_recuperado = lista_obtener(lista);

	pa2m_afirmar(
		*elemento_recuperado == elemento_segundo &&
			lista_cantidad(lista) == 2,
		"Se logra agregar al final un elemento al pasarle una posicion mayor a las existentes.");
	lista_destruir(lista);
}

void prueba_lista_eliminar_posicion_fuera_de_rango()
{
	int elemento_primero = 1;
	int elemento_segundo = 2;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento_primero);
	lista_insertar(lista, &elemento_segundo);
	int *elemento_recuperado = lista_eliminar_posicion(lista, 100);

	pa2m_afirmar(
		!elemento_recuperado && lista_cantidad(lista) == 2,
		"Si se pide eliminar una posicion inexistente se devuelve NULL y se deja la lista como estaba.");
	lista_destruir(lista);
}

void prueba_lista_eliminar_primer_elemento()
{
	int elemento_primero = 1;
	int elemento_segundo = 2;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento_primero);
	lista_insertar(lista, &elemento_segundo);
	lista_eliminar_posicion(lista, 0);
	int *elemento_recuperado = lista_obtener_posicion(lista, 0);

	pa2m_afirmar(
		*elemento_recuperado == elemento_segundo,
		"Si se pide eliminar el primer elemento, luego al leer el primer elemento obtenemos el segundo.");
	lista_destruir(lista);
}

void prueba_lista_eliminar_elemento_intermedio()
{
	int elemento_primero = 1;
	int elemento_segundo = 2;
	int elemento_tercero = 3;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento_primero);
	lista_insertar(lista, &elemento_segundo);
	lista_insertar(lista, &elemento_tercero);
	lista_eliminar_posicion(lista, 1);
	int *elemento_recuperado = lista_obtener_posicion(lista, 1);

	pa2m_afirmar(
		*elemento_recuperado == elemento_tercero,
		"Se elimina un elemento intermedio de la lista sin problemas, y su posición pasa a ser ocupada por el siguiente.");
	lista_destruir(lista);
}

void prueba_lista_con_cada_elemento_false()
{
	int elemento = 1;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento);

	size_t cant_evaluada =
		lista_con_cada_elemento(lista, funcion_false, NULL);

	pa2m_afirmar(
		cant_evaluada == 1,
		"Se devuelve la cantidad correcta de elementos evaluados cuando se devuelve siempre false y se paso un extra NULL.");
	lista_destruir(lista);
}

void prueba_iterador_actual_lista_vacia()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);
	void *elemento_actual = lista_iterador_actual(iterador);

	pa2m_afirmar(
		!elemento_actual,
		"Se puede pedirle el elemento actual a un iterador de una lista vacia sin que se rompa nada.");
	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void prueba_iterador_avanzar_de_mas()
{
	int elemento_primero = 1;
	int elemento_segundo = 2;
	int elemento_tercero = 3;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento_primero);
	lista_insertar(lista, &elemento_segundo);
	lista_insertar(lista, &elemento_tercero);

	lista_iterador_t *iterador = lista_iterador_crear(lista);
	lista_iterador_avanzar(iterador);
	lista_iterador_avanzar(iterador);
	lista_iterador_avanzar(iterador);
	lista_iterador_avanzar(iterador);
	void *elemento_actual = lista_iterador_actual(iterador);

	pa2m_afirmar(
		!elemento_actual,
		"Se puede iterar pasandose de la cantidad real de elementos de la lista sin que se rompa nada, cuando pedimos el elemento actual da NULL.");
	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void prueba_iterador_destruir_con_lista_viva()
{
	int elemento = 1;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &elemento);
	lista_iterador_t *iterador = lista_iterador_crear(lista);
	lista_iterador_destruir(iterador);
	int *elemento_recuperado = lista_obtener(lista);

	pa2m_afirmar(
		elemento == *elemento_recuperado,
		"Se puede destruir el iterador de una lista sin que esta deje de funcionar.");
	lista_destruir(lista);
}

void prueba_iterador_avanzar_lista_vacia()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	lista_iterador_avanzar(iterador);
	pa2m_afirmar(
		true,
		"Se puede intentar avanzar en un iterador de una lista vacía sin que se rompa nada.");
	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void prueba_iterador_colgante()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
	pa2m_afirmar(
		true,
		"Se puede destruir primero la lista y luego el iterador sin que se rompa nada.");
}

void prueba_iterador_hay_mas_elementos_lista_vacia()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	bool hay_mas_elementos = lista_iterador_hay_mas_elementos(iterador);

	pa2m_afirmar(
		!hay_mas_elementos,
		"Se puede crear un iterador a partir de una lista vacía y si preguntamos si tiene elementos nos de false.");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void prueba_iterador_hay_mas_elementos_NULL()
{
	lista_t *lista = lista_crear();
	lista_insertar(lista, NULL);

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	bool hay_mas_elementos = lista_iterador_hay_mas_elementos(iterador);

	pa2m_afirmar(
		hay_mas_elementos,
		"Se comunica que si hay elementos cuando usamos la función con una lista que tiene 1 elemento NULL.");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void pruebas_todas_las_funciones_NULL()
{
	lista_vacia(NULL);
	lista_cantidad(NULL);
	lista_insertar(NULL, NULL);
	lista_insertar_posicion(NULL, 0, NULL);
	lista_obtener(NULL);
	lista_obtener_posicion(NULL, 0);
	lista_eliminar(NULL);
	lista_eliminar_posicion(NULL, 0);
	lista_buscar(NULL, NULL, NULL, NULL);
	lista_con_cada_elemento(NULL, NULL, NULL);
	lista_destruir_todo(NULL, NULL);
	lista_destruir(NULL);

	lista_iterador_crear(NULL);
	lista_iterador_hay_mas_elementos(NULL);
	lista_iterador_avanzar(NULL);
	lista_iterador_actual(NULL);
	lista_iterador_destruir(NULL);

	pa2m_afirmar(
		true,
		"Todas las funciones resisten recibir punteros NULL sin dar seg faults.");
}

void pruebas_lista_eliminar()
{
	prueba_lista_eliminar_e_insertar_seguidamente();
	prueba_lista_eliminar_elemento_intermedio();
	prueba_lista_eliminar_posicion_fuera_de_rango();
	prueba_lista_eliminar_primer_elemento();
}

void pruebas_iterador_externo()
{
	prueba_iterador_hay_mas_elementos_NULL();
	prueba_iterador_hay_mas_elementos_lista_vacia();
	prueba_iterador_destruir_con_lista_viva();
	prueba_iterador_colgante();
	prueba_iterador_avanzar_lista_vacia();
	prueba_iterador_avanzar_de_mas();
	prueba_iterador_actual_lista_vacia();
}

void pruebas_lista_buscar()
{
	prueba_buscar_posicion_elemento_repetido();
	prueba_buscar_posicion_NULL();
}

void pruebas_lista_obtener()
{
	prueba_lista_obtener_sin_eliminar();
}

void pruebas_lista_insertar()
{
	prueba_lista_insertar_NULL();
	prueba_lista_insertar_posicion_fuera_de_rango();
}

void pruebas_lista_destruir_todo()
{
	prueba_lista_destruir_todo_sin_destructor();
}

void pruebas_iterador_interno()
{
	prueba_lista_con_cada_elemento_false();
}

//PRUEBAS DE PILA

void pruebas_pila_resistir_NULL()
{
	pila_apilar(NULL, NULL);
	pila_desapilar(NULL);
	pila_tope(NULL);
	pila_cantidad(NULL);
	pila_destruir(NULL);
	pila_destruir_todo(NULL, NULL);
	pa2m_afirmar(
		true,
		"Las primitivas del TDA pila pueden recibir punteros NULL sin dar segmentation fault.");
}

void prueba_pila_destructor_nulo()
{
	pila_t *pila = pila_crear();
	int elemento = 1;
	pila_apilar(pila, &elemento);
	pila_destruir_todo(pila, NULL);
	pa2m_afirmar(
		true,
		"Se puede usar la función usando un destructor NULL sin que se rompa nada.");
}

void prueba_tope_pila_vacia()
{
	pila_t *pila = pila_crear();
	void *tope = pila_tope(pila);
	pa2m_afirmar(tope == NULL, "Se puede usar tope con una pila vacia.");
	pila_destruir(pila);
}

void prueba_apilar_elemento_NULL()
{
	pila_t *pila = pila_crear();
	pila_apilar(pila, NULL);
	void *elemento_recuperado = pila_tope(pila);
	pa2m_afirmar(pila_cantidad(pila) == 1 && elemento_recuperado == NULL,
		     "Se puede apilar un elemento NULL.");
	pila_destruir(pila);
}

void prueba_desapilar_el_ultimo()
{
	pila_t *pila = pila_crear();
	int elemento_primero = 1;
	int elemento_segundo = 2;
	int elemento_tercero = 3;
	pila_apilar(pila, &elemento_primero);
	pila_apilar(pila, &elemento_segundo);
	pila_apilar(pila, &elemento_tercero);
	int *primer_recuperado = pila_desapilar(pila);
	int *segundo_recuperado = pila_desapilar(pila);
	int *tercer_recuperado = pila_desapilar(pila);

	pa2m_afirmar(*primer_recuperado == elemento_tercero &&
			     *segundo_recuperado == elemento_segundo &&
			     *tercer_recuperado == elemento_primero &&
			     pila_cantidad(pila) == 0,
		     "Se desapila el último elemento en haber sido apilado.");
	pila_destruir(pila);
}

void prueba_pila_tope_no_quita_elementos()
{
	pila_t *pila = pila_crear();
	int elemento_primero = 1;
	pila_apilar(pila, &elemento_primero);
	int *elemento_recuperado = pila_tope(pila);

	pa2m_afirmar(*elemento_recuperado == elemento_primero &&
			     pila_cantidad(pila) == 1,
		     "La función pila_tope no quita elementos de la pila.");
	pila_destruir(pila);
}

void prueba_pila_destruir_no_libera_elementos()
{
	pila_t *pila = pila_crear();
	int *elemento_primero = calloc(1, sizeof(int));
	pila_apilar(pila, elemento_primero);
	pila_destruir(pila);

	pa2m_afirmar(elemento_primero != NULL && *elemento_primero == 0,
		     "Se puede destruir la pila sin destruir sus elementos.");
	free(elemento_primero);
}

//PRUEBAS DE COLA
void pruebas_cola_resistir_NULL()
{
	cola_encolar(NULL, NULL);
	cola_desencolar(NULL);
	cola_frente(NULL);
	cola_cantidad(NULL);
	cola_destruir(NULL);
	cola_destruir_todo(NULL, NULL);

	pa2m_afirmar(
		true,
		"Todas las primitivas del TDA cola resisten el puntero NULL sin dar segmentation fault.");
}

void prueba_cola_FIFO()
{
	cola_t *cola = cola_crear();
	int elemento_primero = 1;
	int elemento_segundo = 2;
	int elemento_tercero = 3;
	cola_encolar(cola, &elemento_primero);
	cola_encolar(cola, &elemento_segundo);
	cola_encolar(cola, &elemento_tercero);
	int *primer_recuperado = cola_desencolar(cola);
	int *segundo_recuperado = cola_desencolar(cola);
	int *tercer_recuperado = cola_desencolar(cola);

	pa2m_afirmar(elemento_primero == *primer_recuperado &&
			     elemento_segundo == *segundo_recuperado &&
			     elemento_tercero == *tercer_recuperado,
		     "El TDA cola respeta el principio FIFO.");
	cola_destruir(cola);
}

void prueba_cola_frente_no_quita_elementos()
{
	cola_t *cola = cola_crear();
	int elemento = 1;
	cola_encolar(cola, &elemento);
	int *elemento_recuperado = cola_frente(cola);

	pa2m_afirmar(elemento == *elemento_recuperado &&
			     cola_cantidad(cola) == 1,
		     "Usar cola_frente no quita elementos de la cola");
	cola_destruir(cola);
}

void prueba_cola_encolar_NULL()
{
	cola_t *cola = cola_crear();
	cola_encolar(cola, NULL);
	void *elemento_recuperado = cola_frente(cola);

	pa2m_afirmar(elemento_recuperado == NULL && cola_cantidad(cola) == 1,
		     "Se puede encolar un elemento NULL.");
	cola_destruir(cola);
}

void prueba_cola_destruir_todo_destructor_NULL()
{
	cola_t *cola = cola_crear();
	cola_destruir_todo(cola, NULL);

	pa2m_afirmar(
		true,
		"Se puede usar cola_destruir_todo con un destructor NULL sin que de segmentation fault");
}

void prueba_cola_destruir_no_libera_elementos()
{
	cola_t *cola = cola_crear();
	int *elemento = calloc(1, sizeof(int));

	cola_encolar(cola, elemento);
	cola_destruir(cola);

	pa2m_afirmar(*elemento == 0,
		     "Cola_destruir no libera elementos al destruir la cola.");
	free(elemento);
}

void prueba_cola_cantidad_devuelve_para_cola_vacia()
{
	cola_t *cola = cola_crear();
	size_t cant = cola_cantidad(cola);

	pa2m_afirmar(cant == 0,
		     "cola_cantidad devuelve cero para una cola vacia.");
	cola_destruir(cola);
}

void prueba_cola_frente_con_lista_vacia()
{
	cola_t *cola = cola_crear();
	void *frente = cola_frente(cola);

	pa2m_afirmar(
		frente == NULL,
		"Usar cola_frente con una cola vacia no da segmentation fault, y devuelve NULL.");
	cola_destruir(cola);
}

void prueba_cola_desencolar_lista_vacia()
{
	cola_t *cola = cola_crear();
	void *elemento_recuperado = cola_desencolar(cola);

	pa2m_afirmar(
		elemento_recuperado == NULL,
		"Se puede usar cola_desencolar con una lista vacia sin que de segmentation fault, y devuelve NULL.");
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS DEL TP X ===============");

	pa2m_nuevo_grupo("Pruebas de lista con punteros NULL");
	pruebas_todas_las_funciones_NULL();

	pa2m_nuevo_grupo("Pruebas de lista_iterador");
	pruebas_iterador_externo();

	pa2m_nuevo_grupo("Pruebas de lista_eliminar y lista_eliminar_posicion");
	pruebas_lista_eliminar();

	pa2m_nuevo_grupo("Pruebas de lista_insertar");
	pruebas_lista_insertar();

	pa2m_nuevo_grupo("Pruebas de lista_obtener");
	pruebas_lista_obtener();

	pa2m_nuevo_grupo("Pruebas de lista_buscar");
	pruebas_lista_buscar();

	pa2m_nuevo_grupo("Pruebas de pila con punteros NULL");
	pruebas_pila_resistir_NULL();

	pa2m_nuevo_grupo("Pruebas de pila_destruir_todo");
	prueba_pila_destructor_nulo();

	pa2m_nuevo_grupo("Pruebas de pila_destruir");
	prueba_pila_destruir_no_libera_elementos();

	pa2m_nuevo_grupo("Pruebas pila_tope");
	prueba_pila_tope_no_quita_elementos();
	prueba_tope_pila_vacia();

	pa2m_nuevo_grupo("Pruebas pila_desapilar");
	prueba_desapilar_el_ultimo();

	pa2m_nuevo_grupo("Pruebas pila_apilar");
	prueba_apilar_elemento_NULL();

	pa2m_nuevo_grupo("Pruebas de cola con punteros NULL");
	pruebas_cola_resistir_NULL();

	pa2m_nuevo_grupo("Pruebas cola_desencolar");
	prueba_cola_FIFO();
	prueba_cola_desencolar_lista_vacia();

	pa2m_nuevo_grupo("Pruebas cola_frente");
	prueba_cola_frente_no_quita_elementos();
	prueba_cola_frente_con_lista_vacia();

	pa2m_nuevo_grupo("Pruebas cola_encolar");
	prueba_cola_encolar_NULL();

	pa2m_nuevo_grupo("Pruebas cola_destruir_todo");
	prueba_cola_destruir_todo_destructor_NULL();

	pa2m_nuevo_grupo("Pruebas cola_destruir");
	prueba_cola_destruir_no_libera_elementos();

	pa2m_nuevo_grupo("Pruebas cola_cantidad");
	prueba_cola_cantidad_devuelve_para_cola_vacia();

	return pa2m_mostrar_reporte();
}
