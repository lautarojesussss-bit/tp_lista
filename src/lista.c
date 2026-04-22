#include "lista.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *primero;
	nodo_t *ultimo;
	size_t cantidad;
};

struct lista_iterador {
	nodo_t *nodo_actual;
};

lista_t *lista_crear(void)
{
	return calloc(1, sizeof(lista_t));
}

bool lista_vacia(lista_t *lista)
{
	if (!lista)
		return true;

	return (lista->cantidad == 0);
}

size_t lista_cantidad(lista_t *lista)
{
	if (!lista)
		return 0;

	return lista->cantidad;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;

	if (lista_vacia(lista))
		lista->primero = nuevo_nodo;
	else
		lista->ultimo->siguiente = nuevo_nodo;

	lista->ultimo = nuevo_nodo;
	lista->cantidad++;
	return lista;
}

static nodo_t *obtener_nodo(lista_t *lista, size_t posicion)
{
	if (lista_vacia(lista) || posicion >= lista->cantidad)
		return NULL;

	nodo_t *nodo_aux = lista->primero;

	for (size_t i = 0; i < posicion; i++)
		nodo_aux = nodo_aux->siguiente;

	return nodo_aux;
}

lista_t *lista_insertar_posicion(lista_t *lista, size_t posicion,
				 void *elemento)
{
	if (!lista)
		return NULL;

	if (posicion >= lista->cantidad)
		return lista_insertar(lista, elemento);

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;

	if (posicion == 0) {
		nuevo_nodo->siguiente = lista->primero;
		lista->primero = nuevo_nodo;
	} else {
		nodo_t *nodo_de_atras = obtener_nodo(lista, posicion - 1);
		nuevo_nodo->siguiente = nodo_de_atras->siguiente;
		nodo_de_atras->siguiente = nuevo_nodo;
	}

	lista->cantidad++;
	return lista;
}

void *lista_obtener(lista_t *lista)
{
	if (lista_vacia(lista))
		return NULL;

	return lista->ultimo->elemento;
}

void *lista_obtener_posicion(lista_t *lista, size_t posicion)
{
	if (lista_vacia(lista) || posicion >= lista->cantidad)
		return NULL;

	nodo_t *nodo_aux = obtener_nodo(lista, posicion);

	return nodo_aux->elemento;
}

void *lista_eliminar(lista_t *lista)
{
	if (lista_vacia(lista))
		return NULL;

	return lista_eliminar_posicion(lista, lista->cantidad - 1);
}

void *lista_eliminar_posicion(lista_t *lista, size_t posicion)
{
	if (lista_vacia(lista) || posicion >= lista->cantidad)
		return NULL;

	nodo_t *nodo_a_eliminar = NULL;

	if (posicion == 0) {
		nodo_a_eliminar = lista->primero;
		lista->primero = lista->primero->siguiente;

		if (!lista->primero)
			lista->ultimo = NULL;

	} else {
		nodo_t *nodo_de_atras = obtener_nodo(lista, posicion - 1);
		nodo_a_eliminar = nodo_de_atras->siguiente;
		nodo_de_atras->siguiente = nodo_a_eliminar->siguiente;

		if (!(nodo_a_eliminar->siguiente))
			lista->ultimo = nodo_de_atras;
	}

	void *elemento_a_extraer = nodo_a_eliminar->elemento;
	free(nodo_a_eliminar);
	lista->cantidad--;

	return elemento_a_extraer;
}

bool lista_buscar(lista_t *lista, void *elemento,
		  int (*comparador)(const void *, const void *),
		  size_t *posicion)
{
	if (lista_vacia(lista) || !comparador)
		return false;

	bool se_encontro = false;
	size_t i = 0;
	nodo_t *nodo_actual = lista->primero;

	while (!se_encontro && nodo_actual) {
		se_encontro = comparador(nodo_actual->elemento, elemento) == 0;

		if (!se_encontro) {
			nodo_actual = nodo_actual->siguiente;
			i++;
		}
	}

	if (se_encontro && posicion)
		*posicion = i;

	return se_encontro;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*f)(void *, void *),
			       void *extra)
{
	if (lista_vacia(lista) || !f)
		return 0;

	size_t cant_afectada = 0;
	nodo_t *nodo_actual = lista->primero;
	bool continuar = true;

	while (nodo_actual && continuar) {
		continuar = f(nodo_actual->elemento, extra);
		nodo_actual = nodo_actual->siguiente;
		cant_afectada++;
	}

	return cant_afectada;
}

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
	if (!lista)
		return;

	nodo_t *nodo_actual = lista->primero;

	while (nodo_actual) {
		nodo_t *nodo_siguiente = nodo_actual->siguiente;

		if (destructor)
			destructor(nodo_actual->elemento);

		free(nodo_actual);
		nodo_actual = nodo_siguiente;
	}

	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	lista_iterador_t *nuevo_iterador = malloc(sizeof(lista_iterador_t));

	if (!nuevo_iterador)
		return NULL;

	nuevo_iterador->nodo_actual = lista->primero;
	return nuevo_iterador;
}

bool lista_iterador_hay_mas_elementos(lista_iterador_t *it)
{
	if (!it)
		return false;

	return it->nodo_actual;
}

void lista_iterador_avanzar(lista_iterador_t *it)
{
	if (!it || !lista_iterador_hay_mas_elementos(it))
		return;

	it->nodo_actual = it->nodo_actual->siguiente;
}

void *lista_iterador_actual(lista_iterador_t *it)
{
	if (!it || !lista_iterador_hay_mas_elementos(it))
		return NULL;

	return it->nodo_actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *it)
{
	free(it);
}