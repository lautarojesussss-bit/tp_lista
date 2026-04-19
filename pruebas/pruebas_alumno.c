#include "pa2m.h"
#include <stdio.h>
#include "../src/lista.h"


void prueba_lista_insertar_NULL()
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_insertar(lista, NULL), "Insertar un elemento NULL a una lista.");
        lista_destruir(lista);
}

void prueba_lista_destruir_todo_NULL()
{
        int elemento = 1;
        lista_t* lista = lista_crear();
        lista_insertar(lista, &elemento);

        lista_destruir_todo(lista, NULL);

        pa2m_afirmar(true, "Se elimina una lista pasando un destructor NULL, y no hay error.");
}

void prueba_lista_obtener_sin_eliminar()
{
        int elemento = 1;
        lista_t *lista = lista_crear();
        lista_insertar(lista, &elemento);

        lista_obtener(lista);

        pa2m_afirmar(lista_cantidad(lista) == 1, "Se obtiene un elemento de una lista con lista_obtener sin que este se elimine de la lista.");
        lista_destruir(lista);
}

static int comparar_enteros(const void *puntero_A, const void *puntero_B)
{
        if (!puntero_A && !puntero_B)
                return 0;

        if (!puntero_A)
                return -1;

        if (!puntero_B)
                return 1;

        const int *entero_A = (const int*)puntero_A;
        const int *entero_B = (const int*)puntero_B;

        if (*entero_A < *entero_B)
                return -1;

        if (*entero_A > *entero_B )
                return 1;

        return 0;
}

void prueba_buscar_posicion_NULL()
{
        int elemento = 1;
        lista_t *lista = lista_crear();
        lista_insertar(lista, &elemento);
        
        bool esta_el_uno = lista_buscar(lista, &elemento, comparar_enteros, NULL);

        pa2m_afirmar(esta_el_uno, "La función devuelve true si está el elemento, incluso si el puntero posición es NULL.");
        lista_destruir(lista);
}

void prueba_buscar_posicion_elemento_repetido()
{
        int elemento_primero = 1;
        int elemento_segundo = 2;
        lista_t *lista = lista_crear();
        lista_insertar(lista, &elemento_primero);

        size_t posicion_elemento = 0;
        bool esta_el_uno = lista_buscar(lista, &elemento_segundo, comparar_enteros, posicion_elemento);

        pa2m_afirmar(esta_el_uno && (posicion_elemento == 0), "Se logra diferenciar entre el valor de los elementos y sus punteros a la hora de comparar.");
        lista_destruir(lista);
}

bool funcion_false(void *ptr1, void *ptr2)
{
        return false;
}

void prueba_lista_con_cada_elemento_false()
{
        int elemento = 1;
        lista_t *lista = lista_crear();
        lista_insertar(lista, &elemento);
        
        size_t cant_evaluada = lista_con_cada_elemento(lista, funcion_false, NULL);

        pa2m_afirmar(cant_evaluada == 1, "Se devuelve la cantidad correcta de elementos evaluados cuando se devuelve siempre false y se paso un extra NULL.");
        lista_destruir(lista);       
}

void prueba_iterador_colgante()
{
        lista_t *lista = lista_crear();
        lista_iterador_t *iterador = lista_iterador_crear(lista);
        void* elemento_actual = lista_iterador_actual(iterador);

        pa2m_afirmar(!elemento_actual, "Se puede pedirle el elemento actual a un iterador de una lista vacia sin que se rompa nada.");
        lista_destruir(lista);
        lista_iterador_destruir(iterador);
}

void prueba_iterador_colgante()
{
        int elemento = 1;
        lista_t *lista = lista_crear();
        lista_insertar(lista, &elemento);        
        lista_iterador_t *iterador = lista_iterador_crear(lista);
        lista_iterador_destruir(iterador);
        int *elemento_recuerado = lista_obtener(lista);

        pa2m_afirmar(elemento == *elemento_recuerado, "Se puede destruir el iterador de una lista sin que esta deje de funcionar.");
        lista_destruir(lista);
}


void prueba_iterador_actualizado()
{
        lista_t *lista = lista_crear();
        lista_iterador_t *iterador = lista_iterador_crear(lista);
        bool primer_chequeo = lista_iterador_hay_mas_elementos(iterador);
        int elemento = 1;
        lista_insertar(lista, &elemento);
        bool segundo_chequeo = lista_iterador_hay_mas_elementos(iterador);        

        pa2m_afirmar(primer_chequeo != segundo_chequeo, "Se puede cambiar la lista y que el iterador responda a esos cambios.");
        lista_destruir(lista);
        lista_iterador_destruir(iterador);
}

void prueba_iterador_colgante()
{
        lista_t *lista = lista_crear();        
        lista_iterador_t *iterador = lista_iterador_crear(lista);

        lista_iterador_avanzar(iterador);
        pa2m_afirmar(true, "Se puede intentar avanzar en un iterador de una lista vacía sin que se rompa nada.");
        lista_destruir(lista);
        lista_iterador_destruir(iterador);
}

void prueba_iterador_colgante()
{
        lista_t *lista = lista_crear();        
        lista_iterador_t *iterador = lista_iterador_crear(lista);

        lista_destruir(lista);
        lista_iterador_destruir(lista);
        pa2m_afirmar(true, "Se puede destruir primero la lista y luego el iterador sin que se rompa nada.");
}

void prueba_iterador_hay_mas_elementos_lista_vacia()
{
        lista_t *lista = lista_crear();        
        lista_iterador_t *iterador = lista_iterador_crear(lista);

        bool hay_mas_elementos = lista_iterador_hay_mas_elementos(iterador);

        pa2m_afirmar(!hay_mas_elementos, "Se puede crear un iterador a partir de una lista vacía y si preguntamos si tiene elementos nos de false.");
        lista_iterador_destruir(lista);
        lista_destruir(lista);  
}

void prueba_iterador_hay_mas_elementos_NULL()
{
        lista_t *lista = lista_crear();
        lista_insertar(lista, NULL);
        
        lista_iterador_t *iterador = lista_iterador_crear(lista);

        bool hay_mas_elementos = lista_iterador_hay_mas_elementos(iterador);

        pa2m_afirmar(hay_mas_elementos, "Se comunica que si hay elementos cuando usamos la función con una lista que tiene 1 elemento NULL.");
        lista_iterador_destruir(lista);
        lista_destruir(lista);  
}


int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS DEL TP X ===============");

	pa2m_nuevo_grupo("Pruebas de Suma del TDA X");
	pruebas_unitarias_sumar();

	return pa2m_mostrar_reporte();
}
