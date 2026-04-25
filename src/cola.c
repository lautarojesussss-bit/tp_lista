#include "lista.h"
#include "cola.h"

struct cola {
	lista_t *lista;
};

/**
 * Crea una cola
 */
cola_t *cola_crear()
{
	cola_t *cola = malloc(sizeof(cola_t));
	if (!cola)
		return NULL;

	cola->lista = lista_crear();

	if (!cola->lista) {
		free(cola);
		return NULL;
	}

	return cola;
}

/**
 * Encola un elemento. Devuelve la cola o NULL en caso de error.
 */
cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if (!cola)
		return NULL;

	if (!lista_insertar(cola->lista, elemento))
		return NULL;

	return cola;
}

/**
 * Desencola un elemento. Devuelve el elemento desencolado o NULL en caso de error.
 */
void *cola_desencolar(cola_t *cola)
{
	if (!cola)
		return NULL;

	return lista_eliminar_posicion(cola->lista, 0);
}

/**
 * Devuelve el primer elemento de la cola o NULL en caso de error.
 */
void *cola_frente(cola_t *cola)
{
	if (!cola)
		return NULL;

	return lista_obtener_posicion(cola->lista, 0);
}

/**
 * Devuelve la cantidad de elementos en la cola.
 */
size_t cola_cantidad(cola_t *cola)
{
	if (!cola)
		return 0;

	return lista_cantidad(cola->lista);
}

/**
 * Destruye la cola
 */
void cola_destruir(cola_t *cola)
{
	if (!cola)
		return;

	lista_destruir(cola->lista);
	free(cola);
}

/**
 * Destruye la cola aplicando la función destructora a cada elemento.
 */
void cola_destruir_todo(cola_t *cola, void (*destructor)(void *))
{
	if (!cola)
		return;

	lista_destruir_todo(cola->lista, destructor);
	free(cola);
}