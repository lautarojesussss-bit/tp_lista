#include "src/lista.h"
#include "pila.h"
#define ERROR -1
#define MULTIPLICAR_STRING "*/"
#define MULTIPLICAR '*'
#define SUMAR '+'
#define RESTAR '-'
#define DIVIDIR '/'

typedef enum {
        COMPLETADA,
        ERROR_MEMORIA,
        ARGUMENTO_INVALIDO,
        ARGUMENTOS_INSUFICIENTES,
        OPERANDOS_INSUFICIENTES,
        OPERADORES_INSUFICIENTES
} estado_t;


bool es_operador(char *string)
{
        if(!string || strlen(string) == 0)
                return false;

        if (strlen(string) == 1 && (string[0] == '/' || string[0] == '+' || string[0] == '-'))
                return true;

        if (strlen(string) == 2 && strcmp(string, MULTIPLICAR) == 0)
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

bool operar(pila_t *operandos, int *numeros_leidos, size_t tope_numeros, char *operador)
{
        if (pila_cantidad(operandos) < 2 || !numeros_leidos || !es_operador_valido(operador))
                return false;

        
        int *operando_2 = pila_desapilar(operandos);
        int *operando_1 = pila_desapilar(operandos);

        if (!operando_1 || !operando_2)
                return false;

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
                numeros_leidos[tope_numeros] = *operando_1 / *operando_2;
                break;
        
        default:
                break;
        }

        return true;
}


estado_t procesar_tokens(int argc, int *numeros_leidos, char **argv, pila_t *operandos, size_t *tope_numeros)
{
        bool seguimos = true;
        for (size_t pos_aux = 1; pos_aux < argc && seguimos; pos_aux++) {

                char *argumento_aux = argv[pos_aux];
                if (es_numero(argumento_aux, &(numeros_leidos[*tope_numeros])))
                        seguimos = pila_apilar(operandos, &(numeros_leidos[*tope_numeros]));
                else
                        seguimos = operar(operandos, numeros_leidos, tope_numeros, argumento_aux);

                (*tope_numeros)++;
        }

}

estado_t calcular_expresion(int argc, char **argv, int* resultado)
{
        if (!argv || !resultado)
                return ARGUMENTOS_INSUFICIENTES;

        pila_t *operandos = pila_crear();
        if (!operandos)
                return ERROR_MEMORIA;
        
        int *numeros_leidos = calloc(argc-1, sizeof(int));
        if (!numeros_leidos) {
                pila_destruir(operandos);
                return ERROR_MEMORIA;
        }
        size_t tope_numeros = 0;
        bool seguimos = true;

        for (size_t pos_aux = 1; pos_aux < argc && seguimos; pos_aux++) {

                char *argumento_aux = argv[pos_aux];
                tope_numeros = pos_aux -1;
                if (es_numero(argumento_aux, &(numeros_leidos[tope_numeros])))
                        seguimos = pila_apilar(operandos, &(numeros_leidos[tope_numeros]));
                else
                        seguimos = operar(operandos, numeros_leidos, tope_numeros, argumento_aux);
        }
        
        int *resultado_aux = pila_desapilar(operandos);     

        if (!seguimos || pila_cantidad(operandos) != 0 || !resultado_aux){
                pila_destruir(operandos);
                free(numeros_leidos);
                return ERROR;
        }

        *resultado = *resultado_aux;
        pila_destruir(operandos);
        free(numeros_leidos);
}

int main(int argc, char **argv)
{
	if(argc < 4 || !argv){
                printf("ERROR");
                return ERROR;
        }

        int resultado = 0;
        estado_t estado_cuenta = calcular_expresion(argc, argv, &resultado);

        if (estado_cuenta == COMPLETADA)
                printf("%d", resultado);
        else 
                avisar_error(estado_cuenta);

        return estado_cuenta;
}