#include "src/lista.h"
#include "src/pila.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ERROR -1
#define MULTIPLICAR '*'
#define SUMAR '+'
#define RESTAR '-'
#define DIVIDIR '/'

typedef enum {
	EXITO,
	ERROR_MEMORIA,
	ARGUMENTO_INVALIDO,
	ARGUMENTOS_INSUFICIENTES,
	OPERANDOS_INSUFICIENTES,
	OPERADORES_INSUFICIENTES,
	DIVISION_POR_CERO,
} estado_t;

bool es_operador(char *string)
{
	if (!string || strlen(string) == 0)
		return false;

	if (strlen(string) == 1 &&
	    (string[0] == SUMAR || string[0] == RESTAR ||
	     string[0] == DIVIDIR || string[0] == MULTIPLICAR))
		return true;

	return false;
}

bool es_numero(const char *cadena, int *valor)
{
	if (!cadena || cadena[0] == '\0')
		return false;

	char *endptr;
	long valor_convertido = 0;

	valor_convertido = strtol(cadena, &endptr, 10);

	if (cadena == endptr || *endptr != '\0')
		return false;

	*valor = (int)valor_convertido;
	return true;
}

estado_t operar(pila_t *operandos, char *operador)
{
	if (pila_cantidad(operandos) < 2)
		return OPERANDOS_INSUFICIENTES;

	if (!es_operador(operador))
		return ARGUMENTO_INVALIDO;

	int *ptr_operando_2 = pila_desapilar(operandos);
	int *ptr_operando_1 = pila_desapilar(operandos);
	int *resultado = calloc(1, sizeof(int));

	if (!ptr_operando_1 || !ptr_operando_2 || !resultado) {
		free(ptr_operando_1);
		free(ptr_operando_2);
		free(resultado);
		return ERROR_MEMORIA;
	}

	estado_t estado_operacion = EXITO;

	switch (*operador) {
	case MULTIPLICAR:
		*resultado = *ptr_operando_1 * *ptr_operando_2;
		break;

	case SUMAR:
		*resultado = *ptr_operando_1 + *ptr_operando_2;
		break;

	case RESTAR:
		*resultado = *ptr_operando_1 - *ptr_operando_2;
		break;

	case DIVIDIR:
		if (*ptr_operando_2 == 0)
			estado_operacion = DIVISION_POR_CERO;
		else
			*resultado = *ptr_operando_1 / *ptr_operando_2;
		break;

	default:
		break;
	}

	free(ptr_operando_1);
	free(ptr_operando_2);

	if (estado_operacion != EXITO) {
		free(resultado);
		return estado_operacion;
	}

	if (!pila_apilar(operandos, resultado)) {
		free(resultado);
		return ERROR_MEMORIA;
	}

	return estado_operacion;
}

estado_t agregar_operando(pila_t *operandos, int operando)
{
	int *nuevo_operando = calloc(1, sizeof(int));
	if (!nuevo_operando)
		return ERROR_MEMORIA;

	*nuevo_operando = operando;
	if (!pila_apilar(operandos, nuevo_operando)) {
		free(nuevo_operando);
		return ERROR_MEMORIA;
	}

	return EXITO;
}

estado_t procesar_argumento(pila_t *operandos, char *argumento_aux)
{
	estado_t estado_operacion = EXITO;
	int operando = 0;

	if (es_numero(argumento_aux, &operando)) {
		estado_operacion = agregar_operando(operandos, operando);
	} else
		estado_operacion = operar(operandos, argumento_aux);

	return estado_operacion;
}

estado_t calcular_expresion(int argc, char **argv, int *resultado)
{
	if (!argv || !resultado)
		return ARGUMENTOS_INSUFICIENTES;

	pila_t *operandos = pila_crear();
	if (!operandos)
		return ERROR_MEMORIA;

	estado_t estado_operacion = EXITO;

	for (size_t pos_aux = 1;
	     pos_aux < (size_t)argc && estado_operacion == EXITO; pos_aux++) {
		char *argumento_aux = argv[pos_aux];

		estado_operacion = procesar_argumento(operandos, argumento_aux);
	}

	int *resultado_aux = pila_desapilar(operandos);

	if (estado_operacion == EXITO && pila_cantidad(operandos) > 0)
		estado_operacion = OPERADORES_INSUFICIENTES;

	if (estado_operacion == EXITO && resultado_aux &&
	    pila_cantidad(operandos) == 0)
		*resultado = *resultado_aux;

	free(resultado_aux);
	pila_destruir_todo(operandos, free);
	return estado_operacion;
}

void avisar_error(estado_t estado_final)
{
	switch (estado_final) {
	case ERROR_MEMORIA:
		printf("ERROR DE MEMORIA.\n");
		break;

	case ARGUMENTO_INVALIDO:
		printf("HAY ARGUMENTOS INVÁLIDOS.\n");
		break;

	case ARGUMENTOS_INSUFICIENTES:
		printf("NO HAY ARGUMENTOS SUFICIENTES.\n");
		break;

	case OPERANDOS_INSUFICIENTES:
		printf("NO HAY OPERANDOS SUFICIENTES PARA TODOS LOS OPERADORES.\n");
		break;

	case OPERADORES_INSUFICIENTES:
		printf("HAY DEMASIADOS OPERANDOS.\n");
		break;

	case DIVISION_POR_CERO:
		printf("ERROR POR INTENTAR DIVIDIR POR CERO.\n");
		break;

	default:
		break;
	}
}

int main(int argc, char **argv)
{
	if (argc < 4 || !argv) {
		printf("ERROR.\n");
		return ERROR;
	}

	int resultado = 0;
	estado_t estado_operacion = calcular_expresion(argc, argv, &resultado);

	if (estado_operacion == EXITO)
		printf("%d\n", resultado);
	else
		avisar_error(estado_operacion);

	return 0;
}