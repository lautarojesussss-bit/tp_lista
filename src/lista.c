#include "lista.h"

typedef struct nodo{
        void *elemento;
        struct nodo *siguiente;
} nodo_t;

struct lista{
        nodo_t *primero;
        nodo_t *ultimo;
        size_t cantidad;
};

struct lista_iterador{
        nodo_t *nodo_actual;
};

lista_t *lista_crear(void)
{
        return calloc(1, sizeof(lista_t));
}

bool lista_vacia(lista_t *lista)
{
        if(!lista)
                return true;

        return (lista->cantidad == 0);
}

size_t lista_cantidad(lista_t *lista)
{
        if(!lista)
                return 0;

        return lista->cantidad;
}

/**
 * Inserta un elemento al final de la lista.
 *
 * Devuelve la lista o NULL en caso de error.
 */
lista_t *lista_insertar(lista_t *lista, void *elemento)
{
        if (!lista)
                return NULL;

        nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
        if(!nuevo_nodo)
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


/**
 * Inserta un elemento en la posición dada de la lista.
 *
 * Si se intenta insertar en una posición inexistente, se inserta al final. Devuelve la lista o NULL en caso de error.
 */
lista_t *lista_insertar_posicion(lista_t *lista, size_t posicion, void *elemento)
{
        if(!lista)
                return NULL;

        size_t cant = lista_cantidad(lista);
        if(posicion >= cant)
                return lista_insertar(lista, elemento);

        nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
        if(!nuevo_nodo)
                return NULL;

        nuevo_nodo->elemento = elemento;


        if (posicion == 0) {
                nuevo_nodo->siguiente = lista->primero;
                lista->primero = nuevo_nodo;
                lista->cantidad++;
                return lista;
        }
        

        size_t pos_aux = 0;
        nodo_t *nodo_aux = lista->primero;

        for (; pos_aux < posicion-1; pos_aux++)
                nodo_aux = nodo_aux->siguiente;

        nuevo_nodo->siguiente = nodo_aux->siguiente;
        nodo_aux->siguiente = nuevo_nodo;
        lista->cantidad++;
        return lista;
}

/**
 * Devuelve el último elemento de la lista (si existe). En caso de error devuelve NULL.
 */
void *lista_obtener(lista_t *lista)
{
        if(!lista || lista_vacia(lista))
                return NULL;

        return lista->ultimo->elemento;
}

/**
 * Dada una posición de la lista, devuelve el elemento en esa posicion. En caso de error devuelve NULL.
 */
void *lista_obtener_posicion(lista_t *lista, size_t posicion)
{
        if(!lista || posicion >= lista_cantidad(lista))
                return NULL;

        size_t pos_aux = 0;

        nodo_t *nodo_aux = lista->primero;

        for (; pos_aux < posicion; pos_aux++)
                nodo_aux = nodo_aux->siguiente;

        return nodo_aux->elemento;
}

/**
 * Elimina el último elemento de la lista (si existe) y lo devuelve.
 *
 * En caso de error devuelve NULL
 */
void *lista_eliminar(lista_t *lista)
{
        size_t cant = lista_cantidad(lista);

        if(!lista || cant == 0)
                return NULL;
        
        
        nodo_t *nodo_aux = lista->primero;
        void *elemento_aux = NULL;

        if (cant == 1) {
                elemento_aux = lista->primero->elemento;
                free(lista->primero);
                lista->primero = NULL;
                lista->ultimo = NULL;
                lista->cantidad--;
                return elemento_aux;
        }
        
        size_t pos_aux = 0;
        for (; pos_aux < cant-2; pos_aux++)
                nodo_aux = nodo_aux->siguiente;

        elemento_aux = nodo_aux->siguiente->elemento;
        free(nodo_aux->siguiente);
        nodo_aux->siguiente = NULL;
        lista->ultimo = nodo_aux;
        lista->cantidad--;

        return elemento_aux;
}


/**
 * Elimina un elemento de la lista en la posición dada. Devuelve el elemento eliminado si la posición es válida.
 *
 * En caso de error devuelve NULL
 */
void *lista_eliminar_posicion(lista_t *lista, size_t posicion)
{
        size_t cant = lista_cantidad(lista);

        if(!lista || posicion >= cant)
                return NULL;

        nodo_t *nodo_aux = lista->primero;
        void *elemento_aux = NULL;

        if (posicion == 0) {
                elemento_aux = lista->primero->elemento;
                lista->primero = lista->primero->siguiente;
                free(nodo_aux);
                lista->cantidad--;
                if(cant == 1)
                        lista->ultimo = NULL;
                return elemento_aux;
        }
        

        size_t pos_aux = 0;
        for (; pos_aux < posicion -1; pos_aux++)
                nodo_aux = nodo_aux->siguiente;

        elemento_aux = nodo_aux->siguiente->elemento;
        nodo_t * nodo_a_eliminar = nodo_aux->siguiente;
        nodo_aux->siguiente = nodo_aux->siguiente->siguiente;
        free(nodo_a_eliminar);

        if(posicion == cant -1)
                lista->ultimo = nodo_aux;

        lista->cantidad--;
        return elemento_aux;
}

/**
 * Busca un elemento en la lista secuencialmente y devuelve true si lo encuentra. 
 * Si posicion es no nulo, almacena la posición del primer elemento encontrado.
 *
 * Si no existe el elemento devuelve false y no se modifica posición.
 */
bool lista_buscar(lista_t *lista, void *elemento,
		  int (*comparador)(const void *, const void *),
		  size_t *posicion)
{
        size_t cant = lista_cantidad(lista);
        if(!lista || !comparador || cant == 0)
                return false;
        
        bool se_encontro = false;
        size_t i = 0;
        nodo_t *nodo_aux = lista->primero;

        for (; !se_encontro && i < cant; i++) {
                se_encontro = comparador(nodo_aux->elemento, elemento) == 0;
                nodo_aux = nodo_aux->siguiente;
        }
        
        if (se_encontro && posicion)
                *posicion = i-1;
        
        return se_encontro;
}


/**
 * Recorre los elementos de la lista y aplica a cada uno la función f.
 *
 * Cuando la función f devuelve false se deja de recorrer la lista.
 *
 * La función retorna la cantidad de elementos a los cuales se le aplicó f
 */
size_t lista_con_cada_elemento(lista_t *lista, bool (*f)(void *, void *),
			       void *extra)
{
        

        if(!lista || !f)
                return 0;

        size_t cant_total = lista_cantidad(lista);
        size_t cant_afectada = 0;
        bool seguimos = true;
        nodo_t *nodo_aux = lista->primero;

        for (;seguimos && cant_afectada < cant_total; cant_afectada++){ 
                seguimos = f(nodo_aux->elemento, extra);
                nodo_aux = nodo_aux->siguiente;
        }

        return cant_afectada;
}


/**
* Destruye la lista.
*/
void lista_destruir(lista_t *lista)
{
        if (!lista)
                return;
        
        nodo_t *nodo_actual = lista->primero;

        while (nodo_actual) {
                nodo_t* nodo_siguiente = nodo_actual->siguiente;
                free(nodo_actual);
                nodo_actual = nodo_siguiente;
        }

        free(lista);
}


/**
 * Destruye la lista aplicando la función destructora a cada elemento.
 */
void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
        if (!lista)
                return;
        
        nodo_t *nodo_aux = lista->primero;

        while (nodo_aux) {
                nodo_t *nodo_aux_2 = nodo_aux->siguiente;

                if (destructor)
                        destructor(nodo_aux->elemento);
                
                free(nodo_aux);
                nodo_aux = nodo_aux_2;
        }

        free(lista);        
}

/**
* Crea un iterador externo para la lista.
 */
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

/**
 * Devuelve true si aún quedan elementos por iterar.
 */
bool lista_iterador_hay_mas_elementos(lista_iterador_t *it)
{
        if(!it)
                return false;

        return it->nodo_actual;
}

/**
* Avanza el iterador a la siguiente iteración.
 */
void lista_iterador_avanzar(lista_iterador_t *it)
{
        if (!it || !lista_iterador_hay_mas_elementos(it))
                return;
        
        it->nodo_actual = it->nodo_actual->siguiente;
}

/**
* Devuelve el elemento de la iteración actual.
 */
void *lista_iterador_actual(lista_iterador_t *it)
{
        if (!it || !lista_iterador_hay_mas_elementos(it))
                return NULL;
        
        return it->nodo_actual->elemento;
}

/**
* Destruye el iterador.
*/
void lista_iterador_destruir(lista_iterador_t *it)
{
        free(it);
}