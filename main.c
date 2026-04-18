#include "src/lista.h"
#include "pila.h"
#define ERROR -1
#define MULTIPLICAR '*'
#define SUMAR '+'
#define RESTAR '-'
#define DIVIDIR '/'

typedef enum {
        ERROR_MEMORIA,
        ARGUMENTO_INVALIDO,
        ARGUMENTOS_INSUFICIENTES,
        OPERANDOS_INSUFICIENTES,
        OPERADORES_INSUFICIENTES,
        DIVISION_POR_CERO,
        EXITO
} estado_t;


bool es_operador(char *string)
{
        if(!string || strlen(string) == 0)
                return false;

        if (strlen(string) == 1 && (string[0] == SUMAR || string[0] == RESTAR || string[0] == DIVIDIR || string[0] == MULTIPLICAR))
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

estado_t operar(pila_t *operandos, int *numeros_leidos, size_t tope_numeros, char *operador)
{
        if (pila_cantidad(operandos) < 2 || !numeros_leidos)
                return OPERANDOS_INSUFICIENTES;

        if (!es_operador(operador))
                return ARGUMENTO_INVALIDO;

        int *operando_2 = pila_desapilar(operandos);
        int *operando_1 = pila_desapilar(operandos);

        if (!operando_1 || !operando_2)
                return ERROR_MEMORIA;

        estado_t estado_operacion = EXITO;

        switch (*operador)
        {
        case MULTIPLICAR:
                numeros_leidos[tope_numeros] = *operando_1 * *operando_2;
                break;

        case SUMAR:
                numeros_leidos[tope_numeros] = *operando_1 + *operando_2;
                break;

        case RESTAR:
                numeros_leidos[tope_numeros] = *operando_1 - *operando_2;
                break;

        case DIVIDIR:
                if(*operando_2 == 0)
                        estado_operacion = DIVISION_POR_CERO;
                else 
                        numeros_leidos[tope_numeros] = *operando_1 / *operando_2;
                break;
        
        default:
                break;
        }
        
        if (estado_operacion == EXITO)
                estado_operacion = pila_apilar(operandos, &(numeros_leidos[tope_numeros])) ? EXITO : ERROR_MEMORIA;

        return estado_operacion;
}

estado_t procesar_argumento(pila_t *operandos, int tope_numeros, char *argumento_aux, int *numeros_leidos)
{
        estado_t estado_operacion = EXITO;

        if (es_numero(argumento_aux, &(numeros_leidos[tope_numeros])))
                estado_operacion = pila_apilar(operandos, &(numeros_leidos[tope_numeros])) ? EXITO : ERROR_MEMORIA;
        else
                estado_operacion = operar(operandos, numeros_leidos, tope_numeros, argumento_aux);

        return estado_operacion;
}

estado_t calcular_expresion(int argc, char **argv, int* resultado)
{
        if (!argv || !resultado)
                return ARGUMENTOS_INSUFICIENTES;

        pila_t *operandos = pila_crear();
        if (!operandos)
                return ERROR_MEMORIA;
        

        int *numeros_leidos = calloc(argc-1, sizeof(int));
        if (!numeros_leidos)
                return ERROR_MEMORIA;

        estado_t estado_operacion = EXITO;

        for (size_t pos_aux = 1; pos_aux < argc && estado_operacion == EXITO; pos_aux++) {
                char *argumento_aux = argv[pos_aux];
                size_t tope_numeros = pos_aux -1;

                estado_operacion = procesar_argumento(operandos, tope_numeros, argumento_aux, numeros_leidos);
        }

        int *resultado_aux = pila_desapilar(operandos);

        if(estado_operacion == EXITO && pila_cantidad(operandos) >0)
                estado_operacion = OPERADORES_INSUFICIENTES;

        if (estado_operacion == EXITO && resultado_aux && pila_cantidad(operandos) == 0)
                *resultado = *resultado_aux;

        pila_destruir(operandos);
        free(numeros_leidos);
        return estado_operacion;
}

void avisar_error(estado_t estado_final)
{
        switch (estado_final)
        {
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
	if(argc < 4 || !argv){
                printf("ERROR.\n");
                return ERROR;
        }

        int resultado = 0;
        estado_t estado_operacion = calcular_expresion(argc, argv, &resultado);

        if (estado_operacion == EXITO)
                printf("%d\n", resultado);
        else 
                avisar_error(estado_operacion);

        return estado_operacion;
}