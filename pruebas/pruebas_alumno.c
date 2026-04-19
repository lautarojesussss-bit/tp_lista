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


int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS DEL TP X ===============");

	pa2m_nuevo_grupo("Pruebas de Suma del TDA X");
	pruebas_unitarias_sumar();

	return pa2m_mostrar_reporte();
}
