#include "lista.h"
#include "pila.h"

struct pila{
        lista_t *lista;
};

/**
 * Crea una pila
 */
pila_t *pila_crear()
{
        pila_t *pila = malloc(sizeof(pila_t));
        if (!pila)
                return NULL;

        pila->lista = lista_crear();

        if (!(pila->lista)){
                free(pila);
                return NULL;
        }

        return pila;
}


/*
* Apila un elemento en la pila. Devuelve la pila o NULL en caso de error.
*/
pila_t *pila_apilar(pila_t *pila, void *elemento)
{
        if (!pila)
                return NULL;
        
        if(!lista_insertar_posicion(pila->lista, 0, elemento))        
                return NULL;
        
        return pila;
}

/**
 * Desapila un elemento y lo devuelve. Devuelve NULL en caso de error.
 */
void *pila_desapilar(pila_t *pila)
{
        if (!pila)
                return NULL;

        return lista_eliminar_posicion(pila->lista, 0);
}

/**
 * Devuelve el primer elemento de la pila y lo devuelve (o NULL en caso de error).
 */
void *pila_tope(pila_t *pila)
{
        if(!pila)
                return NULL;

        return lista_obtener_posicion(pila->lista, 0);
}

/**
 * Devuelve la cantidad de elementos en la pila.
 */
size_t pila_cantidad(pila_t *pila)
{
        if(!pila)
                return 0;

        return lista_cantidad(pila->lista);
}

/**
 * Destruye la pila
 */
void pila_destruir(pila_t *pila)
{
        if(!pila)
                return;

        lista_destruir(pila->lista);
        free(pila);
}

/**
 * Destruye la pila aplicando la función destructora a cada elemento.
 */
void pila_destruir_todo(pila_t *pila, void (*destructor)(void *))
{
        if(!pila)
                return;

        lista_destruir_todo(pila->lista, destructor);
        free(pila);
}